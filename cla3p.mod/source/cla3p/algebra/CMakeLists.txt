#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	PARENT_SCOPE)

set(CLA3P_ALGEBRA_HPP 
	functional.hpp
	operators_add.hpp
	operators_update.hpp
	operators_scale.hpp
	operators_multvv.hpp
	operators_multmv.hpp
	operators_multmm.hpp
	operators_perm.hpp
	operators_linsol.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_ALGEBRA_HPP_INSTALL include/cla3p/algebra)

install(FILES ${CLA3P_ALGEBRA_HPP} DESTINATION ${CLA3P_ALGEBRA_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
