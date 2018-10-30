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

int init_gsl_seed (void)
{
  int seed = 666;
  
  get_int ("seed", &seed);
  
  if ((rng = gsl_rng_alloc (gsl_rng_mt19937)))
  {
    gsl_rng_set (rng, (unsigned long) seed);
    // Log ("Generating random sequence using seed %i\n", seed);
  }
  else
    Exit (6, "init_gsl_seed: GSL error, couldn't allocate RNG. Not enough memory?\n");
  
  return SUCCESS;
}

double gsl_rand_num (double min, double max)
{
  return min + ((max - min) * gsl_rng_uniform_pos (rng));
}

double random_tau (void)
{
  return -1.0 * log (1 - gsl_rand_num (0, 1));
}

int random_theta_phi (double *theta, double *phi)
{
  *theta = acos (2 * gsl_rand_num (0, 1) - 1);
  *phi = 2 * M_PI * gsl_rand_num (0, 1);
  
  return SUCCESS;
}
