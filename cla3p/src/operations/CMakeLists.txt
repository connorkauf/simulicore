#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	operations/math_ops.cpp
	PARENT_SCOPE)

set(CLA3P_OPERATIONS_HPP 
	math_ops.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_OPERATIONS_HPP_INSTALL include/cla3p/operations)

install(FILES ${CLA3P_OPERATIONS_HPP} DESTINATION ${CLA3P_OPERATIONS_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
