#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	dense/dns_rdvector.cpp
	dense/dns_rfvector.cpp
	dense/dns_rivector.cpp
	dense/dns_cdvector.cpp
	dense/dns_cfvector.cpp
	dense/dns_rdmatrix.cpp
	dense/dns_rfmatrix.cpp
	dense/dns_rimatrix.cpp
	dense/dns_cdmatrix.cpp
	dense/dns_cfmatrix.cpp
	# new hierarchy
	dense/dns_xxvector.cpp
	dense/dns_rxvector.cpp
	dense/dns_cxvector.cpp
	PARENT_SCOPE)

set(CLA3P_DENSE_HPP 
	dns_rdvector.hpp
	dns_rfvector.hpp
	dns_rivector.hpp
	dns_cdvector.hpp
	dns_cfvector.hpp
	dns_rdmatrix.hpp
	dns_rfmatrix.hpp
	dns_rimatrix.hpp
	dns_cdmatrix.hpp
	dns_cfmatrix.hpp
	# new hierarchy
	dns_xxvector.hpp
	dns_rxvector.hpp
	dns_cxvector.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_DENSE_HPP_INSTALL include/cla3p/dense)

install(FILES ${CLA3P_DENSE_HPP} DESTINATION ${CLA3P_DENSE_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
