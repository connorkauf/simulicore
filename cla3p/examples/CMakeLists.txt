#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_SRC
	ex01_create_matrix.cpp
	ex02_create_matrix.cpp
	)

set(CLA3P_EXAMPLES_BUILD32 build32/build.sh)
set(CLA3P_EXAMPLES_BUILD64 build64/build.sh)
set(CLA3P_EXAMPLES_CMAKE cmake_list_install/CMakeLists.txt)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES ${CLA3P_EXAMPLES_SRC} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(FILES ${CLA3P_EXAMPLES_CMAKE} DESTINATION ${CLA3P_EXAMPLES_INSTALL})

if(CLA3P_USE_I64)
	install(PROGRAMS ${CLA3P_EXAMPLES_BUILD64} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
else()
	install(PROGRAMS ${CLA3P_EXAMPLES_BUILD32} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
endif()
#-----------------------------------------------
# end
#-----------------------------------------------
