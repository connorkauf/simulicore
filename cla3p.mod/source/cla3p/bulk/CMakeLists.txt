#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	bulk/dns.cpp
	bulk/dns_io.cpp
	bulk/dns_math.cpp
	bulk/csc.cpp
	bulk/csc_math.cpp
	PARENT_SCOPE)

set(CLA3P_BULK_HPP 
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_BULK_HPP_INSTALL include/cla3p/bulk)

install(FILES ${CLA3P_BULK_HPP} DESTINATION ${CLA3P_BULK_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
