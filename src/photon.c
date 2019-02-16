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


void
traverse_phot_ds (Photon * p, double ds)
{
  p->x += ds * p->nx;
  p->y += ds * p->ny;
  p->z += ds * p->nz;
  p->icell = (int) (p->x * geo.nx_cells / geo.x_max);
}

void
define_photon (Photon * p, int number)
{
  double theta, phi;

  p->n = number;
  p->in_grid = TRUE;
  p->w = p->w_0 = geo.rad_lum / geo.n_photons;

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

  p->x = geo.trans_fudge;
  p->y = geo.trans_fudge;
  p->z = geo.trans_fudge;
  p->icell = (int) (p->x * geo.nx_cells / geo.x_max);
}

void
init_photons (void)
{
  int i;
  double n_photons = geo.n_photons;
  double photon_buff_size;

  Log ("\t- Initialising photon structure\n");

  /*
   * Read in the number of photon_main from file and check that it is a sensible
   * number. Even though N_PHOTONS is an int, read in n_photons as a double
   * to make input easier as it allows input such as 1e6
   */

  get_double ("n_photons", &n_photons);
  if ((geo.n_photons = (int) n_photons) <= 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for n_photons: n_photons > 0\n");

  get_double ("rad_lum", &geo.rad_lum);
  if (geo.rad_lum <= 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for rad_lum: rad_lum > 0\n");

#ifdef MPI_ON
  config.progress_out_freq /= mpi.n_procs;
  mpi.tot_n_photons = geo.n_photons;
  geo.n_photons /= mpi.n_procs;
#endif

  /*
   * Allocate storage for all the photon_main and define each photon. If enough
   * space cannot be allocated, then this should be reported and the program
   * will exit
   */

  Log ("\t\t- Defining %1.2e photons in total\n", n_photons);

#ifdef MPI_ON
  Log ("\t\t- Allocating %1.2e photons per process\n", (double) geo.n_photons);
#endif

  photon_buff_size = geo.n_photons * sizeof (*photon_bank);

  if (!(photon_bank = calloc (geo.n_photons, sizeof (*photon_bank))))
    Exit (MEM_ALLOC_ERROR, "init_photons: Couldn't allocate %f bytes for %1.2e photons\n", photon_buff_size, (double) geo.n_photons);
  Log ("\t\t- Allocated %1.2e bytes for %1.2e photons\n", photon_buff_size, (double) geo.n_photons);

  Log ("\t\t- Generating photons\n");
  for (i = 0; i < geo.n_photons; i++)
    define_photon (&photon_bank[i], i);
}



