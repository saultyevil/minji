# Minji - an MCRT sandbox code 

## Purpose

The purpose of this program is to act as a "sandbox"  which will be used to test
various MCRT acceleration techniques or other more general MCRT methods in a 
safe, pleasant, spherically symmetric environment.


## Requirement

The [GNU Science Library](https://www.gnu.org/software/gsl/) is required. It is 
also recommended to having an MPI library installed, such as 
[OpenMPI](https://www.open-mpi.org/), as this can provide significant speed up.
Although, it's not really required as a 1D code shouldn't take long to run, 
unless the model is very optically thick.

## Building

Currently, the code can be built using the provided Makefile. By default, 
the Makefile uses OpenMPI's default C compiler `mpicc` with the compiler flag
`-DMPI_ON` to enable parallel computation using MPI. 

If you do not want to use MPI, the CC flag will require updating and the 
additional `-DMPI_ON` flag will need to be removed.

```bash
$ make minji
```

Once built, the executable is stored in the `bin` directory. It is recommended 
that you add this directory to you `PATH` variable.

## Usage

To execute a simulation, a parameter file is required to be provided as a 
command line argument, e.g., 

```bash
$ minji plane.par
```

Example parameter files can be found in the `examples` directory.

## Acknowledgements 

I would like to acknowledge financial support from the EPSRC Centre for Doctoral
Training in Next Generation Computational Modelleing grant EP/L015382/1.
