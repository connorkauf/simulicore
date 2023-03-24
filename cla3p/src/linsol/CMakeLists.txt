#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	linsol/dns_lsolver_base.cpp
	linsol/dns_auto_lsolver.cpp
	linsol/dns_llt_lsolver.cpp
	linsol/dns_ldlt_lsolver.cpp
	PARENT_SCOPE)

set(CLA3P_LINSOL_HPP 
	dns_lsolver_base.hpp
	dns_auto_lsolver.hpp
	dns_llt_lsolver.hpp
	dns_ldlt_lsolver.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_LINSOL_HPP_INSTALL include/cla3p/linsol)

install(FILES ${CLA3P_LINSOL_HPP} DESTINATION ${CLA3P_LINSOL_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
