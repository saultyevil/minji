/* ***************************************************************************
 *
 * @file
 *
 * @author
 *
 * @brief
 *
 * @details
 *
 * ************************************************************************** */

#include <math.h>

#include "minji.h"

int scatter_phot (Photon *photon)
{
  double theta, phi;
  
  random_theta_phi (&theta, &phi);
  photon->nx = sin (theta) * cos (phi);
  photon->ny = sin (theta) * sin (phi);
  photon->nz = cos (theta);
  
  return SUCCESS;
}
