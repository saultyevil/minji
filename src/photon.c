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
#include "log.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
move_photon(struct Photon *p, double ds)
{
  p->x += ds * p->nx;
  p->y += ds * p->ny;
  p->z += ds * p->nz;
  p->icell = (int) (p->x * Geometry.ncells / Geometry.rmax);
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
  p->w = 1.0;

  /*
   * Generate a random theta and phi direction and update the x, y and z
   * directions
   */

  double theta, phi;
  get_random_theta_phi_direction(&theta, &phi);
  p->nx = sin(theta) * cos(phi);
  p->ny = sin(theta) * sin(phi);
  p->nz = cos(theta);

  /*
   * Set photons to be emitted from the origin, i.e. the first cell
   */

  p->x = 0;
  p->y = 0;
  p->z = 0;
  p->icell = (int) (p->x * Geometry.ncells / Geometry.rmax);
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
  mlog("Initialising photon structure\n");

  double nphotons;
  read_double("n_photons", &nphotons);
  if((Geometry.nphotons = (int) nphotons) <= 0)
    mabort(FAILURE, "Invalid value for n_photons: n_photons > 0\n");

  unsigned long memory = Geometry.nphotons * sizeof(struct Photon);

  if(!(Photons = calloc(Geometry.nphotons, sizeof(struct Photon))))
    mabort(FAILURE, "init_photons: Couldn't allocate %f bytes for %1.2e photons\n", memory, (double) Geometry.nphotons);

  mlog("Allocated %1.2e bytes for %1.2e photons\n", memory, (double) Geometry.nphotons);

  for(int i = 0; i < Geometry.nphotons; i++)
    create_photon(&Photons[i], i);
}



