#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	checks/all_checks.cpp
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
