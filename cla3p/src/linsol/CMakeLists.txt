#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	linsol/lapack_solvers.cpp
	PARENT_SCOPE)

set(CLA3P_LINSOL_HPP 
	lapack_solvers.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_LINSOL_HPP_INSTALL include/cla3p/linsol)

install(FILES ${CLA3P_LINSOL_HPP} DESTINATION ${CLA3P_LINSOL_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
