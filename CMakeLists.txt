cmake_minimum_required(VERSION 3.10)
project(minji C)

set(CMAKE_C_STANDARD 99)
find_package(GSL REQUIRED)

add_executable(minji
        src/functions.h src/main.c src/minji.h src/photon.c
        src/random.c src/input.c src/scatter.c src/time.c
        src/utility.c src/init.c src/trans_phot.c src/grid_set.c
        src/log.c src/parse.c src/log.h)

target_link_libraries(minji GSL::gsl GSL::gslcblas m)
add_definitions(-DMPI_ON)
