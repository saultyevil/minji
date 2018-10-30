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

int print_time (void)
{
  char *c_time_string;
  time_t current_time;
  
  current_time = time (NULL);
  c_time_string = ctime (&current_time);
  
  Log ("Current time: %s", c_time_string);
  
  return SUCCESS;
}

struct timespec get_time (void)
{
  struct timespec time;

  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &time);

  return time;
}

int print_duration (struct timespec start_time, char *message)
{
  double td;
  struct timespec end_time;

  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &end_time);
  td = (end_time.tv_sec - start_time.tv_sec) +
    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
  Log ("%s ", message);
  Log ("%f seconds\n", td);

  return SUCCESS;
}
