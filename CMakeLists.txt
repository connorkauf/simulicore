cmake_minimum_required(VERSION 3.12.0)
cmake_policy(SET CMP0074 NEW)

set(project_name "SimuliCore")
set(project_version "1.3.0")
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

#-----------------------------------------------
# welcome message
#-----------------------------------------------
message(STATUS "Configuring SimuliCore Suite...")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
	set(SIMULICORE_INDENTATION "    ")
	list(APPEND CMAKE_MESSAGE_INDENT ${SIMULICORE_INDENTATION})
endif()

#-----------------------------------------------
# set project root
#-----------------------------------------------
set(SIMULICORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "SimuliCore Root Directory: ${SIMULICORE_ROOT}")

#-----------------------------------------------
# set global project definitions
#-----------------------------------------------
option(SIMULICORE_FULL_INSTALL "Install all SimuliCore featues" OFF)

#-----------------------------------------------
# build & install setup
#-----------------------------------------------
include(${SIMULICORE_ROOT}/cmake/os.cmake)
include(${SIMULICORE_ROOT}/cmake/compiler.cmake)
include(${SIMULICORE_ROOT}/cmake/build_type.cmake)
include(${SIMULICORE_ROOT}/cmake/install.cmake)

message(STATUS "Detected OS: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR})")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "SimuliCore Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# sub-module setup
#-----------------------------------------------
add_subdirectory(cmake)
add_subdirectory(licensing)
add_subdirectory(cla3p.mod)
add_subdirectory(clra.mod)

if(${SIMULICORE_FULL_INSTALL})
	add_subdirectory(sample)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
