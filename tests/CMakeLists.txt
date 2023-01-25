#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_TEST_SRC
	types_test.cpp
	cla3p_tests.cpp
  )

set(CLA3P_TEST_HPP
  )

#-----------------------------------------------
# target setup
#-----------------------------------------------
set(BIN_NAME "cla3p_tests")
set(BSH_NAME "${BIN_NAME}.sh")

add_executable(${BIN_NAME} ${CLA3P_TEST_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${BIN_NAME} PRIVATE 
	${CLA3P_PROJECT_ROOT}
	)

target_link_libraries(${BIN_NAME}
	${CLA3P_LIB}
	#${CMPI_LIB} enable when ready
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
install(TARGETS ${BIN_NAME} DESTINATION bin)
install(PROGRAMS ${BSH_NAME} DESTINATION bin)

#-----------------------------------------------
# end
#-----------------------------------------------
