#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	checks/basic_checks.cpp
	checks/block_ops_checks.cpp
	checks/dns_checks.cpp
	checks/csc_checks.cpp
	checks/coo_checks.cpp
	checks/lapack_checks.cpp
	checks/hermitian_coeff_checks.cpp
	checks/matrix_math_checks.cpp
	checks/perm_checks.cpp
	checks/transp_checks.cpp
	checks/outer_checks.cpp
	PARENT_SCOPE)

set(CLA3P_CHECKS_HPP 
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_CHECKS_HPP_INSTALL include/cla3p/checks)

install(FILES ${CLA3P_CHECKS_HPP} DESTINATION ${CLA3P_CHECKS_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
