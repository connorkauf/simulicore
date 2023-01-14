#-----------------------------------------------
# source root setup
#-----------------------------------------------
set(SRC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------
# sub-module setup
#-----------------------------------------------
set(CLA3P_LIB "cla3p-pre")
add_subdirectory(cla3p)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_executable(${BIN_NAME} example.cpp)

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${BIN_NAME} PRIVATE
	)

target_link_libraries(${BIN_NAME}
	${CLA3P_LIB}
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${BIN_NAME} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
