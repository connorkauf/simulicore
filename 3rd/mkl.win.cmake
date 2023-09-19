set(MKL_ROOT "C:/Program Files (x86)/Intel/oneAPI/mkl/2023.2.0")
set(ICC_ROOT "C:/Program Files (x86)/Intel/oneAPI/compiler/2023.2.0/windows/compiler")

set(ICC_LIB_DIR "${ICC_ROOT}/lib/intel64_win")
set(IOMP5_LIB "${ICC_LIB_DIR}/libiomp5md.lib")

set(MKL_INC "${MKL_ROOT}/include")
set(MKL_LIB_DIR "${MKL_ROOT}/lib/intel64")

if(CLA3P_USE_I64)
	message(STATUS "Configuring Intel MKL (64bit integers)...")
	add_definitions(-DMKL_ILP64)
	set(MKL_LIB 
		${MKL_LIB_DIR}/mkl_intel_ilp64_dll.lib 
		${MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
		${MKL_LIB_DIR}/mkl_core_dll.lib 
		${IOMP5_LIB})
else()
	message(STATUS "Configuring Intel MKL (32bit integers)...")
	set(MKL_LIB 
		${MKL_LIB_DIR}/mkl_intel_lp64_dll.lib 
		${MKL_LIB_DIR}/mkl_intel_thread_dll.lib 
		${MKL_LIB_DIR}/mkl_core_dll.lib 
		${IOMP5_LIB})
endif()
