#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(src)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLRA_EXAMPLES_INSTALL examples/clra)

install(FILES cmake_list_install/CMakeLists.txt DESTINATION ${CLRA_EXAMPLES_INSTALL})

if(${SIMULICORE_CMAKE_LINUX} OR ${SIMULICORE_CMAKE_MACOS})
	install(PROGRAMS example_builder.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
	install(PROGRAMS example_builder_i32.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
	install(PROGRAMS example_builder_i64.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
	if(${SIMULICORE_FULL_INSTALL})
		install(PROGRAMS example_executor.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
		install(PROGRAMS example_executor_i32.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
		install(PROGRAMS example_executor_i64.sh DESTINATION ${CLRA_EXAMPLES_INSTALL})
	endif()
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
