#-----------------------------------------------
# target setup
#-----------------------------------------------
set(BIN_NAME "sample")

if(UNIX)
	set(BSH_NAME "${BIN_NAME}.sh")
elseif(WIN32)
	set(BSH_NAME "${BIN_NAME}.bat")
endif()

add_executable(${BIN_NAME} sample.cpp)

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${BIN_NAME} PRIVATE 
	${COMPACT_SUITE_ROOT}
	${MKL_INC}
	)

target_link_libraries(${BIN_NAME}
	${CLA3P_LIB}
	${MKL_LIB}
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${BIN_NAME} DESTINATION bin)

if(LINUX)
	set(script_fname "${CMAKE_CURRENT_BINARY_DIR}/${BSH_NAME}")
	file(WRITE ${script_fname} "#!/bin/bash\n")
	file(APPEND ${script_fname} "ROOT_DIR=`dirname $0`\n")
	file(APPEND ${script_fname} "MKL_LIB_PATHS=${MKL_LIB_DIR}:${ICC_LIB_DIR}\n")
	file(APPEND ${script_fname} "CLA3P_LIB_PATH=${CMAKE_INSTALL_PREFIX}/lib\n")
	file(APPEND ${script_fname} "if [[ -z $" "{LD_LIBRARY_PATH} ]]; then\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
	file(APPEND ${script_fname} "else\n")
	file(APPEND ${script_fname} "export LD_LIBRARY_PATH=$" "{LD_LIBRARY_PATH}:$" "{CLA3P_LIB_PATH}:$" "{MKL_LIB_PATHS}\n")
	file(APPEND ${script_fname} "fi\n")
	file(APPEND ${script_fname} "exec $" "{ROOT_DIR}/${BIN_NAME}")
	install(PROGRAMS ${script_fname} DESTINATION bin)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
