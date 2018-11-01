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

int mcrt_iterations (void)
{
  int i;
  double xi;
  double avg_n_scat;
  struct timespec mcrt_start;
  Photon *p;

  int n_scat = 0;

  TRANS_FUDGE = 1e-5 * (geo.x_max / geo.nx_cells);

  #ifdef MPI_ON
    int mpi_n_scat;
  #endif

  Log (" - Beginning MCRT iterations\n");

  #ifdef MPI_ON
    if (mpi_proc == MASTER_MPI_PROC)
  #endif

  mcrt_start = get_time ();

  for (i = 0; i < N_PHOTONS; i++)
  {
    p = &phot_main[i];

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
        define_photon (p, p->n);  // re-emit a new photon

    }
    
    if (i % PROGRESS_OUT_FREQ == 0 && i != 0)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i,
           (double) N_PHOTONS, (double) i / N_PHOTONS * 100);
    else if (i == N_PHOTONS - 1)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i,
           (double) N_PHOTONS, (double) i / N_PHOTONS * 100);
  }

  #ifdef MPI_ON
    /*
     * Use MPI_Barrier and MPI_Reduce to find the total number of scatters
     * across all MPI processes
     *
     * TODO: shouldn't need the barrier.. delete?
     */

    MPI_Barrier (MPI_COMM);
    Log_verbose ("MPI OP: collecting n_scat from %i MPI processes\n",
                  n_mpi_processes);
    MPI_Reduce (&n_scat, &mpi_n_scat, 1, MPI_INT, MPI_SUM, MASTER_MPI_PROC,
                MPI_COMM);
    n_scat = mpi_n_scat;
    avg_n_scat = (double) n_scat / n_photons_og;
  #else
    avg_n_scat = (double) n_scat / N_PHOTONS;
  #endif

  #ifdef MPI_ON
    if (mpi_proc == MASTER_MPI_PROC)
  #endif

  print_duration (mcrt_start, " - MCRT iterations completed in");

  Log ("\n--------------------------------------------------------------\n\n");
  Log (" MCRT Summary:\n\n");
  Log (" - Average scatters per photon: %i\n", (int) avg_n_scat);
  
  return SUCCESS;
}
