#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	perms/pxmatrix.cpp
	PARENT_SCOPE)

set(CLA3P_PERMS_HPP 
	pxmatrix.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_PERMS_HPP_INSTALL include/cla3p/perms)

install(FILES ${CLA3P_PERMS_HPP} DESTINATION ${CLA3P_PERMS_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
