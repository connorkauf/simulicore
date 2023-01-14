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
# set install location
#-----------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")

#-----------------------------------------------
# add build subdirectories
#-----------------------------------------------
add_subdirectory(src)

#-----------------------------------------------
# end
#-----------------------------------------------
