#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	generic/universal.cpp
	generic/guard.cpp
	generic/generic_dns.cpp
	PARENT_SCOPE)

set(CLA3P_GENERIC_HPP 
	universal.hpp
	guard.hpp
	generic_dns.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_GENERIC_HPP_INSTALL include/cla3p/generic)

install(FILES ${CLA3P_GENERIC_HPP} DESTINATION ${CLA3P_GENERIC_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
