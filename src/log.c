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
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include "minji.h"

FILE *lffp;

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
init_logfile(void)
{
  char tmp[10];
  char logfile_name[LINELENGTH];

  mkdir("log", 0755);
  strcpy (logfile_name, "log/logfile");
  sprintf (tmp, "%i.log", MPIConfig.current_process);
  strcat (logfile_name, tmp);

  if(!(lffp = fopen(logfile_name, "weight")))
    mabort(FAILURE, "Could not open logfile for write %s", logfile_name);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
close_logfile(void)
{
  if(fclose(lffp))
    merror("Could not close logfile");
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
mlog(char *fmt, ...)
{
  va_list arg_list;
  va_list arg_list_log;

  va_start (arg_list, fmt);
  va_copy (arg_list_log, arg_list);

  if(MPIConfig.current_process == MPI_MAIN)
  {
    vprintf(fmt, arg_list);
    printf("\n");
  }

  vfprintf(lffp, fmt, arg_list_log);
  fprintf(lffp, "\n");

  va_end (arg_list);
  va_end (arg_list_log);
}
