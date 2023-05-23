#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	types/operation.cpp
	types/property.cpp
	PARENT_SCOPE)

set(CLA3P_TYPES_HPP 
	integer.hpp
	scalar.hpp
	enums.hpp
	operation.hpp
	property.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_TYPES_HPP_INSTALL include/cla3p/types)

install(FILES ${CLA3P_TYPES_HPP} DESTINATION ${CLA3P_TYPES_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
