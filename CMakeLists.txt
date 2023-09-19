cmake_minimum_required(VERSION 3.1.0)

set(project_name "Compact Suite")
set(project_version "1.0.0")
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

#-----------------------------------------------
# detect operating system
#-----------------------------------------------
# FIXME: tide this up
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
if(CMAKE_VERSION VERSION_LESS "3.25.0")
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		set(LINUX 1)
	endif()
endif()

message("WIN32: ${WIN32}")
message("UNIX : ${UNIX}")
message("APPLE: ${APPLE}")
message("LINUX: ${LINUX}")

if(LINUX)
	message("LINUX OS IS DETECTED!!!")
endif()

if(WIN32)
	message("WINDOWS OS IS DETECTED!!!")
endif()

if(APPLE)
	message("MAC OS IS DETECTED!!!")
endif()

#-----------------------------------------------
# choose standard
#-----------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#-----------------------------------------------
# set build type
#-----------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# set project root
#-----------------------------------------------
set(COMPACT_SUITE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message("Compact Suite Root Directory: ${COMPACT_SUITE_ROOT}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${COMPACT_SUITE_ROOT}/install" CACHE PATH "Installation directory" FORCE)
endif()
message("Compact Suite Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
message("Use 64bit integers for CLA3P: ${CLA3P_USE_I64}")

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
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
	message(WARNING "OpenMP not found")
endif()

#-----------------------------------------------

# mkl setup
add_definitions(-DMKL_Complex8=std::complex<float>)
add_definitions(-DMKL_Complex16=std::complex<double>)
if(LINUX)
	include(3rd/mkl.lin.cmake)
elseif(WIN32)
	include(3rd/mkl.win.cmake)
endif()
message(STATUS "MKL_INC: ${MKL_INC}")
message(STATUS "MKL_LIB: ${MKL_LIB}")

#-----------------------------------------------

# mpi setup
# or future use
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
message(STATUS "CMPI_LIB: ${CMPI_LIB}")
message(STATUS "CLA3P_LIB: ${CLA3P_LIB}")

#-----------------------------------------------

add_subdirectory(cmpi)
add_subdirectory(cla3p)

add_subdirectory(3rd)
#add_subdirectory(tests)
add_subdirectory(sample)

#-----------------------------------------------
# end
#-----------------------------------------------
