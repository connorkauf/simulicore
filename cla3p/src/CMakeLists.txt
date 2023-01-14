#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC
	test.cpp
	)

set(CLA3P_HPP
	test.hpp
	types.hpp
	)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_library(${CLA3P_LIB} SHARED ${CLA3P_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
# target_include_directories(${CLA3P_LIB} PRIVATE ${SOME_INC_DIR})
# target_link_libraries(${CLA3P_LIB} ${SOME_LIB})

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_HPP_INSTALL include/cla3p)
set(CLA3P_LIB_INSTALL lib)

install(FILES   ${CLA3P_HPP} DESTINATION ${CLA3P_HPP_INSTALL})
install(TARGETS ${CLA3P_LIB} DESTINATION ${CLA3P_LIB_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
