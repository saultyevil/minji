/* ************************************************************************** */
/**
* @file    spherical.c
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
spherical_ds_to_cell_edge(const struct Photon p)
{
  double s_edge_left = ds_to_sphere(Geometry.xpoints[p.grid], p);
  double s_edge_right = ds_to_sphere(Geometry.xpoints[p.grid + 1], p);

  if(s_edge_left == LARGE_NUMBER && s_edge_right == LARGE_NUMBER)
  {
    merror("could not find transport solution for photon %i in grid %i to nearest spherical wall", p.n, p.grid);
    return Geometry.pushthrough_distance;
  }

  double s_edge = s_edge_right;
  if(s_edge < s_edge_left)
  {
    s_edge = s_edge_right;
  }

  s_edge += Geometry.pushthrough_distance;

  if(s_edge <= 0)
    merror("distance to spherical cell edge %e < 0\n", s_edge);

  return s_edge;
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern int
spherical_where_in_grid(const double *xyz)
{
  double position = vector_magnitude(xyz);

  /*
   * Vague checks to ensure the position is within the grid
   */

  if(position > Geometry.xpoints[Geometry.ncells] || position < Geometry.xpoints[0])
    return PHOTON_OUTSIDE_GRID;

  /*
   * Find which cell position belongs in by using the linear interpolation function
   * to return the index
   */

  double fraction;
  int gridcell = -5;
  linear_interpolation(MODE_LINEAR, position, Geometry.xpoints, Geometry.ncells + NGHOSTCELLS, &gridcell, &fraction);

  return gridcell;
}
