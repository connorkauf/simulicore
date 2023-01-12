message("Setting up ${LINA_LIB}...")

set(LINA_SRC
	test.cpp
	)

set(LINA_HPP
	test.hpp
	)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_library(${LINA_LIB} SHARED ${LINA_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(LINA_INC_INSTALL include/lina)
set(LINA_LIB_INSTALL lib)

install(TARGETS ${LINA_LIB} DESTINATION ${LINA_LIB_INSTALL})
install(FILES   ${LINA_HPP} DESTINATION ${LINA_INC_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
