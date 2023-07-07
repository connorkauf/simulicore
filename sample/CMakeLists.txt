#-----------------------------------------------
# target setup
#-----------------------------------------------
set(BIN_NAME "sample")
set(BSH_NAME "${BIN_NAME}.sh")

add_executable(${BIN_NAME} sample.cpp)

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${BIN_NAME} PRIVATE 
	${COMPACT_SUITE_ROOT}
	${MKL_INC}
	)

target_link_libraries(${BIN_NAME}
	${CLA3P_LIB}
	#${CMPI_LIB} enable when ready
	${MKL_LIB}
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${BIN_NAME} DESTINATION bin)
install(PROGRAMS ${BSH_NAME} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
