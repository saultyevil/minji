/* ************************************************************************** */
/**
* @file    main.c
* @author  Edward Parkinson
* @brief   Contains the main function of the program.
*
* @details
*
* *************************************************************************** */

#include <time.h>

#include "minji.h"
#include "fmt.h"
#include "functions.h"

/* ************************************************************************** */
/**
* @brief   The main function of the program.
*
* @details
*
* *************************************************************************** */

int
main(int argc, char **argv)
{
#ifdef MPI_ON
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_MAIN_COMM, &MPIConfig.current_process);
  MPI_Comm_size(MPI_MAIN_COMM, &MPIConfig.nprocesses);
#endif

  init_logfile();
  struct timespec start_time = get_current_time();
  print_current_time();
  mlog("\n%s\n\n", FMT_SEPARATOR);

  char *parameter_file_path;
  parameter_file_path = get_command_line_arguments(argc, argv);
  open_parameter_file(parameter_file_path);

  /*
   * Begin the process of initialising all of the simulation components such
   * as the photons and the the density grid
   */

  mlog("Beginning initialisation routines\n");
  init_minji();
  init_grid();
  init_photons();

  transport_photons();

  /*
   * Indicate the end of the simulation and clean up
   */

  mlog("\n%s\n\n", FMT_SEPARATOR);
  print_time_elapsed(start_time, "Simulation completed in: ");
  clean_up();

#ifdef MPI_ON
  MPI_Finalize();
#endif

  return SUCCESS;
}
