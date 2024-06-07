cmake_minimum_required(VERSION 3.12.0)

project("CLA3P Examples" VERSION "1.0.0" LANGUAGES CXX)

#-----------------------------------------------
# set global definitions
#-----------------------------------------------
option(CLA3P_EXAMPLES_I64 "CLA3P integer precision (32/64bits)" OFF)
set(SIMULICORE_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

#-----------------------------------------------
# build setup
#-----------------------------------------------
include(${SIMULICORE_INSTALL_DIR}/cmake/os.cmake)
include(${SIMULICORE_INSTALL_DIR}/cmake/compiler.cmake)
include(${SIMULICORE_INSTALL_DIR}/cmake/build_type.cmake)

message(STATUS "Detected OS: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR})")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------
# installation setup
#-----------------------------------------------
if(${CLA3P_EXAMPLES_I64})
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/i64" CACHE PATH "Installation directory" FORCE)
else()
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/i32" CACHE PATH "Installation directory" FORCE)
endif()
message(STATUS "SimuliCore Examples Install Directory: ${CMAKE_INSTALL_PREFIX}")

#-----------------------------------------------
# set openmp
#-----------------------------------------------
include(${SIMULICORE_INSTALL_DIR}/cmake/openmp.cmake)

#-----------------------------------------------
# set 3rd parties (initialize with CLA3P)
#-----------------------------------------------

set(CLA3P_EXAMPLES_3RD_PARTY_DEF)
set(CLA3P_EXAMPLES_3RD_PARTY_I64_DEF CLA3P_I64)
set(CLA3P_EXAMPLES_3RD_PARTY_INC ${SIMULICORE_INSTALL_DIR}/include)

set(CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${SIMULICORE_INSTALL_DIR}/lib)
set(CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH ${CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH} ${SIMULICORE_INSTALL_DIR}/lib)
if(${SIMULICORE_CMAKE_LINUX})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB -L${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} -lcla3p)
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB -L${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} -lcla3p_i64)
elseif(${SIMULICORE_CMAKE_WIN32})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}/cla3p.lib)
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}/cla3p_i64.lib)
elseif(${SIMULICORE_CMAKE_MACOS})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB -L${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} -lcla3p)
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB -L${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} -lcla3p_i64)
endif()

# accelerate setup
if(${SIMULICORE_CMAKE_MACOS})
	set(CLA3P_EXAMPLES_3RD_PARTY_DEF ${CLA3P_EXAMPLES_3RD_PARTY_DEF} ACCELERATE_NEW_LAPACK)
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_DEF ${CLA3P_EXAMPLES_3RD_PARTY_I64_DEF} ACCELERATE_NEW_LAPACK ACCELERATE_LAPACK_ILP64)
	set(CLA3P_EXAMPLES_3RD_PARTY_INC ${CLA3P_EXAMPLES_3RD_PARTY_INC} ${MACOS_OMP_INC})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB ${CLA3P_EXAMPLES_3RD_PARTY_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB  ${CLA3P_EXAMPLES_3RD_PARTY_I64_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")
endif()

# mkl setup
if(${SIMULICORE_CMAKE_LINUX_X86_64} OR ${SIMULICORE_CMAKE_WIN32_X86_64})
	if(${SIMULICORE_CMAKE_LINUX_X86_64})
		include(${SIMULICORE_INSTALL_DIR}/cmake/3rd/mkl.lin.cmake)
	elseif(${SIMULICORE_CMAKE_WIN32_X86_64})
		include(${SIMULICORE_INSTALL_DIR}/cmake/3rd/mkl.win.cmake)
	endif()
	message(STATUS "Intel MKL ROOT: ${MKL_ROOT}")
	message(STATUS "Intel ICC ROOT: ${ICC_ROOT}")
	set(CLA3P_MKL_DEFAULT_DEFS CLA3P_INTEL_MKL MKL_Complex8=std::complex<float> MKL_Complex16=std::complex<double>)
	set(CLA3P_EXAMPLES_3RD_PARTY_DEF ${CLA3P_EXAMPLES_3RD_PARTY_DEF} ${CLA3P_MKL_DEFAULT_DEFS})
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_DEF ${CLA3P_EXAMPLES_3RD_PARTY_I64_DEF} ${CLA3P_MKL_DEFAULT_DEFS} MKL_ILP64)
	set(CLA3P_EXAMPLES_3RD_PARTY_INC ${CLA3P_EXAMPLES_3RD_PARTY_INC} ${MKL_INC})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB ${CLA3P_EXAMPLES_3RD_PARTY_LIB} ${MKL_LIB})
	set(CLA3P_EXAMPLES_3RD_PARTY_I64_LIB  ${CLA3P_EXAMPLES_3RD_PARTY_I64_LIB} ${MKL_I64_LIB})
	set(CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH ${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH} ${MKL_LIB_DIR} ${ICC_LIB_DIR})
	set(CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH ${CLA3P_EXAMPLES_3RD_PARTY_DLL_PATH} ${MKL_DLL_DIR} ${ICC_DLL_DIR})
endif()

#-----------------------------------------------
# function that creates wrap script
#-----------------------------------------------
if(${SIMULICORE_CMAKE_MACOS})
	function(install_script_file)
		set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${example}.sh")
		file(WRITE ${script_fname} "#!/bin/bash\n")
		file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
		file(APPEND ${script_fname} "if [[ -z $" "{DYLD_FALLBACK_LIBRARY_PATH} ]]; then\n")
		file(APPEND ${script_fname} "  export DYLD_FALLBACK_LIBRARY_PATH=${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}\n")
		file(APPEND ${script_fname} "else\n")
		file(APPEND ${script_fname} "  export DYLD_FALLBACK_LIBRARY_PATH=$" "{DYLD_FALLBACK_LIBRARY_PATH}:${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}\n")
		file(APPEND ${script_fname} "fi\n")
		file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${example}")
		install(PROGRAMS ${script_fname} DESTINATION bin)
	endfunction()
endif()

if(${SIMULICORE_CMAKE_LINUX})
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

if(${SIMULICORE_CMAKE_WIN32})
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
if(${SIMULICORE_CMAKE_LINUX} OR ${SIMULICORE_CMAKE_MACOS})
	string(REPLACE ";" ":" CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH "${CLA3P_EXAMPLES_3RD_PARTY_LIB_PATH}")
endif()

file(GLOB examples "src/*.cpp")

foreach(example_cpp_full ${examples})
	get_filename_component(example_cpp ${example_cpp_full} NAME)
	string(REPLACE ".cpp" "" example ${example_cpp})
	add_executable(${example} src/${example_cpp})
	if(${CLA3P_EXAMPLES_I64})
		target_include_directories(${example} PRIVATE ${CLA3P_EXAMPLES_3RD_PARTY_INC})
		target_compile_definitions(${example} PRIVATE ${CLA3P_EXAMPLES_3RD_PARTY_I64_DEF})
		target_link_libraries(${example} ${CLA3P_EXAMPLES_3RD_PARTY_I64_LIB})
	else()
		target_include_directories(${example} PRIVATE ${CLA3P_EXAMPLES_3RD_PARTY_INC})
		target_compile_definitions(${example} PRIVATE ${CLA3P_EXAMPLES_3RD_PARTY_DEF})
		target_link_libraries(${example} ${CLA3P_EXAMPLES_3RD_PARTY_LIB})
	endif()
	install(TARGETS ${example} DESTINATION bin)
	install_script_file()
endforeach()

#-----------------------------------------------
# end
#-----------------------------------------------
