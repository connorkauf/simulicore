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
# set global definitions
#-----------------------------------------------
option(CLA3P_EXAMPLES_I64 "CLA3P integer precision (32/64bits)" OFF)

#-----------------------------------------------
# set build type
#-----------------------------------------------
if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# set install location
#-----------------------------------------------
if(CLA3P_EXAMPLES_I64)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/i64" CACHE PATH "Installation directory" FORCE)
else()
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/i32" CACHE PATH "Installation directory" FORCE)
endif()
message(STATUS "Compact Suite Examples Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set compiler flags
#-----------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-m64)
endif()

#-----------------------------------------------
# set 3rd parties (initialize with CLA3P)
#-----------------------------------------------
set(CLA3P_EXAMPLES_3RD_PARTY_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set(CLA3P_EXAMPLES_3RD_PARTY_LIB -L${CMAKE_CURRENT_SOURCE_DIR}/../../lib -lcla3p)
set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB -L${CMAKE_CURRENT_SOURCE_DIR}/../../lib -lcla3p_i64)
set(CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)
set(CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

# mkl setup
if(LINUX)
	include("${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/mkl.lin.cmake")
elseif(WIN32)
	include("${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/mkl.win.cmake")
endif()
set(CLA3P_EXAMPLES_3RD_PARTY_INC ${CLA3P_EXAMPLES_3RD_PARTY_INC} ${MKL_INC})
set(CLA3P_EXAMPLES_3RD_PARTY_LIB ${CLA3P_EXAMPLES_3RD_PARTY_LIB} ${MKL_LIB})
set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB ${CLA3P_EXAMPLES_3RD_PARTY_I64_LIB} ${MKL_I64_LIB})
set(CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${MKL_LIB_DIR} ${ICC_LIB_DIR})
set(CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${MKL_DLL_DIR} ${ICC_DLL_DIR})

#-----------------------------------------------
# function that creates wrap script
#-----------------------------------------------
if(LINUX)
	function(install_script_file)
		set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${example}.sh")
		file(WRITE ${script_fname} "#!/bin/bash\n")
		file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
		file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
		file(APPEND ${script_fname} "  export LD_LIBRARY_PATH=${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}\n")
		file(APPEND ${script_fname} "else\n")
		file(APPEND ${script_fname} "  export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}\n")
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
		file(APPEND ${script_fname} "set PATH=%PATH%;${CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH}\n")
		file(APPEND ${script_fname} "\"%~dp0\\${example}\"")
		install(PROGRAMS ${script_fname} DESTINATION bin)
	endfunction()
endif()

#-----------------------------------------------
# target/dependencies/installation setup
#-----------------------------------------------
if(LINUX)
	string(REPLACE ";" ":" CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH "${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}")
endif()

file(GLOB examples "src/*.cpp")

foreach(example_cpp_full ${examples})
	get_filename_component(example_cpp ${example_cpp_full} NAME)
	string(REPLACE ".cpp" "" example ${example_cpp})
	add_executable(${example} src/${example_cpp})
	target_include_directories(${example} PRIVATE ${CLA3P_EXAMPLES_3RD_PARTY_INC})
	if(CLA3P_EXAMPLES_I64)
		target_compile_definitions(${example} PRIVATE CLA3P_I64)
		target_compile_definitions(${example} PRIVATE MKL_ILP64)
		target_link_libraries(${example} ${CLA3P_EXAMPLES_3RD_PARTY_I64_LIB})
	else()
		target_link_libraries(${example} ${CLA3P_EXAMPLES_3RD_PARTY_LIB})
	endif()
	install(TARGETS ${example} DESTINATION bin)
	install_script_file()
endforeach()

#-----------------------------------------------
# end
#-----------------------------------------------
