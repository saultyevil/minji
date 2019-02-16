cmake_minimum_required(VERSION 3.10)
project(minji C)

set(CMAKE_C_STANDARD 99)
find_package(GSL REQUIRED)

add_executable(minji
        src/functions.h src/main.c src/mcrt.c src/minji.h src/photon.c
        src/random.c src/read_pars.c src/scatter.c src/setup.c src/time.c
        src/utility.c src/default_pars.c src/trans_phot.c src/grid_set.c
        src/output.c src/parameters.h)

target_link_libraries(minji GSL::gsl GSL::gslcblas m)
add_definitions(-DMPI_ON)
