set(MKL_ROOT /opt/intel/oneapi/mkl/2023.2.0)
set(ICC_ROOT /opt/intel/oneapi/compiler/2023.2.0/linux/compiler)

if(NOT EXISTS ${MKL_ROOT})
	message(FATAL_ERROR "Intel MKL root directory '${MKL_ROOT}' does not exist.")
endif()

if(NOT EXISTS ${ICC_ROOT})
	message(FATAL_ERROR "Intel Compiler root directory '${ICC_ROOT}' does not exist.")
endif()

set(ICC_LIB_DIR ${ICC_ROOT}/lib/intel64_lin)
set(IOMP5_LIB -L${ICC_LIB_DIR} -liomp5)

set(MKL_INC ${MKL_ROOT}/include)
set(MKL_LIB_DIR ${MKL_ROOT}/lib/intel64)

if(CLA3P_USE_I64)
	message(STATUS "Configuring Intel MKL (64bit integers)...")
	add_definitions(-DMKL_ILP64)
	set(MKL_LIB 
		-L${MKL_LIB_DIR} 
		-Wl,--no-as-needed 
		-lmkl_intel_ilp64 
		-lmkl_intel_thread 
		-lmkl_core 
		${IOMP5_LIB}
		-lpthread -lm -ldl)
else()
	message(STATUS "Configuring Intel MKL (32bit integers)...")
	set(MKL_LIB 
		-L${MKL_LIB_DIR}
		-Wl,--no-as-needed 
		-lmkl_intel_lp64 
		-lmkl_intel_thread 
		-lmkl_core 
		${IOMP5_LIB}
		-lpthread -lm -ldl)
endif()
