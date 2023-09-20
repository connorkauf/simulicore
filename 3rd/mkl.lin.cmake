set(MKL_ROOT /opt/intel/oneapi/mkl/2023.2.0)
set(ICC_ROOT /opt/intel/oneapi/compiler/2023.2.0)

set(MKL_INC ${MKL_ROOT}/include)
set(MKL_LIB_DIR ${MKL_ROOT}/lib/intel64)
set(ICC_LIB_DIR ${ICC_ROOT}/linux/compiler/lib/intel64_lin)

if(CLA3P_USE_I64)
	message(STATUS "Configuring Intel MKL (64bit integers)...")
	add_definitions(-DMKL_ILP64)
	set(MKL_LIB 
		-L${MKL_LIB_DIR} 
		-Wl,--no-as-needed 
		-lmkl_intel_ilp64 
		-lmkl_intel_thread 
		-lmkl_core 
		-L${ICC_LIB_DIR} -liomp5
		-lpthread -lm -ldl)
else()
	message(STATUS "Configuring Intel MKL (32bit integers)...")
	set(MKL_LIB 
		-L${MKL_LIB_DIR}
		-Wl,--no-as-needed 
		-lmkl_intel_lp64 
		-lmkl_intel_thread 
		-lmkl_core 
		-L${ICC_LIB_DIR} -liomp5
		-lpthread -lm -ldl)
endif()
