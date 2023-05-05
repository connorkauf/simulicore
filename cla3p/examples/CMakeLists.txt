#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_SRC
	ex01_create_matrix.cpp
	ex02_create_matrix.cpp
	)

set(CLA3P_EXAMPLES_BUILD32 build_i32.sh)
set(CLA3P_EXAMPLES_BUILD64 build_i64.sh)
set(CLA3P_EXAMPLES_CMAKE cmake_list_install/CMakeLists.txt)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES ${CLA3P_EXAMPLES_SRC} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(FILES ${CLA3P_EXAMPLES_CMAKE} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(PROGRAMS ${CLA3P_EXAMPLES_BUILD32} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(PROGRAMS ${CLA3P_EXAMPLES_BUILD64} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
