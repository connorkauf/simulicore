message(STATUS "Configuring CLRA...")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
	list(APPEND CMAKE_MESSAGE_INDENT ${SIMULICORE_INDENTATION})
endif()

#-----------------------------------------------
# set module root
#-----------------------------------------------
set(CLRA_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CLRA Root Directory: ${CLRA_ROOT}")

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
set(CLRA_SOURCE_DIR ${SIMULICORE_ROOT}/../clra.mod/source)
if(EXISTS ${CLRA_SOURCE_DIR})
	if(IS_DIRECTORY ${CLRA_SOURCE_DIR})
		add_subdirectory(${CLRA_SOURCE_DIR} ${CMAKE_BINARY_DIR}/source)
	endif()
endif()

#add_subdirectory(examples)

if(${SIMULICORE_FULL_INSTALL})
	add_subdirectory(documentation)
	add_subdirectory(images)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
