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
#include <stdlib.h>

#include "minji.h"

int init_photons (void)
{
  int p;
  double photon_buff_size;

  double rad_lum = 1e6, n_photons = 1e6;
  
  /*
   * Read in the number of photon_main from file and check that it is a sensible
   * number. Even though N_PHOTONS is an int, read in n_photons as a double
   * to make input easier as it allows input such as 1e6
   */
  
  get_double ("n_photons", &n_photons);
  if ((N_PHOTONS = (int) n_photons) <= 0)
    Exit (2, "Invalid value for n_photons: n_photons > 0\n");
  get_double ("rad_lum", &rad_lum);
  if ((RAD_LUM = rad_lum) <= 0)
    Exit (2, "Invalid value for rad_lum: rad_lum > 0\n");

  #ifdef MPION
    N_PHOTONS /= n_mpi_processes;
  #endif
  
  /*
   * Allocate storage for all the photon_main and define each photon. If enough
   * space cannot be allocated, then this should be reported and the program
   * will exit
   */
  
  Log ("\t- Initialising photon structure\n");
  photon_buff_size = N_PHOTONS * sizeof (*phot_main);
  
  if (!(phot_main = calloc (N_PHOTONS, sizeof (*phot_main))))
    Exit (4, "init_photons: Couldn't allocate %f bytes for %1.2e photons\n",
          photon_buff_size, (double) N_PHOTONS);
  
  Log ("\t\t- Allocated %1.2e bytes for %1.2e photons\n", photon_buff_size,
       (double) N_PHOTONS);
  Log ("\t\t- Defining emitted photons\n");
  
  for (p = 0; p < N_PHOTONS; p++)
    define_photon (&phot_main[p], p);
  
  return SUCCESS;
}

int define_photon (Photon *photon, int number)
{
  double theta, phi;
  
  photon->n = number;
  photon->in_grid = TRUE;
  photon->w = photon->w_0 = RAD_LUM / N_PHOTONS;
  
  /*
   * Generate a random theta and phi direction and update the x, y and z
   * directions
   */

  random_theta_phi (&theta, &phi);
  photon->nx = sin (theta) * cos (phi);
  photon->ny = sin (theta) * sin (phi);
  photon->nz = cos (theta);

  return SUCCESS;
}

int traverse_phot_ds (Photon *p, double ds)
{
  p->x += ds * p->nx;
  p->y += ds * p->ny;
  p->z += ds * p->nz;
  p->icell = (int) (p->x * geo.nx_cells / geo.x_max);

  return SUCCESS;
}
