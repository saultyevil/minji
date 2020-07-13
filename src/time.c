/* ************************************************************************** */
/**
 * @file     time.c
 * @author   Edward Parkinson
 * @brief    Functions for various timing operations.
 *
 * @details
 *
 * ************************************************************************** */

#include <time.h>

#include "minji.h"

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
print_current_time(void)
{
  const time_t current_time = time(NULL);
  const char *const c_time_string = ctime(&current_time);
  mlog("Current time: %s", c_time_string);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
print_time_elapsed(struct timespec start_time, char *message)
{
  struct timespec end_time;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
  const double td = (double) ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
  mlog("%s %f seconds", message, td);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern struct timespec
get_current_time(void)
{
  struct timespec time;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);

  return time;
}
