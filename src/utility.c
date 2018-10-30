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


void Exit (int error_code, char *fmt, ...)
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
  #else
    exit (error_code);
  #endif
}

int Log (char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
  #ifdef MPI_ON
    if (mpi_proc == MASTER_MPI_PROC)
  #endif
  vprintf (fmt, arg_list);
  va_end (arg_list);
  
  return SUCCESS;
}

int Log_parallel (char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
  vprintf (fmt, arg_list);
  va_end (arg_list);
  
  return SUCCESS;
}

int Log_verbose (char *fmt, ...)
{
  if (VERBOSITY == TRUE)
  {
    va_list arg_list;
    
    va_start (arg_list, fmt);
    #ifdef MPI_ON
      if (mpi_proc == MASTER_MPI_PROC)
    #endif
    vprintf (fmt, arg_list);
    va_end (arg_list);
  
    return SUCCESS;
  }
  else
    return SUCCESS;
}

int Log_error (char *fmt, ...)
{
  va_list arg_list;
  
  va_start (arg_list, fmt);
  #ifdef MPI_ON
    printf ("PROC %i ", mpi_proc);
  #endif
  printf ("ERROR: ");
  vprintf (fmt, arg_list);
  va_end (arg_list);
  
  return SUCCESS;
}

double min_double (int n, ...)
{
  int i;
  double num, min;
  va_list nums;

  va_start (nums, n);

  min = va_arg (nums, double);
  for (i = 1; i < n; i++)
  {
    num = va_arg (nums, double);
    if (num < min)
      min = num;
  }

  va_end (nums);

  return min;
}
