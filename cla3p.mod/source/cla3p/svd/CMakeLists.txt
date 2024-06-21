#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	svd/default_svd.cpp
	PARENT_SCOPE)

set(CLA3P_SVD_HPP 
	default_svd.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_SVD_HPP_INSTALL include/cla3p/svd)

install(FILES ${CLA3P_SVD_HPP} DESTINATION ${CLA3P_SVD_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
