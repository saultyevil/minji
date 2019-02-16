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

#include <string.h>

#include "minji.h"

void
init_geo (void)
{

  double out_freq = config.progress_out_freq;

  get_double (OUTPUT_FREQ_STR, &out_freq);
  if ((config.progress_out_freq = (int) out_freq) < 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for output_freq: output_freq > 0\n");

  get_double (SCATTER_ALBEO_STR, &geo.scat_albedo);
  if (geo.scat_albedo < 0)
    Exit (INVALID_PARAMETER_ERROR, "Invalid value for scat_albedo: scat_albedo > 0\n");

  /*
   * Get the grid and model types sand call the appropriate grid initialisation
   * routine
   */

  get_string (GRID_TYPE_STR, geo.grid_type);
  if (!(strcmp (geo.grid_type, PLANE)) || !(strcmp (geo.grid_type, SPHERICAL)))
  {
    Log ("\t- Initialising grid for 1d %s atmosphere\n", geo.grid_type);
    init_grid ();
  }
  else
  {
    Exit (INVALID_PARAMETER_ERROR, "Invalid choice '%s' for grid_type\n", geo.grid_type);
  }
}
