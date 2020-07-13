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

extern void
write_grid_to_file(void)
{
  FILE *f = fopen("log/minji.grid.txt", "w");
  fprintf(f, "%-12s %-12s %-12s %-12s %-12s \n", "n", "x", "y", "z", "mdensity");
  for(int i = 0; i < Geometry.ncells; ++i)
  {
    fprintf(f, "%-12i %-12e %-12e %-12e %-12e\n", i, GridCells[i].xyz[0], GridCells[i].xyz[1], GridCells[i].xyz[2],
            GridCells[i].mdensity);
  }
  if(fclose(f))
    merror("Unable to close grid output file for some reason");
}
