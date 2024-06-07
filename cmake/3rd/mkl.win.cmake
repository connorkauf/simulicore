set(MKL_ROOT "C:/Program Files (x86)/Intel/oneAPI/mkl/2023.2.0")
set(ICC_ROOT "C:/Program Files (x86)/Intel/oneAPI/compiler/2023.2.0")

set(MKL_INC "${MKL_ROOT}/include")
set(MKL_LIB_DIR "${MKL_ROOT}/lib/intel64")
set(MKL_DLL_DIR "${MKL_ROOT}/redist/intel64")
set(ICC_LIB_DIR "${ICC_ROOT}/windows/compiler/lib/intel64_win")
set(ICC_DLL_DIR "${ICC_ROOT}/windows/redist/intel64_win/compiler")

set(MKL_LIB 
	${MKL_LIB_DIR}/mkl_intel_lp64_dll.lib 
	${MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
	${MKL_LIB_DIR}/mkl_core_dll.lib 
	${ICC_LIB_DIR}/libiomp5md.lib)

set(MKL_I64_LIB 
	${MKL_LIB_DIR}/mkl_intel_ilp64_dll.lib 
	${MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
	${MKL_LIB_DIR}/mkl_core_dll.lib 
	${ICC_LIB_DIR}/libiomp5md.lib)
