#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	qr/default_qr.cpp
	PARENT_SCOPE)

set(CLA3P_QR_HPP 
	default_qr.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_QR_HPP_INSTALL include/cla3p/qr)

install(FILES ${CLA3P_QR_HPP} DESTINATION ${CLA3P_QR_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
