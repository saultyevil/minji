/* ************************************************************************** */
/**
* @file    trans_phot.c
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include <math.h>
#include <time.h>

#include "minji.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

static double
ds_to_cell_wall(struct Photon p)
{
  double ds;

  ds = spherical_ds_to_cell_edge(p);  // TODO 1d case

  return ds;
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

static void
move_photon_to_scatter(struct Photon *p)
{
  double tau_scat;
  get_random_optical_depth(&tau_scat);

  /*
   * Calculate the total distance, s_max, the photon is required to traverse to
   * escape from the atmosphere. If s_max is very small, we will consider that
   * the photon is already at the edge of the simulation grid and exit
   */

  double smax_escape = ds_to_sphere(Geometry.rmax, *p);
  if(smax_escape < Geometry.pushthrough_distance)
  {
    p->in_grid = false;
    return;
  }

  double ds = 0;
  double tau = 0;
  double ds_move;

  while(tau < tau_scat && ds < smax_escape)
  {
    double ds_cell_edge = ds_to_cell_wall(*p);
    double tau_cell_edge = GridCells[p->grid].mdensity * ds_cell_edge;

    if((tau + tau_cell_edge) >= tau_scat)
    {
      ds_move = (tau_scat - tau) / (tau_cell_edge);
    }
    else
    {
      ds_move = ds_cell_edge;
    }


    ds += ds_move;
    // TODO move to edge of grid instead or something
    if (ds > smax_escape)
    {
      p->in_grid = false;
      break;
    }

    tau += tau_cell_edge;
    move_photon(p, ds_move);
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
  int output = Geometry.nphotons / 10;
  if(output < 1)
    output = 1;

  const struct timespec mcrt_start = get_current_time();

  int nscat = 0;
  for(int i = 0; i < Geometry.nphotons; i++)
  {
    if(i % output == 0)
      mlog("- %-9i of %-9i photons transported or %-03.2f%%", i, Geometry.nphotons, (double) i / Geometry.nphotons * 100);

    struct Photon p = Photons[i];

    while(p.in_grid)
    {
      struct Photon porig = p;
      move_photon_to_scatter(&p);

      // check inner boundary
      double ds_star = ds_to_sphere(Geometry.rmin, porig);
      double position = vector_magnitude(p.xyz);
      double path[3];
      subtract_vectors(p.xyz, porig.xyz, path);
      double pathlength = vector_magnitude(path);
      if(position < Geometry.rmin || (ds_star < LARGE_NUMBER && pathlength))
      {
        p.in_grid = false;
        break;
      }

      // check outer boundary
      double rhosq = p.xyz[0] * p.xyz[0] + p.xyz[1] * p.xyz[1];
      double rmaxsq = Geometry.rmax * Geometry.rmax;

      if(rhosq > rmaxsq)
      {
        p.in_grid = false;
        break;
      }
      if(fabs(p.xyz[2]) > Geometry.rmax)
      {
        p.in_grid = false;
        break;
      }

      double xi = gsl_rand_num(0, 1);
      if(p.in_grid && xi < Geometry.scatter_albedo)
      {
        scatter_photon(&p);
        p.nscat++;
        nscat++;
      }
    }
  }

  mlog("- %-9i of %-9i photons transported or 100.00%%", Geometry.nphotons, Geometry.nphotons);
  mlog("number of scatters = %i", nscat);
  mlog("average number of scatters per photon = %i", (int) nscat / Geometry.nphotons);
}
