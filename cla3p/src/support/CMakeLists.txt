#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	support/error.cpp
	support/error_internal.cpp
	support/imalloc.cpp
	support/utils.cpp
	PARENT_SCOPE)

set(CLA3P_SUPPORT_HPP 
	error.hpp
	imalloc.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_SUPPORT_HPP_INSTALL include/cla3p/support)

install(FILES ${CLA3P_SUPPORT_HPP} DESTINATION ${CLA3P_SUPPORT_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
