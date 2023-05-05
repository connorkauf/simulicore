cmake_minimum_required(VERSION 3.1.0)

project("CLA3P Examples" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#-----------------------------------------------
# set build type
#-----------------------------------------------
set(CMAKE_BUILD_TYPE Release)

#-----------------------------------------------
# set install location
#-----------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
if(CLA3P_USE_I64)
	add_definitions(-DCLA3P_I64)
endif()

#-----------------------------------------------
# set compiler flags
#-----------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

#-----------------------------------------------
# set 3rd parties
#-----------------------------------------------

# mkl setup
set(MKL_ROOT /home/connor/Development/3rd/intel/mkl_23.1.0)
set(ICC_ROOT /home/connor/Development/3rd/intel/compiler_23.1.0)
set(IOMP5_LIB
	-L${ICC_ROOT}/lib/intel64_lin
	-liomp5)
set(MKL_INC ${MKL_ROOT}/include)
if(CLA3P_USE_I64)
	message(STATUS "Configuring Intel MKL (64bit integers)...")
	add_definitions(-DMKL_ILP64)
	set(MKL_LIB
		-L${MKL_ROOT}/lib/intel64
		-Wl,--no-as-needed
		-lmkl_intel_ilp64
		-lmkl_intel_thread
		-lmkl_core
		${IOMP5_LIB}
		-lpthread -lm -ldl)
else()
	message(STATUS "Configuring Intel MKL (32bit integers)...")
	set(MKL_LIB
		-L${MKL_ROOT}/lib/intel64
		-Wl,--no-as-needed
		-lmkl_intel_lp64
		-lmkl_intel_thread
		-lmkl_core
		${IOMP5_LIB}
		-lpthread -lm -ldl)
endif()

#-----------------------------------------------
# set compact libraries
#-----------------------------------------------

# cla3p setup
if(CLA3P_USE_I64)
	set(CLA3P_LIB -lcla3p_i64_pre)
else()
	set(CLA3P_LIB -lcla3p_pre)
endif()

set(CLA3P_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set(CLA3P_LIB -L${CMAKE_CURRENT_SOURCE_DIR}/../../lib ${CLA3P_LIB})

#-----------------------------------------------
# function that creates wrap script
#-----------------------------------------------
function(install_script_file)
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${example}.sh")
	file(WRITE ${script_fname} "#!/bin/bash\n")
	file(APPEND ${script_fname} "MKL_LIB_PATH=${MKL_ROOT}/lib/intel64:${ICC_ROOT}/lib/intel64_lin\n")
	file(APPEND ${script_fname} "CLA3P_LIB_PATH=${CMAKE_CURRENT_SOURCE_DIR}/../../lib\n")
	file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATH}\n")
	file(APPEND ${script_fname} "else\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATH}\n")
	file(APPEND ${script_fname} "fi\n")
	file(APPEND ${script_fname} "exec ./${example}")
	install(PROGRAMS ${script_fname} DESTINATION bin)
endfunction()

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
