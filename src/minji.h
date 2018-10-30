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

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LINE_LEN 256

#ifdef MPI_ON

  /*
   * Global variables for MPI parallelisation
   */

  #include <mpi.h>
 
  #define MPI_COMM MPI_COMM_WORLD
  #define MASTER_MPI_PROC 0
  
  int mpi_proc;
  int n_mpi_processes;
  
#endif

/*
 * Global variables
 */

int N_PHOTONS;
int VERBOSITY;
int PROGRESS_OUT_FREQ;
double RAD_LUM;

/*
 * The available grid types -- note that this code will exploit symmetry
 */

#define PLANAR "planar"
#define SPHERICAL "spherical"

/*
 * The structure to hold various geometry parameters
 */

typedef struct Geometry
{
  char geo_type[LINE_LEN];
  int nx_cells;
  double hx;
  double x_max;
  double s_max_frac;
  double tau_max;
  double scat_albedo;
} Geometry;

Geometry geo;

typedef struct Photon
{
  int n;
  int in_grid;
  int icell;
  double ds;
  double x, y, z;
  double nx, ny, nz;
  double tau, tau_scat;
  double w, w_0;
} Photon;

Photon *phot_main;

typedef struct Grid
{
  double n;
  double x;
  double opac;
  double dens;
} Grid;

Grid *grid;

#include "functions.h"
