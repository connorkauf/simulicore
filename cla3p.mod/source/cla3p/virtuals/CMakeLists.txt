#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	virtuals/virtual_object.cpp
	virtuals/virtual_prod.cpp
	PARENT_SCOPE)

set(CLA3P_VIRTUALS_HPP 
	virtual_entity.hpp
	virtual_object.hpp
	virtual_prod.hpp
	virtual_sum.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_VIRTUALS_HPP_INSTALL include/cla3p/virtuals)

install(FILES ${CLA3P_VIRTUALS_HPP} DESTINATION ${CLA3P_VIRTUALS_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
