/* ************************************************************************** */
/**
* @file    algebra.c
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

extern int
solve_quadratic(double a, double b, double c, double *solution)
{
  if(a == 0.0)    // not a quadratic, but whatever
  {
    if(b == 0.0)  // roots are imaginary
    {
      *solution = LARGE_NUMBER;
      return FAILURE;
    }

    *solution = -c / b;  // linear solution

    if(*solution < 0)
      return FAILURE;

    return 0;
  }

  double discriminator = b * b - 4 * a * c;

  if(discriminator < 0.0)  // roots are imaginary
  {
    *solution = LARGE_NUMBER;
    return FAILURE;
  }

  double roots[2];
  discriminator = sqrt(discriminator);
  roots[0] = (-b + discriminator) / (2 * a);
  roots[1] = (-b - discriminator) / (2 * a);

  // r[0] is smallest positive root
  if(roots[0] > 0 && (roots[0] < roots[1] || roots[1] < 0))
  {
    *solution = roots[0];
    return SUCCESS;
  }

  // r[1] is smallest positive root
  if(roots[1] > 0 && (roots[1] < roots[0] || roots[0] < 0))
  {
    *solution = roots[1];
    return SUCCESS;
  }

  // both roots were negative
  *solution = LARGE_NUMBER;
  return FAILURE;  // both roots are negative
}

/* ************************************************************************** */
/**
* @brief
*
* @param[in]  mode  MODE_LINEAR or MODE_LOGARITHMIC
* @param[in]  value The value to be interpolated for
* @param[in]  array  The array to interpolate for
* @param[in]  npoints  The number of points in the array
* @param[out] index  The lower index
* @param[out] fraction  The fraction of the upper point used in interpolation
*
* @details
*
* *************************************************************************** */

extern int
linear_interpolation(enum InterpolationMode mode, const double value, const double *array, const int npoints,
                     int *index, double *fraction)
{

  int imin = 0;
  int imax = npoints - 1;

  if(value < array[0])
  {
    *index = 0;
    *fraction = 0.0;
    return -1;
  }

  if(value > array[imax])
  {
    *index = npoints - 2;
    *fraction = 1.0;
    return 1;
  }

  while(imax - imin > 1)
  {
    int ihalf = (imin + imax) >> 1;
    if(value > array[ihalf])
    {
      imin = ihalf;
    }
    else
    {
      imax = ihalf;
    }
  }

  if(mode == MODE_LINEAR)
  {
    *fraction = (value - array[imin]) / (array[imax] - array[imin]);
  }
  else if(mode == MODE_LOGARITHMIC)
  {
    *fraction = (log(value) - log(array[imin])) / (log(array[imax]) - log(array[imin]));
  }
  else
  {
    mabort(FAILURE, "Unknown interpolation mode %i\n", mode);
  }

  *index = imin;

  return 0;
}
