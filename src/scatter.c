/**
* @file    scatter.c
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include <math.h>

#include "minji.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
scatter_photon(struct Photon *p)
{
  double theta, phi;

  get_random_theta_phi_direction(&theta, &phi);
  p->nx = sin(theta) * cos(phi);
  p->ny = sin(theta) * sin(phi);
  p->nz = cos(theta);
}
