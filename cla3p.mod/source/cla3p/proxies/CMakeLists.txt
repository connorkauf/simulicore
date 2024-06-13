#-----------------------------------------------
# source setup
#-----------------------------------------------
if(${CLA3P_CMAKE_INTEL_MKL})
	set(CLA3P_MKL_SRC
		proxies/mkl_proxy.cpp
		proxies/mkl_sparse_proxy.cpp
		proxies/mkl_pardiso_proxy.cpp
		)
endif()

if(${CLA3P_CMAKE_ARMPL})
	set(CLA3P_ARMPL_SRC
		proxies/armpl_sparse_proxy.cpp
		)
endif()

set(CLA3P_SRC ${CLA3P_SRC}
	proxies/blas_proxy.cpp
	proxies/lapack_proxy.cpp
	${CLA3P_MKL_SRC}
	${CLA3P_ARMPL_SRC}
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
