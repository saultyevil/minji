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
  int i;
  double photon_buff_size;

  double rad_lum = 1e6, n_photons = 1e6;

  Log ("\t- Initialising photon structure\n");

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

  #ifdef MPI_ON
    n_photons_og = N_PHOTONS;
    N_PHOTONS /= n_mpi_processes;
    PROGRESS_OUT_FREQ /= n_mpi_processes;
  #endif
  
  /*
   * Allocate storage for all the photon_main and define each photon. If enough
   * space cannot be allocated, then this should be reported and the program
   * will exit
   */

  Log ("\t\t- Defining %1.2e photons in total\n", n_photons);

  #ifdef MPI_ON
    Log ("\t\t- Allocating %1.2e photons per process\n", (double) N_PHOTONS);
  #endif

  photon_buff_size = N_PHOTONS * sizeof (*phot_main);
  
  if (!(phot_main = calloc (N_PHOTONS, sizeof (*phot_main))))
    Exit (4, "init_photons: Couldn't allocate %f bytes for %1.2e photons\n",
          photon_buff_size, (double) N_PHOTONS);
  
  Log ("\t\t- Allocated %1.2e bytes for %1.2e photons\n", photon_buff_size,
       (double) N_PHOTONS);

  Log ("\t\t- Generating photons\n");
  
  for (i = 0; i < N_PHOTONS; i++)
    define_photon (&phot_main[i], i);
  
  return SUCCESS;
}

int define_photon (Photon *p, int number)
{
  double theta, phi;
  
  p->n = number;
  p->in_grid = TRUE;
  p->w = p->w_0 = RAD_LUM / N_PHOTONS;
  
  /*
   * Generate a random theta and phi direction and update the x, y and z
   * directions
   */

  random_theta_phi (&theta, &phi);
  p->nx = sin (theta) * cos (phi);
  p->ny = sin (theta) * sin (phi);
  p->nz = cos (theta);

  /*
   * Set photons to be emitted from the origin, i.e. the first cell
   */

  p->x = TRANS_FUDGE;
  p->y = TRANS_FUDGE;
  p->z = TRANS_FUDGE;
  p->icell = (int) (p->x * geo.nx_cells / geo.x_max);

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
