#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	sparse/csc_xxobject.cpp
	sparse/csc_xxmatrix.cpp
	sparse/csc_rxmatrix.cpp
	sparse/csc_cxmatrix.cpp
	sparse/coo_xxmatrix.cpp
	sparse/coo_rxmatrix.cpp
	sparse/coo_cxmatrix.cpp
	PARENT_SCOPE)

set(CLA3P_SPARSE_HPP 
	csc_xxobject.hpp
	csc_xxmatrix.hpp
	csc_rxmatrix.hpp
	csc_cxmatrix.hpp
	coo_xxmatrix.hpp
	coo_rxmatrix.hpp
	coo_cxmatrix.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_SPARSE_HPP_INSTALL include/cla3p/sparse)

install(FILES ${CLA3P_SPARSE_HPP} DESTINATION ${CLA3P_SPARSE_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
