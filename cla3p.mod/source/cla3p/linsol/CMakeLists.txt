#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	linsol/lapack_base.cpp
	linsol/pardiso_options.cpp
	linsol/pardiso_base.cpp
	PARENT_SCOPE)

set(CLA3P_LINSOL_HPP 
	lapack_base.hpp
	lapack_auto.hpp
	lapack_llt.hpp
	lapack_ldlt.hpp
	lapack_lu.hpp
	lapack_complete_lu.hpp
	pardiso_options.hpp
	pardiso_base.hpp
	pardiso_auto.hpp
	pardiso_llt.hpp
	pardiso_ldlt.hpp
	pardiso_lu.hpp
	pardiso_symmetric_lu.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_LINSOL_HPP_INSTALL include/cla3p/linsol)

install(FILES ${CLA3P_LINSOL_HPP} DESTINATION ${CLA3P_LINSOL_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
