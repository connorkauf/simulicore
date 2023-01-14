message("Setting up ${CLA3P_LIB}...")

set(CLA3P_SRC
	test.cpp
	)

set(CLA3P_HPP
	test.hpp
	)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_library(${CLA3P_LIB} SHARED ${CLA3P_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_INC_INSTALL include/cla3p)
set(CLA3P_LIB_INSTALL lib)

install(TARGETS ${CLA3P_LIB} DESTINATION ${CLA3P_LIB_INSTALL})
install(FILES   ${CLA3P_HPP} DESTINATION ${CLA3P_INC_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
