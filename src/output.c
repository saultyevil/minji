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

#include <stdio.h>

#include "minji.h"

void
write_grid_to_file (char *filename)
{
  int i;
  FILE *outgrid;

  if ((outgrid = fopen (filename, "w")) == NULL)
    Exit (FILE_OPEN_ERROR, "Can't open file to write: %s\n", filename);

  fprintf (outgrid, "# n_cell x_coord density opacity\n");
  for (i = 0; i < geo.nx_cells; i++)
    fprintf (outgrid, "%+i %+e %+e %+e\n", grid[i].n, grid[i].x, grid[i].dens, grid[i].opac);

  if (fclose (outgrid))
    Exit (FILE_CLOSE_ERROR, "Can't close file %s\n", filename);
}
