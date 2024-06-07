message(STATUS "Configuring sample executable...")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
	list(APPEND CMAKE_MESSAGE_INDENT ${SIMULICORE_INDENTATION})
endif()

#-----------------------------------------------
# target setup
#-----------------------------------------------
set(SAMPLE_BIN "sample")
set(SAMPLE_BIN_I64 "${SAMPLE_BIN}_i64")

#-----------------------------------------------
# cla3p library setup
#-----------------------------------------------
set(SAMPLE_3RD_PARTY_DEF)
set(SAMPLE_3RD_PARTY_I64_DEF CLA3P_I64)
set(SAMPLE_3RD_PARTY_INC ${SIMULICORE_ROOT}/cla3p.mod/source)
set(SAMPLE_3RD_PARTY_LIB ${CLA3P_LIB})
set(SAMPLE_3RD_PARTY_I64_LIB ${CLA3P_I64_LIB})
set(SAMPLE_3RD_PARTY_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(SAMPLE_3RD_PARTY_DLL_PATH ${CMAKE_INSTALL_PREFIX}/lib)

#-----------------------------------------------
# set openmp
#-----------------------------------------------
include(${SIMULICORE_ROOT}/cmake/openmp.cmake)

#-----------------------------------------------
# 3rd party library setup
#-----------------------------------------------
# accelerate setup
if(${SIMULICORE_CMAKE_MACOS})
	set(SAMPLE_3RD_PARTY_INC ${SAMPLE_3RD_PARTY_INC} ${MACOS_OMP_INC})
	set(SAMPLE_3RD_PARTY_LIB ${SAMPLE_3RD_PARTY_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")
	set(SAMPLE_3RD_PARTY_I64_LIB  ${SAMPLE_3RD_PARTY_I64_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")
endif()

# mkl setup
if(${SIMULICORE_CMAKE_LINUX_X86_64} OR ${SIMULICORE_CMAKE_WIN32_X86_64})
	if(${SIMULICORE_CMAKE_LINUX_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.lin.cmake)
	elseif(${SIMULICORE_CMAKE_WIN32_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.win.cmake)
	endif()
	set(SAMPLE_3RD_PARTY_I64_DEF ${SAMPLE_3RD_PARTY_I64_DEF} MKL_ILP64)
	set(SAMPLE_3RD_PARTY_INC ${SAMPLE_3RD_PARTY_INC} ${MKL_INC})
	set(SAMPLE_3RD_PARTY_LIB ${SAMPLE_3RD_PARTY_LIB} ${MKL_LIB})
	set(SAMPLE_3RD_PARTY_I64_LIB  ${SAMPLE_3RD_PARTY_I64_LIB} ${MKL_I64_LIB})
	set(SAMPLE_3RD_PARTY_LIB_PATH ${SAMPLE_3RD_PARTY_LIB_PATH} ${MKL_LIB_DIR} ${ICC_LIB_DIR})
	set(SAMPLE_3RD_PARTY_DLL_PATH ${SAMPLE_3RD_PARTY_DLL_PATH} ${MKL_DLL_DIR} ${ICC_DLL_DIR})
endif()

#-----------------------------------------------
# target & dependency setup
#-----------------------------------------------
add_executable(${SAMPLE_BIN} sample.cpp)
target_compile_definitions(${SAMPLE_BIN} PRIVATE ${SAMPLE_3RD_PARTY_DEF})
target_include_directories(${SAMPLE_BIN} PRIVATE ${SAMPLE_3RD_PARTY_INC})
target_link_libraries(${SAMPLE_BIN} ${SAMPLE_3RD_PARTY_LIB})

add_executable(${SAMPLE_BIN_I64} sample.cpp)
target_compile_definitions(${SAMPLE_BIN_I64} PRIVATE ${SAMPLE_3RD_PARTY_I64_DEF})
target_include_directories(${SAMPLE_BIN_I64} PRIVATE ${SAMPLE_3RD_PARTY_INC})
target_link_libraries(${SAMPLE_BIN_I64} ${SAMPLE_3RD_PARTY_I64_LIB})

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${SAMPLE_BIN} DESTINATION bin)
install(TARGETS ${SAMPLE_BIN_I64} DESTINATION bin)

if(${SIMULICORE_CMAKE_LINUX} OR ${SIMULICORE_CMAKE_MACOS})
	string(REPLACE ";" ":" SAMPLE_3RD_PARTY_LIB_PATH "${SAMPLE_3RD_PARTY_LIB_PATH}")
endif()

if(${SIMULICORE_CMAKE_MACOS})
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN}.sh")
	set(script_fname_i64 "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN_I64}.sh")
	file(WRITE ${script_fname} "#!/bin/bash\n")
	file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
	file(APPEND ${script_fname} "if [[ -z $" "{DYLD_FALLBACK_LIBRARY_PATH} ]]; then\n")
	file(APPEND ${script_fname} "  export DYLD_FALLBACK_LIBRARY_PATH=${SAMPLE_3RD_PARTY_LIB_PATH}\n")
	file(APPEND ${script_fname} "else\n")
	file(APPEND ${script_fname} "  export DYLD_FALLBACK_LIBRARY_PATH=$" "{DYLD_FALLBACK_LIBRARY_PATH}:${SAMPLE_3RD_PARTY_LIB_PATH}\n")
	file(APPEND ${script_fname} "fi\n")
	file(COPY_FILE ${script_fname} ${script_fname_i64})
	file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${SAMPLE_BIN}")
	file(APPEND ${script_fname_i64} "exec $" "{ROOT_DIR}/${SAMPLE_BIN_I64}")
endif()

if(${SIMULICORE_CMAKE_LINUX})
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN}.sh")
	set(script_fname_i64 "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN_I64}.sh")
	file(WRITE ${script_fname} "#!/bin/bash\n")
	file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
	file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
	file(APPEND ${script_fname} "  export LD_LIBRARY_PATH=${SAMPLE_3RD_PARTY_LIB_PATH}\n")
	file(APPEND ${script_fname} "else\n")
	file(APPEND ${script_fname} "  export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:${SAMPLE_3RD_PARTY_LIB_PATH}\n")
	file(APPEND ${script_fname} "fi\n")
	file(COPY_FILE ${script_fname} ${script_fname_i64})
	file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${SAMPLE_BIN}")
	file(APPEND ${script_fname_i64} "exec $" "{ROOT_DIR}/${SAMPLE_BIN_I64}")
endif()

if(${SIMULICORE_CMAKE_WIN32})
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN}.bat")
	set(script_fname_i64 "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN_I64}.bat")
	file(WRITE  ${script_fname} "@echo off\n")
	file(APPEND ${script_fname} "setlocal\n")
	file(APPEND ${script_fname} "set PATH=%PATH%;${SAMPLE_3RD_PARTY_DLL_PATH}\n")
	file(COPY_FILE ${script_fname} ${script_fname_i64})
	file(APPEND ${script_fname} "\"%~dp0\\${SAMPLE_BIN}\"")
	file(APPEND ${script_fname_i64} "\"%~dp0\\${SAMPLE_BIN_I64}\"")
endif()

install(PROGRAMS ${script_fname} DESTINATION bin)
install(PROGRAMS ${script_fname_i64} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
