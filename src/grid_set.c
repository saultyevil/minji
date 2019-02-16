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


void
get_grid_params (void)
{
  get_int (N_CELLS_STR, &geo.nx_cells);
  if (geo.nx_cells <= 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for nx_cells: nx_cells > 0\n");

  get_double (X_MAX_STR, &geo.x_max);
  if (geo.x_max < 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for x_max: x_max >= 0");

  get_double (TAU_MAX_STR, &geo.tau_max);
  if (geo.tau_max < 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for tau_max: tau_max >= 0\n");

  get_double (RHO_EXP_STR, &geo.rho_exp);

  geo.hx = geo.x_max / geo.nx_cells;
}

void
allocate_1d_grid (void)
{
  long mem_req;

  mem_req = geo.nx_cells * sizeof (*grid);

  if (!(grid = calloc (geo.nx_cells, sizeof (*grid))))
    Exit (MEM_ALLOC_ERROR, "Could not allocate memory for grid of size %li\n", mem_req);

  Log ("\t\t- Allocated %1.2e bytes for %1.2e grid cells\n", (double) mem_req, (double) geo.nx_cells);
}

void
init_grid (void)
{
  int i;
  double tau_escape;

  get_grid_params ();
  allocate_1d_grid ();

  Log_verbose ("\t\t- Creating location of grid points\n");
  for (i = 0; i < geo.nx_cells; i++)
  {
    grid[i].n = i;
    grid[i].x = (i + 1) * geo.hx;
  }

  tau_escape = 0.0;
  Log_verbose ("\t\t- Creating opacity and density grid\n");
  for (i = 0; i < geo.nx_cells; i++)
  {
    if (!(strcmp (geo.grid_type, PLANE)))
    {
      grid[i].dens = 1.0;
      grid[i].opac = geo.tau_max / geo.nx_cells;  // TODO: non-uniform density
      tau_escape += grid[i].opac * grid[i].dens;
    }
    else if (!(strcmp (geo.grid_type, SPHERICAL)))
    {
      Exit (NOT_IMPLEMENTED_ERROR, "1d spherical grid isn't implemented yet\n");
    }
  }
  Log ("\t\t- Optical depth to escape = %f\n", tau_escape);
  Log ("\t\t- Writing grid to file\n");
  write_grid_to_file (filenames.grid_output);
}
