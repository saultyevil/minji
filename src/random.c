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
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "minji.h"

gsl_rng *rng;


void
init_gsl_seed (void)
{
  int seed = 666;

  get_int (SEED_STR, &seed);

  /*
   * When MPI is enabled, add the process number to the seed so each MPI
   * process will have its own seed
   */

  if ((rng = gsl_rng_alloc (gsl_rng_mt19937)))
#ifdef MPI_ON
    gsl_rng_set (rng, (unsigned long) seed + mpi.proc);
#else
    gsl_rng_set (rng, (unsigned long) seed);
#endif
  else
    Exit (GSL_RNG_ERROR, "GSL error: couldn't allocate RNG\n");
}

double
gsl_rand_num (double min, double max)
{
  return min + ((max - min) * gsl_rng_uniform_pos (rng));
}

double
random_tau (void)
{
  return -1.0 * log (1 - gsl_rand_num (0, 1));
}

void
random_theta_phi (double *theta, double *phi)
{
  *theta = acos (2 * gsl_rand_num (0, 1) - 1);
  *phi = 2 * M_PI * gsl_rand_num (0, 1);
}
