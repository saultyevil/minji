/* ************************************************************************** */
/**
* @file    init.c
* @author  Edward Parkinson
* @brief   Contains the functions for initialising various variables and data
 *         structures used throughout the code.
*
* @details
*
* *************************************************************************** */

#include "minji.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief   Sets default values for a bunch of variables used throughout the
*          program.
*
* @details
*
* *************************************************************************** */

extern void
init_minji(void)
{
  Geometry.nphotons = (int) 1e6;
  Geometry.grid_type == GRID_LINEAR;
  Geometry.ncells = 500;
  Geometry.rmax = 1.0;
  Geometry.scatter_albedo = 1.0;
  Geometry.smax_transport_frac = 0.90;
  Geometry.pushthrough_distance = Geometry.rmax / Geometry.ncells / 1e5;

  init_gsl_seed();
}
