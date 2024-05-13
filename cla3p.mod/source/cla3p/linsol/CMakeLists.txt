#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	linsol/lapack_base.cpp
	linsol/lapack_auto.cpp
	linsol/lapack_llt.cpp
	linsol/lapack_ldlt.cpp
	linsol/lapack_lu.cpp
	linsol/lapack_complete_lu.cpp
	PARENT_SCOPE)

set(CLA3P_LINSOL_HPP 
	lapack_base.hpp
	lapack_auto.hpp
	lapack_llt.hpp
	lapack_ldlt.hpp
	lapack_lu.hpp
	lapack_complete_lu.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_LINSOL_HPP_INSTALL include/cla3p/linsol)

install(FILES ${CLA3P_LINSOL_HPP} DESTINATION ${CLA3P_LINSOL_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
