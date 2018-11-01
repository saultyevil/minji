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

int init_default_pars (void)
{
  /*
   * Initialise the general parameters for MCRT iterations
   */

  N_PHOTONS = (int) 1e6;
  PROGRESS_OUT_FREQ = (int) 1e5;
  RAD_LUM = 1e6;

  /*
   * Initialise the geo pars to be a small planar atmosphere
   */

  strcpy (geo.geo_type, PLANAR);
  geo.nx_cells = 100;
  geo.x_max = 1.0;
  geo.tau_max = 10.0;
  geo.scat_albedo = 1.0;
  geo.s_max_frac = 0.999;
  geo.rho_exp = -2.0;

  // TODO: find a better place to put this
  get_optional_double ("s_max_frac", &geo.s_max_frac);

  return SUCCESS;
}
