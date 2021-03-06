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
  p->ijk[0] = sin(theta) * cos(phi);
  p->ijk[1] = sin(theta) * sin(phi);
  p->ijk[2] = cos(theta);
}
