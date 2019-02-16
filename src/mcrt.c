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

#include <time.h>
#include <stdio.h>

#include "minji.h"

int
mcrt_iterations (void)
{
  int i;
  double xi;
  double avg_n_scat;
  struct timespec mcrt_start;
  Photon *p;

  int n_scat = 0;

  geo.trans_fudge = 1e-5 * (geo.x_max / geo.nx_cells);

#ifdef MPI_ON
  int mpi_n_scat;
#endif

  Log (" - Beginning MCRT iterations\n");

#ifdef MPI_ON
  if (mpi.proc == MASTER_MPI_PROC)
#endif

    mcrt_start = get_time ();

  for (i = 0; i < geo.n_photons; i++)
  {
    p = &photon_bank[i];

    trans_phot (p);

    while (p->in_grid == TRUE)
    {
      xi = gsl_rand_num (0, 1);
      if (xi < geo.scat_albedo)
      {
        scatter_phot (p);
        n_scat += 1;
      }

      trans_phot (p);

      if (p->x < 0)
        define_photon (p, p->n);        // re-emit a new photon

    }

    if (i % config.progress_out_freq == 0 && i != 0)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i, (double) geo.n_photons, (double) i / geo.n_photons * 100);
    else if (i == geo.n_photons - 1)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i, (double) geo.n_photons, (double) i / geo.n_photons * 100);
  }

#ifdef MPI_ON
  Log_verbose ("MPI OP: collecting n_scat from %i MPI processes\n", mpi.n_procs);
  MPI_Reduce (&n_scat, &mpi_n_scat, 1, MPI_INT, MPI_SUM, MASTER_MPI_PROC, MPI_COMM);
  n_scat = mpi_n_scat;
  avg_n_scat = (double) n_scat / mpi.tot_n_photons;
#else
  avg_n_scat = (double) n_scat / geo.n_photons;
#endif

#ifdef MPI_ON
  if (mpi.proc == MASTER_MPI_PROC)
#endif

    print_duration (mcrt_start, " - MCRT iterations completed in");

  Log ("\n--------------------------------------------------------------\n\n");
  Log (" MCRT Summary:\n\n");
  Log (" - Average scatters per photon: %i\n", (int) avg_n_scat);

  return SUCCESS;
}
