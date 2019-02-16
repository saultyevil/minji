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
clean_up (void)
{
  close_logfile ();
  close_parameter_file ();
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
