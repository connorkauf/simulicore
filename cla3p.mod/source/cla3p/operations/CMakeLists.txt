#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	operations/math_ops.cpp
	operations/operators.cpp
	PARENT_SCOPE)

set(CLA3P_OPERATIONS_HPP 
	math_ops.hpp
	operators.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_OPERATIONS_HPP_INSTALL include/cla3p/operations)

install(FILES ${CLA3P_OPERATIONS_HPP} DESTINATION ${CLA3P_OPERATIONS_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
