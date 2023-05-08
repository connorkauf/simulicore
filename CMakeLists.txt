cmake_minimum_required(VERSION 3.1.0)

set(project_name "CLA3P")
set(project_version "1.0.0")
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#-----------------------------------------------
# set build type
#-----------------------------------------------
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Release)
message("Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# set project root
#-----------------------------------------------
set(CLA3P_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CLA3P_PROJECT_ROOT}/install")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
set(CLA3P_USE_I64 1)

if(CLA3P_USE_I64)
	add_definitions(-DCLA3P_I64)
endif()

#-----------------------------------------------
# set compiler flags
#-----------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

#-----------------------------------------------
# set 3rd parties
#-----------------------------------------------

#openmp
find_package(OpenMP)
if (OPENMP_FOUND)
	message(STATUS "Configuring OpenMP ${OpenMP_CXX_VERSION}...")
	# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
	message(STATUS "OpenMP not found")
endif()

#-----------------------------------------------

# mkl setup
add_definitions(-DMKL_Complex8=std::complex<float>)
add_definitions(-DMKL_Complex16=std::complex<double>)
include(3rd/cmake.mkl.in)
message(STATUS "MKL INCLUDE: ${MKL_INC}")
message(STATUS "MKL LIBRARY: ${MKL_LIB}")

#-----------------------------------------------

# mpi setup
# set(MPI_CXX_LIBRARIES 
# -L<mpi-root>/lib/release -lmpi_ilp64 -lmpi
# -L<mpi-root>/lib -lmpicxx -lmpifort
# -L<mpi-root>/libfabric/lib -lfabric
# -lrt -lpthread -ldl)
# set(MPI_CXX_COMPILER <mpi-root>/bin/choose-compiler)

#-----------------------------------------------
# sub-module setup
#-----------------------------------------------
if(CLA3P_USE_I64)
set(CMPI_LIB "cmpi_i64_pre")
set(CLA3P_LIB "cla3p_i64_pre")
else()
set(CMPI_LIB "cmpi_pre")
set(CLA3P_LIB "cla3p_pre")
endif()

add_subdirectory(cmpi)
add_subdirectory(cla3p)

add_subdirectory(3rd)
add_subdirectory(tests)
add_subdirectory(example)

#-----------------------------------------------
# end
#-----------------------------------------------
