#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	proxies/blas_proxy.cpp
	proxies/lapack_proxy.cpp
	proxies/mkl_proxy.cpp
	PARENT_SCOPE)

set(CLA3P_PROXY_HPP 
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_PROXY_HPP_INSTALL include/cla3p/proxies)

install(FILES ${CLA3P_PROXY_HPP} DESTINATION ${CLA3P_PROXY_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
