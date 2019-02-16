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

int
init_default_pars (void)
{
  /*
   * Initialise the general parameters for MCRT iterations
   */

  geo.n_photons = (int) 1e6;
  geo.rad_lum = geo.n_photons;
  config.progress_out_freq = (int) 1e5;

  /*
   * Initialise the geo pars to be a small planar atmosphere
   */

  strcpy (geo.grid_type, PLANE);
  geo.nx_cells = 100;
  geo.x_max = 1.0;
  geo.tau_max = 10.0;
  geo.scat_albedo = 1.0;
  geo.s_max_frac = 0.999;
  geo.rho_exp = -2.0;

  // TODO: find a better place to put this
  get_optional_double (SMAX_MAX_STR, &geo.s_max_frac);

  /*
   * Initialise filenames
   */

  strcpy (filenames.grid_output, "grid.out");


  return SUCCESS;
}
