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
#include <stdlib.h>
#include <stdarg.h>

#include "minji.h"


void
init_logfile (void)
{

};

void
close_logfile (void)
{

}

void
Log (char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
#ifdef MPI_ON
  if (mpi.proc == MASTER_MPI_PROC)
#endif
    vprintf (fmt, arg_list);
  va_end (arg_list);
}

void
Log_parallel (char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
  vprintf (fmt, arg_list);
  va_end (arg_list);
}

void
Log_verbose (char *fmt, ...)
{
  if (config.verbosity == TRUE)
  {
    va_list arg_list;

    va_start (arg_list, fmt);
#ifdef MPI_ON
    if (mpi.proc == MASTER_MPI_PROC)
#endif
      vprintf (fmt, arg_list);
    va_end (arg_list);
  }
}

void
Log_error (char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
#ifdef MPI_ON
  printf ("PROC %i ", mpi.proc);
#endif
  printf ("ERROR: ");
  vprintf (fmt, arg_list);
  va_end (arg_list);
}

void
Exit (int error_code, char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);

  printf ("\n--------------------------------------------------------------\n\n");
  printf ("\tERROR: ");
  vprintf (fmt, arg_list);
  printf ("\t       Exiting with error code %i\n", error_code);
  printf ("\n--------------------------------------------------------------\n");

  va_end (arg_list);

  #if MPI_ON
  MPI_Abort (MPI_COMM, error_code);
  MPI_Finalize ();
  exit (error_code);
  #else
  exit (error_code);
  #endif
}
