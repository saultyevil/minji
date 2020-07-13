/* ************************************************************************** */
/**
* @file    photon.c
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "minji.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern int
find_grid_cell(const double *xyz)
{
  int n;

  n = spherical_where_in_grid(xyz);  // TODO 1d case

  return n;
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
move_photon(struct Photon *p, const double ds)
{
  p->xyz[0] += ds * p->ijk[0];
  p->xyz[1] += ds * p->ijk[1];
  p->xyz[2] += ds * p->ijk[2];
  p->grid = find_grid_cell(p->xyz);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
create_photon(struct Photon *p, int number)
{
  p->n = number;
  p->in_grid = true;
  p->weight = 1.0;
  p->nscat = 0;

  /*
   * Generate a random theta and phi direction and update the x, y and z
   * directions
   */

  double theta, phi;
  get_random_theta_phi_direction(&theta, &phi);
  p->ijk[0] = sin(theta) * cos(phi);
  p->ijk[1] = sin(theta) * sin(phi);
  p->ijk[2] = cos(theta);

  /*
   * Set photons to be emitted from the skin of the central source
   */

  random_spherical_vector(p->xyz, Geometry.rmin + Geometry.pushthrough_distance);
  p->grid = find_grid_cell(p->xyz);
  if (p->grid == PHOTON_OUTSIDE_GRID)
    merror("photon %i is not in the grid when defined", p->n);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
init_photons(void)
{
  mlog("Initialising photons");

  double nphotons = 0;
  read_double("Geometry.nphotons", &nphotons);
  Geometry.nphotons = (int) nphotons;
  if(Geometry.nphotons <= 0)
    mabort(FAILURE, "Invalid value for n_photons %e: n_photons > 0", (double) Geometry.nphotons);

  unsigned long memory = Geometry.nphotons * sizeof(struct Photon);

  if(!(Photons = calloc(Geometry.nphotons, sizeof(struct Photon))))
    mabort(FAILURE, "init_photons: Couldn't allocate %e bytes for %3.2e photons", (double) memory, (double) Geometry.nphotons);

  mlog("Allocated %e bytes for %e photons", (double) memory, (double) Geometry.nphotons);

  for(int i = 0; i < Geometry.nphotons; ++i)
  {
    create_photon(&Photons[i], i);
  }
}



