/* ************************************************************************** */
/**
* @file    grid_set.c
* @author  Edward Parkinson
* @brief   Contains the functions for initializing the simulation grid.
*
* @details
*
* *************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "minji.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

static void
grid_get_parameters(void)
{
  // Number of grid cells
  read_integer("Geometry.ncells", &Geometry.ncells);
  if(Geometry.ncells <= 0)
    mabort(FAILURE, "Invalid value for nx_cells: nx_cells > 0\n");

  // Spherical extent of the simulation grid
  read_double("Geometry.rmax(m)", &Geometry.rmax);
  if(Geometry.rmax <= 0)
    mabort(FAILURE, "Invalid value for rmax --> rmax > 0");

  // Mass density of the grid
  read_double("Geometry.mass_density_exponent", &Geometry.mass_density_exponent);
  read_double("Geometry.mass_density_base(kg/m3)", &Geometry.mass_density_bottom);
  if(Geometry.mass_density_bottom <= 0)
    mabort(FAILURE, "Invalid value for mass_density_bottom --> mass_density_bottom > 0");
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

static void
grid_malloc(void)
{
  const int NGHOST = 2;
  const long memory_requirement = Geometry.ncells * (long) sizeof(struct GridCell);
  GridCells = calloc(Geometry.ncells + NGHOST, sizeof(struct GridCell));
  if(!GridCells)
  {
    mabort(FAILURE, "Unable to allocate %d bytes for simulation grid of %d", memory_requirement, Geometry.ncells);
  }
  else  // else is used here to avoid compiler warnings
  {
    mlog("Allocated %1.2e bytes for %1.2e grid cells\n", (double) memory_requirement, (double) Geometry.ncells);
  }
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
init_grid(void)
{
  grid_get_parameters();
  grid_malloc();

  double dr;
  if(Geometry.grid_type == GRID_LINEAR)
  {
    dr = Geometry.rmax / Geometry.ncells;
    mlog("Using linear grid spacing with dr %e\n", dr);
  }
  else if(Geometry.grid_type == GRID_LOGARITHMIC)
  {
    mlog("Using logarithmic grid spacing\n");
  }
  else
  {
    mabort(FAILURE, "Unknown grid type %d\n", Geometry.grid_type);
  }

  for(int i = 0; i < Geometry.ncells; ++i)
  {
    if(Geometry.grid_type == GRID_LOGARITHMIC)
    {
      dr = 1.0;
    }

    GridCells[i].n = i;
    GridCells[i].r = i * dr;
  }
}
