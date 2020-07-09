/* ************************************************************************** */
/**
* @file    trans_phot.c
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#include "minji.h"
#include "fmt.h"
#include "log.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

// We only care about it traversing in one direction as it is 1d
static double
ds_to_escape(const struct Photon p)
{
  double smax;

  if(p.nx > 0)
  {
    smax = (Geometry.rmax - p.x) / p.nx;
  }
  else if(p.nx < 0)
  {
    smax = -1.0 * p.x / p.nx;
  }
  else
  {
    smax = 100 * Geometry.rmax;
  }

  return smax;
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

/*
 * If the distance to the next cell wall is small, then we will consider the
 * photon to be in the next cell wall, move it into the next cell and then
 * calculate dx for the new cell
 */

static double
ds_to_cell_wall(struct Photon p)
{
  double ds;

  if(p.nx > 0)
  {
    ds = (GridCells[p.icell].r - p.x) / p.nx;
    if(ds < Geometry.pushthrough_distance)
    {
      p.x = GridCells[p.icell].r;
      p.icell += 1;
      ds = (GridCells[p.icell].r - p.x) / p.nx;
    }
  }
  else if(p.nx < 0)
  {
    ds = (GridCells[p.icell - 1].r - p.x) / p.nx;
    if(ds < Geometry.pushthrough_distance)
    {
      p.x = GridCells[p.icell - 1].r;
      p.icell -= 1;
      ds = (GridCells[p.icell - 1].r - p.x) / p.nx;
    }
  }
  else
  {
    ds = 100 * Geometry.rmax;
  }

  if(ds < 0)
  merror("trans_phot: p %i: dx < 0 (dx = %f)\n", p.n, ds);

  return ds;
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
move_photon_to_scatter(struct Photon p)
{
  double tau_scat;
  get_random_optical_depth(&tau_scat);

  /*
   * Calculate the total distance, s_max, the photon is required to traverse to
   * escape from the atmosphere. If s_max is very small, we will consider that
   * the photon is already at the edge of the simulation grid and exit
   */

  double smax = ds_to_escape(p) * Geometry.smax_transport_frac;
  if(smax < Geometry.pushthrough_distance)
  {
    p.in_grid = false;
    return;
  }

  double ds = 0;
  double tau = 0;

  while(tau < tau_scat && ds < smax)
  {
    /*
     * Figure out the distance to the nearest cell wall, then calculate the
     * total optical depth a photon will encounter as it traverses towards the
     * cell wall. Recall that this is given by,
     *      dtau = rho * kappa * ds
     */

    double dcell = ds_to_cell_wall(p);
    double tau_cell = GridCells[p.icell].opac * GridCells[p.icell].dens * d_cell;

    /*
     * If the total optical depth PLUS the optical depth experience by the
     * photon is more than the optical depth to the next scattering event,
     * then the photon is moved a distance given by tau_cell. The while loop
     * will then break. Otherwise, the photon does not scatter in the current
     * cell, hence the photon will be moved to the edge of the cell and the
     * while loop will iterate again.
     */

    double ds_scat;
    if((tau + tau_cell) >= tau_scat)
    {
      ds_scat = (tau_scat - tau) / (GridCells[p.icell].opac * GridCells[p.icell].dens);
    }
    else
    {
      ds_scat = dcell;
    }

    /*
     * The running totals for optical depth and ds moved are now incremented
     * and the position of the photon is updated
     */

    ds += ds_scat;
    tau += tau_cell;
    traverse_phot_ds(p, ds_scat);
  }

  /*
   * If the photon has moved greater than the allowed s_max, then the photon is
   * no longer within the atmosphere, hence p->in_grid is switched to FALSE to
   * indicate this. Otherwise, the photon is still within the atmosphere hence
   * the photon's position is updated
   */

  if(ds >= smax)
  {
    p.in_grid = false;
  }
  else
  {
    traverse_phot_ds(p, ds_scat);
  }
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
transport_photons(void)
{
  int nscat = 0;

  mlog("Beginning MCRT iterations\n");
  const struct timespec mcrt_start = get_current_time();

  for(int i = 0; i < Geometry.nphotons; i++)
  {
    struct Photon p = Photons[i];

    move_photon_to_scatter(p);
    while(p.in_grid)
    {
      double xi = gsl_rand_num(0, 1);
      if(xi < Geometry.scatter_albedo)
      {
        scatter_photon(&p);
        nscat += 1;
      }

      move_photon_to_scatter(p);
    }
  }
}
