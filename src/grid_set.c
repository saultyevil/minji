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
    mabort(FAILURE, "Invalid value for nx_cells: nx_cells > 0");

  // Spherical extent of the simulation grid
  read_double("Geometry.rmax(m)", &Geometry.rmax);
  read_double("Geometry.rmin(m)", &Geometry.rmin);
  if(Geometry.rmax <= 0 || Geometry.rmax < Geometry.rmin)
    mabort(FAILURE, "Invalid value for rmax --> rmax > 0 and rmax > rmin");
  if(Geometry.rmin < 0 || Geometry.rmin > Geometry.rmax)
    mabort(FAILURE, "Invalid value for rmin --> rmin >= 0 and rmin < rmax");

  // Mass density of the grid
  read_double("Geometry.density_exponent", &Geometry.density_exponent);
  read_double("Geometry.mass_density_base(kg/m3)", &Geometry.mass_initial);
  if(Geometry.mass_initial <= 0)
    mabort(FAILURE, "Invalid value for mass_initial --> mass_initial > 0");
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
  // Allocate memory for the simulation grid
  const long memory_requirement = Geometry.ncells * (long) sizeof(struct GridCell);
  GridCells = calloc(Geometry.ncells + NGHOSTCELLS, sizeof(struct GridCell));

  if(!GridCells)
    mabort(FAILURE, "Unable to allocate %d bytes for simulation grid of %d", memory_requirement, Geometry.ncells);

  mlog("Allocated %1.2e bytes for %1.2e grid cells", (double) memory_requirement, (double) Geometry.ncells);

  // Allocate memory for the arrays storing the x, y, z coordinates
  Geometry.xpoints = calloc(Geometry.ncells + NGHOSTCELLS, sizeof(*Geometry.xpoints));
  if(!Geometry.xpoints)
    mabort(FAILURE, "Unable to allocate memory for internal x points cooridates array");

  Geometry.ypoints = calloc(Geometry.ncells + NGHOSTCELLS, sizeof(*Geometry.ypoints));
  if(!Geometry.ypoints)
    mabort(FAILURE, "Unable to allocate memory for internal y points cooridates array");

  Geometry.zpoints = calloc(Geometry.ncells + NGHOSTCELLS, sizeof(*Geometry.zpoints));
  if(!Geometry.zpoints)
    mabort(FAILURE, "Unable to allocate memory for internal z points cooridates array");
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
    mlog("Using linear grid spacing");
    dr = (Geometry.rmax - Geometry.rmin) / (Geometry.ncells);
  }
  else if(Geometry.grid_type == GRID_LOGARITHMIC)
  {
    mlog("Using logarithmic grid spacing");
    dr = log10(Geometry.rmax / Geometry.rmin) / (Geometry.ncells);
  }
  else
  {
    mabort(FAILURE, "Unknown grid type %d", Geometry.grid_type);
  }

  for(int i = 0; i < Geometry.ncells + NGHOSTCELLS; ++i)
  {

    GridCells[i].n = i;

    double r;
    double rcen;

    if(Geometry.grid_type == GRID_LINEAR)
    {
      r = Geometry.rmin + dr * i;
      rcen = r + 0.5 * dr;
    }
    else if(Geometry.grid_type == GRID_LOGARITHMIC)
    {
      r = Geometry.rmin * pow(10, dr * (i - 1));
      rcen = 0.5 * Geometry.rmin * (pow(10, dr * i) + pow(10, dr * (i - 1)));
    }
    else
    {
      mabort(FAILURE, "Unknown grid type %d", Geometry.grid_type);
    }

    const double spherical_angle = 0.5 * M_PI;
    GridCells[i].xyz[1] = GridCells[i].xyz_cen[1] = 0;
    GridCells[i].xyz[0] = GridCells[i].xyz[2] = r * sin(spherical_angle);
    GridCells[i].xyz_cen[0] = GridCells[i].xyz_cen[2] = rcen * sin(spherical_angle);
    GridCells[i].mdensity = Geometry.mass_initial * pow(dot_product(GridCells[i].xyz_cen, GridCells[i].xyz_cen), Geometry.density_exponent);

    // Record coordindates for later use
    Geometry.xpoints[i] = GridCells[i].xyz[0];
    Geometry.ypoints[i] = GridCells[i].xyz[1];
    Geometry.zpoints[i] = GridCells[i].xyz[2];
  }

  double delta_boundary = Geometry.rmax - Geometry.rmin;

  if(delta_boundary < 1e8)
  {
    Geometry.pushthrough_distance = delta_boundary / 1e3;
  }
  else if(delta_boundary < 1e15)
  {
    Geometry.pushthrough_distance = 1e15;
  }
  else
  {
    Geometry.pushthrough_distance = Geometry.rmax / 1e10;
  }

  write_grid_to_file();
}
