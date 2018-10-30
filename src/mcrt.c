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

#include "minji.h"

int mcrt_iterations (void)
{
  int i;
  double xi;
  struct timespec mcrt_start;
  Photon *p;

  int n_scat = 0;
  int proc_start = 0, proc_end = N_PHOTONS;
  
  #ifdef MPI_ON
    int mpi_n_scat;
    int phots_per_proc;
    phots_per_proc = (double) N_PHOTONS / n_mpi_processes;
    proc_start = mpi_proc * phots_per_proc;
    proc_end = (mpi_proc + 1) * phots_per_proc;
  #endif

  Log (" - Beginning MCRT iterations\n");

  #ifdef MPI_OP
    if (mpi_proc == MASTER_MPI_PROC)
  #endif

  mcrt_start = get_time ();

  for (i = proc_start; i < proc_end; i++)
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
    }
    
    if (i % PROGRESS_OUT_FREQ == 0 && i != 0)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i,
           (double) proc_end, (double) i / proc_end * 100);
    else if (i == proc_end - 1)
      Log ("\t- Transported %1.2e out of %1.2e photons (%3.0f%%)\n", (double) i,
           (double) proc_end, (double) i / proc_end * 100);
  }

  #ifdef MPI_ON
    /*
     * Use MPI_Barrier and MPI_Reduce to find the total number of scatters
     * across all MPI processes
     */

    MPI_Barrier (MPI_COMM);
    Log ("MPI OP: collecting n_scat from %i MPI processes\n", n_mpi_processes);
    MPI_Reduce (&n_scat, &mpi_n_scat, 1, MPI_INT, MPI_SUM, MASTER_MPI_PROC,
                MPI_COMM);
    n_scat = mpi_n_scat;
  #endif

  #ifdef MPI_OP
    if (mpi_proc == MASTER_MPI_PROC)
  #endif

  print_duration (mcrt_start, " - MCRT iterations completed in");

  Log ("\n--------------------------------------------------------------\n\n");
  Log (" MCRT Summary:\n\n");
  Log (" - Average scatters per photon: %i\n", n_scat / N_PHOTONS);
  
  return SUCCESS;
}
