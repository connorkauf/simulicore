cmake_minimum_required(VERSION 3.7.0)

set(project_name "SimuliCore")
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
# set compiler options
#-----------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
if(SIMULICORE_FULL_INSTALL)
	add_compile_options(-Werror)
endif()
	add_compile_options(-m64)
	add_compile_options(-Wall)
	add_compile_options(-Wextra)
	add_compile_options(-Wshadow)
	add_compile_options(-Wmissing-format-attribute)
	add_compile_options(-fdiagnostics-color=always)
	#add_compile_options(-Wno-psabi)
endif()

# TODO: add options for all compilers

#-----------------------------------------------
# set build type
#-----------------------------------------------
if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# set project root
#-----------------------------------------------
set(SIMULICORE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "SimuliCore Root Directory: ${SIMULICORE_ROOT}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${SIMULICORE_ROOT}/install" CACHE PATH "Installation directory" FORCE)
endif()
message(STATUS "SimuliCore Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
option(SIMULICORE_FULL_INSTALL "Install all SimuliCore featues" OFF)

#-----------------------------------------------
# sub-module setup
#-----------------------------------------------
add_subdirectory(3rd)
add_subdirectory(licensing)
add_subdirectory(cla3p.mod)

if(SIMULICORE_FULL_INSTALL)
	add_subdirectory(sample)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
