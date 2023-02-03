#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	generic/dns_generic.cpp
	PARENT_SCOPE)

set(CLA3P_GENERIC_HPP 
	dns_generic.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_GENERIC_HPP_INSTALL include/cla3p/generic)

install(FILES ${CLA3P_GENERIC_HPP} DESTINATION ${CLA3P_GENERIC_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
