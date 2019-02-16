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
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include "minji.h"


FILE *LOGFILE;
char LOGFILE_NAME[LINE_LEN];

void
init_logfile (void)
{
  char tmp[10];

  mkdir ("log", 0755);
  strcpy (LOGFILE_NAME, "log/logfile");
  sprintf (tmp, "_%i.log", mpi.proc);
  strcat (LOGFILE_NAME, tmp);

  if (!(LOGFILE = fopen (LOGFILE_NAME, "w")))
    Exit (FILE_OPEN_ERROR, "Could not open logfile for write %s\n", LOGFILE_NAME);
}

void
close_logfile (void)
{
  if (fclose (LOGFILE))
    Exit (FILE_CLOSE_ERROR, "Could not close logfile %s\n", LOGFILE_NAME);
}

void
Log (char *fmt, ...)
{
  va_list arg_list, arg_list_log;

  va_start (arg_list, fmt);
  va_copy (arg_list_log, arg_list);

#ifdef MPI_ON
  if (mpi.proc == MASTER_MPI_PROC)
  {
#endif
    vprintf (fmt, arg_list);
    vfprintf (LOGFILE, fmt, arg_list_log);
#ifdef MPI_ON
  }
#endif

  va_end (arg_list);
  va_end (arg_list_log);
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
    va_list arg_list, arg_list_log;

    va_start (arg_list, fmt);
    va_copy (arg_list_log, arg_list);

#ifdef MPI_ON
    if (mpi.proc == MASTER_MPI_PROC)
    {
#endif
    vprintf (fmt, arg_list);
    vfprintf (LOGFILE, fmt, arg_list_log);
#ifdef MPI_ON
    }
#endif
    va_end (arg_list);
    va_end (arg_list_log);
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
