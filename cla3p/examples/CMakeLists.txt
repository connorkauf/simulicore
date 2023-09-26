#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_SRC
	ex01_create_matrix.cpp
	ex02_create_matrix.cpp
	)

set(CLA3P_EXAMPLES_CMAKE cmake_list_install/CMakeLists.txt)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES ${CLA3P_EXAMPLES_SRC} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(FILES ${CLA3P_EXAMPLES_CMAKE} DESTINATION ${CLA3P_EXAMPLES_INSTALL})

if(LINUX)
	if(CLA3P_USE_I64)
		install(PROGRAMS build64/build.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	else()
		install(PROGRAMS build32/build.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	endif()
endif()
#-----------------------------------------------
# end
#-----------------------------------------------
