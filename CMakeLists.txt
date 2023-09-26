cmake_minimum_required(VERSION 3.7.0)

set(project_name "Compact Suite")
set(project_version "1.0.0")
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

#-----------------------------------------------
# detect operating system
#-----------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.25.0")
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		set(LINUX 1)
	endif()
endif()

if(LINUX)
	message(STATUS "Detected OS: Linux")
elseif(WIN32)
	message(STATUS "Detected OS: Windows")
elseif(APPLE)
	message(STATUS "Detected OS: MacOS")
else()
	message(FATAL_ERROR "Unsupported OS (${CMAKE_SYSTEM_NAME})")
endif()

#-----------------------------------------------
# choose standard
#-----------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#-----------------------------------------------
# set build type
#-----------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# set project root
#-----------------------------------------------
set(COMPACT_SUITE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Compact Suite Root Directory: ${COMPACT_SUITE_ROOT}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${COMPACT_SUITE_ROOT}/install" CACHE PATH "Installation directory" FORCE)
endif()
message(STATUS "Compact Suite Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
message(STATUS "Use 64bit integers for CLA3P: ${CLA3P_USE_I64}")

if(CLA3P_USE_I64)
	add_definitions(-DCLA3P_I64)
endif()

#-----------------------------------------------
# set compiler flags
#-----------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-m64)
	add_compile_options(-Werror)
	add_compile_options(-Wall)
	add_compile_options(-Wextra)
	add_compile_options(-Wshadow)
	add_compile_options(-Wmissing-format-attribute)
	add_compile_options(-fdiagnostics-color=always)
endif()

#-----------------------------------------------
# set openmp
#-----------------------------------------------
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
# set 3rd parties
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
# sub-module setup
#-----------------------------------------------
if(CLA3P_USE_I64)
	set(CLA3P_LIB "cla3p_i64_pre")
else()
	set(CLA3P_LIB "cla3p_pre")
endif()
message(STATUS "CLA3P_LIB: ${CLA3P_LIB}")

#-----------------------------------------------

add_subdirectory(cla3p)

add_subdirectory(3rd)
add_subdirectory(sample)

#-----------------------------------------------
# end
#-----------------------------------------------
