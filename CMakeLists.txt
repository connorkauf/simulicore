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
# set project root
#-----------------------------------------------
set(CLA3P_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CLA3P_PROJECT_ROOT}/install")

#-----------------------------------------------
# sub-module setup
#-----------------------------------------------
set(CMPI_LIB "cmpi-pre")
set(CLA3P_LIB "cla3p-pre")

add_subdirectory(cmpi)
add_subdirectory(cla3p)

#-----------------------------------------------
# custom executable setup
#-----------------------------------------------
add_subdirectory(example)

#-----------------------------------------------
# end
#-----------------------------------------------
