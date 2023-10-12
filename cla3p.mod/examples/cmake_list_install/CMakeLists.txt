cmake_minimum_required(VERSION 3.7.0)

project("CLA3P Examples" VERSION "1.0.0" LANGUAGES CXX)

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
# set install location
#-----------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Installation directory" FORCE)
message(STATUS "Compact Suite Examples Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
if(CLA3P_USE_I64)
	add_definitions(-DCLA3P_I64)
endif()

#-----------------------------------------------
# set compiler flags
#-----------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-m64)
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
if(LINUX)
	include("${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/mkl.lin.cmake")
elseif(WIN32)
	include("${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/mkl.win.cmake")
endif()
message(STATUS "MKL_INC: ${MKL_INC}")
message(STATUS "MKL_LIB: ${MKL_LIB}")

#-----------------------------------------------
# set compact libraries
#-----------------------------------------------

# cla3p setup
set(CLA3P_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

if(CLA3P_USE_I64)
	set(CLA3P_LIB_BASENAME "cla3p_i64")
else()
	set(CLA3P_LIB_BASENAME "cla3p")
endif()

if(LINUX)
	set(CLA3P_LIB -L${CMAKE_CURRENT_SOURCE_DIR}/../../lib -l${CLA3P_LIB_BASENAME})
elseif(WIN32)
	set(CLA3P_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CLA3P_LIB_BASENAME}.lib)
endif()

#-----------------------------------------------
# function that creates wrap script
#-----------------------------------------------
if(LINUX)
	function(install_script_file)
		set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${example}.sh")
		file(WRITE ${script_fname} "#!/bin/bash\n")
		file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
		file(APPEND ${script_fname} "MKL_LIB_PATHS=${MKL_LIB_DIR}:${ICC_LIB_DIR}\n")
		file(APPEND ${script_fname} "CLA3P_LIB_PATH=${CMAKE_CURRENT_SOURCE_DIR}/../../lib\n")
		file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
		file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
		file(APPEND ${script_fname} "else\n")
		file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
		file(APPEND ${script_fname} "fi\n")
		file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${example}")
		install(PROGRAMS ${script_fname} DESTINATION bin)
	endfunction()
endif()

if(WIN32)
	function(install_script_file)
		set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${example}.bat")
		file(WRITE  ${script_fname} "@echo off\n")
		file(APPEND ${script_fname} "setlocal\n")
		file(APPEND ${script_fname} "set MKL_LIB_PATHS=${MKL_DLL_DIR};${ICC_DLL_DIR}\n")	
		file(APPEND ${script_fname} "set CLA3P_LIB_PATH=${CMAKE_CURRENT_SOURCE_DIR}/../../lib\n")
		file(APPEND ${script_fname} "set PATH=%PATH%;%CLA3P_LIB_PATH%;%MKL_LIB_PATHS%\n")
		file(APPEND ${script_fname} "\"%~dp0\\${example}\"")
		install(PROGRAMS ${script_fname} DESTINATION bin)
	endfunction()
endif()

#-----------------------------------------------
# target/dependencies/installation setup
#-----------------------------------------------

file(GLOB examples "*.cpp")

foreach(example_cpp_full ${examples})
	get_filename_component(example_cpp ${example_cpp_full} NAME)
	string(REPLACE ".cpp" "" example ${example_cpp})
	add_executable(${example} ${example_cpp})
	target_include_directories(${example} PRIVATE ${CLA3P_INC})
	target_link_libraries(${example} ${CLA3P_LIB})
	target_link_libraries(${example} ${MKL_LIB})
	install(TARGETS ${example} DESTINATION bin)
	install_script_file()
endforeach()

#-----------------------------------------------
# end
#-----------------------------------------------
