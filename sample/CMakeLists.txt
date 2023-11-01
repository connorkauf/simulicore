#-----------------------------------------------
# target setup
#-----------------------------------------------
set(SAMPLE_BIN "sample")
set(SAMPLE_BIN_I64 "${SAMPLE_BIN}_i64")

#-----------------------------------------------
# 3rd party library setup
#-----------------------------------------------
if(LINUX)
  include("${COMPACT_SUITE_ROOT}/3rd/mkl.lin.cmake")
	set(CLA3P_LIB -L${CMAKE_BINARY_DIR}/cla3p.mod/source/cla3p -lcla3p)
	set(CLA3P_I64_LIB -L${CMAKE_BINARY_DIR}/cla3p.mod/source/cla3p -lcla3p_i64)
elseif(WIN32)
  include("${COMPACT_SUITE_ROOT}/3rd/mkl.win.cmake")
	set(CLA3P_LIB ${CMAKE_BINARY_DIR}/cla3p.mod/source/cla3p/cla3p.lib)
	set(CLA3P_I64_LIB ${CMAKE_BINARY_DIR}/cla3p.mod/source/cla3p/cla3p_i64.lib)
endif()

#-----------------------------------------------
# target & dependency setup
#-----------------------------------------------
include_directories(
	${COMPACT_SUITE_ROOT}/cla3p.mod/source
	${MKL_INC}
	)

add_executable(${SAMPLE_BIN} sample.cpp)
target_link_libraries(${SAMPLE_BIN} ${CLA3P_LIB} ${MKL_LIB})

add_executable(${SAMPLE_BIN_I64} sample.cpp)
target_compile_definitions(${SAMPLE_BIN_I64} PRIVATE CLA3P_I64)
target_compile_definitions(${SAMPLE_BIN_I64} PRIVATE MKL_ILP64)
target_link_libraries(${SAMPLE_BIN_I64} ${CLA3P_I64_LIB} ${MKL_I64_LIB})

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${SAMPLE_BIN} DESTINATION bin)
install(TARGETS ${SAMPLE_BIN_I64} DESTINATION bin)

if(LINUX)
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN}.sh")
	set(script_fname_i64 "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN_I64}.sh")
	file(WRITE ${script_fname} "#!/bin/bash\n")
	file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
	file(APPEND ${script_fname} "MKL_LIB_PATHS=${MKL_LIB_DIR}:${ICC_LIB_DIR}\n")
	file(APPEND ${script_fname} "CLA3P_LIB_PATH=${CMAKE_INSTALL_PREFIX}/lib\n")
	file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
	file(APPEND ${script_fname} "else\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
	file(APPEND ${script_fname} "fi\n")
	file(COPY_FILE ${script_fname} ${script_fname_i64})
	file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${SAMPLE_BIN}")
	file(APPEND ${script_fname_i64} "exec $" "{ROOT_DIR}/${SAMPLE_BIN_I64}")
endif()

if(WIN32)
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN}.bat")
	set(script_fname_i64 "${CMAKE_CURRENT_BINARY_DIR}/${SAMPLE_BIN_I64}.bat")
	file(WRITE  ${script_fname} "@echo off\n")
	file(APPEND ${script_fname} "setlocal\n")
	file(APPEND ${script_fname} "set MKL_LIB_PATHS=${MKL_DLL_DIR};${ICC_DLL_DIR}\n")	
	file(APPEND ${script_fname} "set CLA3P_LIB_PATH=${CMAKE_INSTALL_PREFIX}/lib\n")
	file(APPEND ${script_fname} "set PATH=%PATH%;%CLA3P_LIB_PATH%;%MKL_LIB_PATHS%\n")
	file(COPY_FILE ${script_fname} ${script_fname_i64})
	file(APPEND ${script_fname} "\"%~dp0\\${SAMPLE_BIN}\"")
	file(APPEND ${script_fname_i64} "\"%~dp0\\${SAMPLE_BIN_I64}\"")
endif()

install(PROGRAMS ${script_fname} DESTINATION bin)
install(PROGRAMS ${script_fname_i64} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
