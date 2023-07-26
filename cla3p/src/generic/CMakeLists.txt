#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	generic/guard.cpp
	generic/ownership.cpp
	generic/array2d.cpp
	PARENT_SCOPE)

set(CLA3P_GENERIC_HPP 
	guard.hpp
	ownership.hpp
	array2d.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_GENERIC_HPP_INSTALL include/cla3p/generic)

install(FILES ${CLA3P_GENERIC_HPP} DESTINATION ${CLA3P_GENERIC_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
