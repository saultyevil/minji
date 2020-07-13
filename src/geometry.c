/* ************************************************************************** */
/**
* @file    geometry.c
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include "minji.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern double
ds_to_sphere(const double radius, const struct Photon p)
{
  double a = 1;
  double b = 2 * dot_product(p.xyz, p.ijk);
  double c = dot_product(p.xyz, p.xyz) - radius * radius;

  double solution;
  int check = solve_quadratic(a, b, c, &solution);

  if(check == FAILURE)
    return LARGE_NUMBER;

  return solution;
}
