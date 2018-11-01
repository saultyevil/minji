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
#include <string.h>
#include <stdlib.h>

#include "minji.h"

int init_grid (void)
{
  int i;

  int write_grid = FALSE;
  double tau_escape = 0.0;

  get_grid_params ();
  allocate_1d_grid ();

  Log_verbose ("\t\t- Creating location of grid points\n");

  for (i = 0; i < geo.nx_cells; i++)
  {
    grid[i].n = i;
    grid[i].x = (i + 1) * geo.hx;
  }

  Log_verbose ("\t\t- Creating opacity and density grid\n");
  Log ("\t\t- WIP: setting only a uniform grid structure for now\n");

  for (i = 0; i < geo.nx_cells; i++)
  {
    if (!(strcmp (geo.geo_type, PLANAR)))
    {
      grid[i].dens = 1.0;
      grid[i].opac = geo.tau_max / geo.nx_cells;
      tau_escape += grid[i].opac * grid[i].dens;
    }
    else if (!(strcmp (geo.geo_type, SPHERICAL)))
    {
      Exit (666, "1d spherical grid isn't implemented properly yet!\n");
    }
  }

  Log ("\t\t- Optical depth to escape = %f\n", tau_escape);

  get_optional_int ("write_grid", &write_grid);
  if (write_grid != FALSE && write_grid != TRUE)
    Log_error ("Invalid value for write_grid: write_grid is either 0 or 1\n");
  if (write_grid)
  {
    Log ("\t\t- Writing grid to file\n");
    write_grid_to_file ("opacity.txt");
  }
  return SUCCESS;
}

int get_grid_params (void)
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
  get_double ("rho_exp", &geo.rho_exp);

  geo.hx = geo.x_max / geo.nx_cells;

  return SUCCESS;
}

int allocate_1d_grid (void)
{
  long mem_req;

  mem_req = geo.nx_cells * sizeof (*grid);

  if (!(grid = calloc (geo.nx_cells, sizeof (*grid))))
    Exit (3, "Could not allocate memory for grid of size %li\n", mem_req);

  Log ("\t\t- Allocated %1.2e bytes for %1.2e grid cells\n", (double) mem_req,
       (double) geo.nx_cells);

  return SUCCESS;
}
