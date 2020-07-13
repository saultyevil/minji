/* ************************************************************************** */
/**
* @file    minji.h
* @author  Edward Parkinson
* @brief   The main header file for the program.
*
* @details
*
* *************************************************************************** */

#include <time.h>
#include <stdbool.h>

#include "constants.h"
#include "log.h"
#include "algebra.h"

#define SUCCESS 0
#define FAILURE 1
#define LINELENGTH 128
#define PHOTON_OUTSIDE_GRID -1
#define NGHOSTCELLS 2

#ifdef MPI_ON
#include <mpi.h>
#define MPI_MAIN_COMM MPI_COMM_WORLD
#endif

#define MPI_MAIN 0

struct MPIConfigSettings
{
  int nphotons;
  int nprocesses;
  int current_process;
} MPIConfig;

// Structure to contain the global geometry configuration
struct GeometrySettings
{
  int ncells;
  int nphotons;
  double rmin, rmax;
  double mass_initial;
  double density_exponent;
  double pushthrough_distance;
  double scatter_albedo;
  double *xpoints;
  double *ypoints;
  double *zpoints;

  enum GridType
  {
    GRID_LINEAR,
    GRID_LOGARITHMIC
  } grid_type;

} Geometry;

// Structure to define an individual grid cell
struct GridCell
{
  int n;
  double xyz[3];
  double xyz_cen[3];
  double mdensity;
} *GridCells;  // Array for all the grid cells

// Structure to define an individual photon
struct Photon
{
  bool in_grid;
  int n;
  int grid;
  int nscat;
  double xyz[3];
  double ijk[3];
  double weight;
} *Photons;  // Array for all the photons

#include "functions.h"
