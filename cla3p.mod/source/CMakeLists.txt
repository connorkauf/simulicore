#-----------------------------------------------
# set openmp
#-----------------------------------------------
include(${SIMULICORE_ROOT}/cmake/openmp.cmake)

#-----------------------------------------------
# set 3rd parties
#-----------------------------------------------

set(CLA3P_3RD_PARTY_DEF)
set(CLA3P_3RD_PARTY_I64_DEF CLA3P_I64)
set(CLA3P_3RD_PARTY_INC)
set(CLA3P_3RD_PARTY_LIB)
set(CLA3P_3RD_PARTY_I64_LIB)

# 
# accelerate setup
#
if(${SIMULICORE_CMAKE_MACOS})

	# definitions
	set(CLA3P_3RD_PARTY_DEF ${CLA3P_3RD_PARTY_DEF} ACCELERATE_NEW_LAPACK)
	set(CLA3P_3RD_PARTY_I64_DEF ${CLA3P_3RD_PARTY_I64_DEF} ACCELERATE_NEW_LAPACK ACCELERATE_LAPACK_ILP64)

	# includes
	set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${MACOS_OMP_INC})

	# libraries
	set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")
	set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} ${MACOS_OMP_LIB} "-framework Accelerate")

endif()

# 
# mkl setup
#
if(${SIMULICORE_CMAKE_LINUX_X86_64} OR ${SIMULICORE_CMAKE_WIN32_X86_64})

	if(${SIMULICORE_CMAKE_LINUX_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.lin.cmake)
	elseif(${SIMULICORE_CMAKE_WIN32_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.win.cmake)
	endif()

	message(STATUS "Intel MKL ROOT: ${MKL_ROOT}")
	message(STATUS "Intel ICC ROOT: ${ICC_ROOT}")

	# definitions
	set(CLA3P_MKL_DEFAULT_DEFS CLA3P_INTEL_MKL MKL_Complex8=std::complex<float> MKL_Complex16=std::complex<double>)
	set(CLA3P_3RD_PARTY_DEF ${CLA3P_3RD_PARTY_DEF} ${CLA3P_MKL_DEFAULT_DEFS})
	set(CLA3P_3RD_PARTY_I64_DEF ${CLA3P_3RD_PARTY_I64_DEF} ${CLA3P_MKL_DEFAULT_DEFS} MKL_ILP64)

	# includes
	set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${MKL_INC})

	# libraries
	set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${MKL_LIB})
	set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} ${MKL_I64_LIB})

endif()

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(cla3p)

#-----------------------------------------------
# end
#-----------------------------------------------
