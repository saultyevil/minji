/* ************************************************************************** */
/**
* @file
* @author  Edward Parkinson
* @brief
*
* @details
*
* *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "minji.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
clean_up(void)
{
  free(GridCells);
  close_logfile();
  close_parameter_file();
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
mabort(const int error_code, char *fmt, ...)
{
  va_list arg_list;

  va_start (arg_list, fmt);
  printf("\tERROR: ");
  vprintf(fmt, arg_list);
  printf("\t       Exiting with error code %i\n", error_code);
  va_end(arg_list);

#if MPI_ON
  MPI_Abort(MPI_MAIN_COMM, error_code);
#else
  exit(error_code);
#endif
}
