#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	linsol/dns_default_lsolver.cpp
	linsol/dns_custom_lsolvers.cpp
	PARENT_SCOPE)

set(CLA3P_LINSOL_HPP 
	dns_default_lsolver.hpp
	dns_custom_lsolvers.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_LINSOL_HPP_INSTALL include/cla3p/linsol)

install(FILES ${CLA3P_LINSOL_HPP} DESTINATION ${CLA3P_LINSOL_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
