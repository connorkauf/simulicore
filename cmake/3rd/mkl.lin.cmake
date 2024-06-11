set(INTEL_MKL_ROOT /opt/intel/oneapi/mkl/2023.2.0)
set(INTEL_ICC_ROOT /opt/intel/oneapi/compiler/2023.2.0)

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
set(INTEL_ICC_LIB_DIR ${INTEL_ICC_ROOT}/linux/compiler/lib/intel64_lin)

# 
# libraries
#
set(INTEL_MKL_LIB 
	-L${INTEL_MKL_LIB_DIR}
	-Wl,--no-as-needed 
	-lmkl_intel_lp64 
	-lmkl_intel_thread 
	-lmkl_core 
	-L${INTEL_ICC_LIB_DIR} -liomp5
	-lpthread -lm -ldl)

set(INTEL_MKL_I64_LIB 
	-L${INTEL_MKL_LIB_DIR} 
	-Wl,--no-as-needed 
	-lmkl_intel_ilp64 
	-lmkl_intel_thread 
	-lmkl_core 
	-L${INTEL_ICC_LIB_DIR} -liomp5
	-lpthread -lm -ldl)
