set(CONFIG_FILES_CMAKE 
	os.cmake
	compiler.cmake
	build_type.cmake
	install.cmake
	openmp.cmake
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CONFIG_FILES_CMAKE_INSTALL cmake)

install(FILES ${CONFIG_FILES_CMAKE} DESTINATION ${CONFIG_FILES_CMAKE_INSTALL})

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(3rd)
