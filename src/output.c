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

  for (i = 0; i < geo.nx_cells; i++)
  {
    fprintf (outgrid, "%f\n", grid[i].opac);
  }

  if (fclose (outgrid))
    Exit (FILE_CLOSE_ERROR, "Can't close file %s\n", filename);
}
