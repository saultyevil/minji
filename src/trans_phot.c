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

#include "minji.h"

double DELTA;

int trans_phot (Photon *p)
{
  double ds_max_frac;
  double s_max, d_cell;
  double tau_cell, d_move;

  DELTA = 1e-5 * (geo.x_max / geo.nx_cells);

  /*
   * Initialise the photon's current ds/tau to be 0 to indicate that this is
   * a new move. p->tau_scat is the optical depth a photon will encounter before
   * it is scattered
   */

  p->ds = 0;
  p->tau = 0;
  p->tau_scat = random_tau ();

  /*
   * Calculate the total distance, s_max, the photon is required to traverse to
   * escape from the atmosphere. If s_max is very small, we will consider that
   * the photon is already at the edge of the grid and exit
   */

  dist_to_edge (p, &s_max);
  if (s_max < DELTA)
  {
    p->in_grid = FALSE;
    return SUCCESS;
  }

  /*
   * Set the total s_max a photon is allowed to move
   */

  ds_max_frac = geo.s_max_frac * s_max;

  while (p->tau < p->tau_scat && p->ds < ds_max_frac)
  {
    /*
     * Figure out the distance to the nearest cell wall, then calculate the
     * total optical depth a photon will encounter as it traverses towards the
     * cell wall. Recall that this is given by,
     *      dtau = rho * kappa * ds
     */

    dist_to_cell_wall (p, &d_cell);
    tau_cell = grid[p->icell].opac * grid[p->icell].dens * d_cell;

    /*
     * If the total optical depth PLUS the optical depth experience by the
     * photon is more than the optical depth to the next scattering event,
     * then the photon is moved a distance given by tau_cell. The while loop
     * will then break. Otherwise, the photon does not scatter in the current
     * cell, hence the photon will be moved to the edge of the cell and the
     * while loop will iterate again.
     */

    if ((p->tau + tau_cell) >= p->tau_scat)
      d_move = (p->tau_scat - p->tau) /
                                    (grid[p->icell].opac * grid[p->icell].dens);
    else
      d_move = d_cell;

    /*
     * The running totals for optical depth and ds moved are now incremented
     * and the position of the photon is updated
     */

    p->ds += d_move;
    p->tau += tau_cell;
    traverse_phot_ds (p, d_move);
  }

  /*
   * If the photon has moved greater than the allowed s_max, then the photon is
   * no longer within the atmosphere, hence p->in_grid is switched to FALSE to
   * indicate this. Otherwise, the photon is still within the atmosphere hence
   * the photon's position is updated
   */

  if (p->ds >= ds_max_frac)
    p->in_grid = FALSE;
  else
    traverse_phot_ds (p, d_move);

  return SUCCESS;
}

// We only care about it traversing in one direction as it is 1d
int dist_to_edge (Photon *p, double *s_max)
{
  if (p->nx > 0)
    *s_max = (geo.x_max - p->x) / p->nx;
  else if (p->nx < 0)
    *s_max = -p->x / p->nx;
  else
    *s_max = 100 * geo.x_max;

  return SUCCESS;
}

/*
 * If the distance to the next cell wall is small, then we will consider the
 * photon to be in the next cell wall, move it into the next cell and then
 * calculate dx for the new cell
 */

int dist_to_cell_wall (Photon *p, double *d_cell)
{
  double dx;

  if (p->nx > 0)
  {
    dx = (grid[p->icell].x - p->x) / p->nx;
    if (dx < DELTA)
    {
      p->x = grid[p->icell].x;
      p->icell += 1;
      dx = (grid[p->icell].x - p->x) / p->nx;
    }
  }
  else if (p->nx < 0)
  {
    dx = (grid[p->icell - 1].x - p->x) / p->nx;
    if (dx < DELTA)
    {
      p->x = grid[p->icell - 1].x;
      p->icell -= 1;
      dx =(grid[p->icell - 1].x - p->x) / p->nx;
    }
  }
  else
    dx = 100 * geo.x_max;

  if (dx <= 0)
    Log_error ("trans_phot: p %i: dx <= 0 (dx = %f)\n", p->n, dx);

  *d_cell = dx;

  return SUCCESS;
}
