#-----------------------------------------------
# target setup
#-----------------------------------------------
set(BIN_NAME "example")
set(BSH_NAME "${BIN_NAME}.sh")

add_executable(${BIN_NAME} example.cpp)

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${BIN_NAME} PRIVATE 
	${CLA3P_PROJECT_ROOT}
	)

target_link_libraries(${BIN_NAME}
	${CLA3P_LIB}
	#${CMPI_LIB}
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${BIN_NAME} DESTINATION bin)
install(PROGRAMS ${BSH_NAME} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
