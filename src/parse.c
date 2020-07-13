/* ************************************************************************** */
/**
* @file    parse.c
* @author  Edward Parkinson
* @brief   Contains functions for parsing from the command line.
*
* @details
*
* *************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "minji.h"

/* ************************************************************************** */
/**
 * @brief  Process the command line arguments passed to the program.
 *
 * @param[in]  argc  The number of command line arguments
 * @param[in]  argv  The command line arguments
 * @return     The name of the parameter file
 *
 * @details
 *
 * - If no arguments to the program are provided, the user will be prompted
 *    to input a file path to find the parameter file and then parameters
 *    will be read in from the file.
 * - If 1 argument is provided, the program will attempt to load parameters
 *    from the provided file path from the argument list.
 * - If more than 1 argument is provided, the program will exit.
 *
 * ************************************************************************** */

extern char *
get_command_line_arguments(int argc, char **argv)
{
  char *parameter_file_path = malloc(LINELENGTH);

  if(!parameter_file_path)
    mabort(FAILURE, "Unable to allocate memory to store parameter file");

  if(argc == 1)
  {
    query_for_parameter_file(parameter_file_path);
  }
  else if(argc == 2)
  {
    strcpy(parameter_file_path, argv[1]);
  }
  else
  {
    mabort(FAILURE, "Too many arguments provided");
  }

  return parameter_file_path;
}
