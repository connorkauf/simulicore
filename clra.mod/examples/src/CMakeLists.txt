#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLRA_EXAMPLES_SRC
	ex01a_lowrank_matrix_create.cpp
	ex01b_lowrank_matrix_create_random.cpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLRA_EXAMPLES_INSTALL examples/clra/src)

install(FILES ${CLRA_EXAMPLES_SRC} DESTINATION ${CLRA_EXAMPLES_INSTALL})

#-----------------------------------------------
# end
#-----------------------------------------------
