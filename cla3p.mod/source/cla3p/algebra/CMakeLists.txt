#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	algebra/functional_inner.cpp
	algebra/functional_outer.cpp
	algebra/functional_add.cpp
	algebra/functional_update.cpp
	algebra/functional_multmv.cpp
	algebra/functional_multmm.cpp
	algebra/operators_add.cpp
	algebra/operators_update.cpp
	algebra/operators_scale.cpp
	algebra/operators_multvv.cpp
	algebra/operators_multmv.cpp
	algebra/operators_multmm.cpp
	algebra/operators_perm.cpp
	algebra/operators_linsol.cpp
	PARENT_SCOPE)

set(CLA3P_ALGEBRA_HPP 
	functional_inner.hpp
	functional_outer.hpp
	functional_add.hpp
	functional_update.hpp
	functional_multmv.hpp
	functional_multmm.hpp
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
