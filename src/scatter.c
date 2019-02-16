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


void
scatter_phot (Photon * p)
{
  double theta, phi;

  random_theta_phi (&theta, &phi);
  p->nx = sin (theta) * cos (phi);
  p->ny = sin (theta) * sin (phi);
  p->nz = cos (theta);
}
