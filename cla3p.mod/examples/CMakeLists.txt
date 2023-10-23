#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(src)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES cmake_list_install/CMakeLists.txt DESTINATION ${CLA3P_EXAMPLES_INSTALL})

if(LINUX)
	if(CLA3P_USE_I64)
		install(PROGRAMS i64/example_builder.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	else()
		install(PROGRAMS i32/example_builder.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	endif()
endif()

if(COMPACT_SUITE_FULL_INSTALL)
	if(LINUX)
		install(PROGRAMS example_runner.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	endif()
endif()
#-----------------------------------------------
# end
#-----------------------------------------------
