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
#define SUCCESS 0
#define FAILURE 1
#define LINE_LEN 256

#include "parameters.h"

#ifdef MPI_ON

  /*
   * Global variables for MPI parallelisation
   */

#include <mpi.h>

#define MPI_COMM MPI_COMM_WORLD
#define MASTER_MPI_PROC 0

typedef struct MPI_Config
{
  int proc;
  int n_procs;
  int tot_n_photons;
} MPI_Config;

MPI_Config mpi;


#endif


typedef struct Config
{
  int verbosity;
  int progress_out_freq;
} Config;

Config config;

/*
 * The available grid types -- note that this code will exploit symmetry
 */

#define PLANE "plane"
#define SPHERICAL "spherical"

enum Errors
{
  MEM_ALLOC_ERROR = 1,
  INVALID_PARAMETER_ERROR,
  INVALID_INPUT_ERROR,
  NOT_IMPLEMENTED_ERROR,
  FILE_OPEN_ERROR,
  FILE_CLOSE_ERROR,
  GSL_RNG_ERROR,
  PAR_FILE_SYNTAX_ERROR,
};

/*
 * The structure to hold various geometry parameters
 */

typedef struct Geometry
{
  char grid_type[LINE_LEN];
  int nx_cells;
  int n_photons;
  double trans_fudge;
  double rad_lum;
  double hx;
  double x_max;
  double s_max_frac;
  double rho_exp;
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

Photon *photon_bank;

typedef struct Grid
{

  double n;
  double x;
  double opac;
  double dens;
} Grid;

Grid *grid;

typedef struct Files
{
  char grid_output[LINE_LEN];
} Files;

Files filenames;

#include "functions.h"
