/* ************************************************************************** */
/**
* @file    random.c
* @author  Edward Parkinson
* @brief   Contains the functions for creating random variables.
*
* @details
*
* *************************************************************************** */


#include <math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "minji.h"
#include "functions.h"

const gsl_rng *rng;

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
init_gsl_seed(void)
{
  rng = gsl_rng_alloc(gsl_rng_mt19937);
  long seed = 9874108371231234;

  if(rng)
  {
#ifdef MPI_ON
    /*
     * When MPI is enabled, add the process number to the seed so each MPI
     * process will have its own seed
     */

    gsl_rng_set(rng, seed + MPIConfig.current_process);
#else
    gsl_rng_set(rng, seed);
#endif
  }
  else
  {
    mabort(FAILURE, "GSL error: couldn't allocate RNG\n");
  }
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

double
gsl_rand_num(double min, double max)
{
  return min + ((max - min) * gsl_rng_uniform_pos(rng));
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
get_random_optical_depth(double *const tau)
{
  *tau = -1.0 * log(1 - gsl_rand_num(0, 1));
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
get_random_theta_phi_direction(double *const theta, double *const phi)
{
  *theta = acos(2 * gsl_rand_num(0, 1) - 1);
  *phi = 2 * M_PI * gsl_rand_num(0, 1);
}
