message(STATUS "Configuring ${CLA3P_LIB}...")

#-----------------------------------------------
# set module root
#-----------------------------------------------
set(CLA3P_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CLA3P Root Directory: ${CLA3P_ROOT}")

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(source)
add_subdirectory(examples)

if(COMPACT_SUITE_FULL_INSTALL)
	add_subdirectory(documentation)
	add_subdirectory(images)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
