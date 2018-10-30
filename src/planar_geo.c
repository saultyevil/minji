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

#include <stdlib.h>

#include "minji.h"

int init_planar_geo (void)
{
  int i;

  get_planar_params ();
  allocate_planar_grid ();

  for (i = 0; i < geo.nx_cells; i++)
  {
    grid[i].n = i;
    grid[i].x = (i + 1) * geo.hx;
    grid[i].dens = 1.0;
    grid[i].opac = 1.0;
  }

  return SUCCESS;
}

int get_planar_params (void)
{
  get_int ("nx_cells", &geo.nx_cells);
  if (geo.nx_cells <= 0)
    Exit (2, "Invalid value for nx_cells: nx_cells > 0\n");
  get_double ("x_max", &geo.x_max);
  if (geo.x_max < 0)
    Exit (2, "Invalid value for x_max: x_max >= 0");
  get_double ("tau_max", &geo.tau_max);
  if (geo.tau_max < 0)
    Exit (2, "Invalid value for tau_max: tau_max >= 0\n");

  geo.hx = geo.x_max / geo.nx_cells;

  return SUCCESS;
}

int allocate_planar_grid (void)
{
  long mem_req;

  mem_req = geo.nx_cells * sizeof (*grid);

  if (!(grid = calloc (geo.nx_cells, sizeof (*grid))))
    Exit (3, "Could not allocate memory for grid of size %li\n", mem_req);

  Log ("\t\t- Allocated %1.2e bytes for %1.2e grid cells\n", (double) mem_req,
       (double) geo.nx_cells);

  return SUCCESS;
}
