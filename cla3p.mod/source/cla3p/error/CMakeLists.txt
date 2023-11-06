#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	error/exceptions.cpp
	error/literals.cpp
	PARENT_SCOPE)

set(CLA3P_ERROR_HPP 
	exceptions.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_ERROR_HPP_INSTALL include/cla3p/error)

install(FILES ${CLA3P_ERROR_HPP} DESTINATION ${CLA3P_ERROR_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
