/* ************************************************************************** */
/**
* @file    minji.h
* @author  Edward Parkinson
* @brief   The main header file for the program.
*
* @details
*
* *************************************************************************** */

#include <stdbool.h>

#define SUCCESS 0
#define FAILURE 1
#define LINELENGTH 128

#ifdef MPI_ON

#include <mpi.h>

#define MPI_MAIN_COMM MPI_COMM_WORLD
#define MPI_MAIN 0

struct MPIConfigSettings
{
  int nprocesses;
  int nphotons;
  int current_process;
} MPIConfig;
#endif

// Structure to contain the global geometry configuration
struct GeometrySettings
{
  int ncells;
  int nphotons;
  double rmax;
  double mass_density_bottom;
  double mass_density_exponent;
  double smax_transport_frac;
  double pushthrough_distance;
  double scatter_albedo;

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
  double r;
  double mass_density;
} *GridCells;  // Array for all the grid cells

// Structure to define an individual photon
struct Photon
{
  bool in_grid;
  int n;
  int icell;
  double x, y, z;
  double nx, ny, nz;
  double w, w0;
} *Photons;  // Array for all the photons
