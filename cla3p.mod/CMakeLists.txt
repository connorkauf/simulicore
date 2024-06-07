message(STATUS "Configuring CLA3P...")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
	list(APPEND CMAKE_MESSAGE_INDENT ${SIMULICORE_INDENTATION})
endif()

#-----------------------------------------------
# set module root
#-----------------------------------------------
set(CLA3P_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CLA3P Root Directory: ${CLA3P_ROOT}")

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(source)
add_subdirectory(examples)

if(${SIMULICORE_FULL_INSTALL})
	add_subdirectory(documentation)
	add_subdirectory(images)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
