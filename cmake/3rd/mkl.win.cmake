set(INTEL_MKL_ROOT "C:/Program Files (x86)/Intel/oneAPI/mkl/2023.2.0")
set(INTEL_ICC_ROOT "C:/Program Files (x86)/Intel/oneAPI/compiler/2023.2.0")

#
# definitions
#
set(INTEL_MKL_DEF MKL_Complex8=std::complex<float> MKL_Complex16=std::complex<double>)
set(INTEL_MKL_I64_DEF MKL_Complex8=std::complex<float> MKL_Complex16=std::complex<double> MKL_ILP64)

#
# include
#
set(INTEL_MKL_INC ${INTEL_MKL_ROOT}/include)

#
# library paths
#
set(INTEL_MKL_LIB_DIR ${INTEL_MKL_ROOT}/lib/intel64)
set(INTEL_MKL_DLL_DIR ${INTEL_MKL_ROOT}/redist/intel64)
set(INTEL_ICC_LIB_DIR ${INTEL_ICC_ROOT}/windows/compiler/lib/intel64_win)
set(INTEL_ICC_DLL_DIR ${INTEL_ICC_ROOT}/windows/redist/intel64_win/compiler)

#
# libraries
#
set(INTEL_MKL_LIB 
	${INTEL_MKL_LIB_DIR}/mkl_intel_lp64_dll.lib 
	${INTEL_MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
	${INTEL_MKL_LIB_DIR}/mkl_core_dll.lib 
	${INTEL_ICC_LIB_DIR}/libiomp5md.lib)

set(INTEL_MKL_I64_LIB 
	${INTEL_MKL_LIB_DIR}/mkl_intel_ilp64_dll.lib 
	${INTEL_MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
	${INTEL_MKL_LIB_DIR}/mkl_core_dll.lib 
	${INTEL_ICC_LIB_DIR}/libiomp5md.lib)
