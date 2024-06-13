#-----------------------------------------------
# set 3rd parties
#-----------------------------------------------

set(CLA3P_3RD_PARTY_DEF )
set(CLA3P_3RD_PARTY_I64_DEF CLA3P_I64)
set(CLA3P_3RD_PARTY_INC )
set(CLA3P_3RD_PARTY_LIB )
set(CLA3P_3RD_PARTY_I64_LIB )

#-----------------------------------------------
# set openmp
#-----------------------------------------------
include(${SIMULICORE_ROOT}/cmake/openmp.cmake)

if(${SIMULICORE_CMAKE_MACOS})
	set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${MACOS_OMP_INC})
	set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${MACOS_OMP_LIB})
	set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} ${MACOS_OMP_LIB})
endif()

#-----------------------------------------------
# armpl/accelerate setup
#-----------------------------------------------
set(CLA3P_CMAKE_ARMPL false)
if(${SIMULICORE_CMAKE_MACOS})

	# definitions
	# set(CLA3P_3RD_PARTY_DEF ${CLA3P_3RD_PARTY_DEF} ACCELERATE_NEW_LAPACK)
	# set(CLA3P_3RD_PARTY_I64_DEF ${CLA3P_3RD_PARTY_I64_DEF} ACCELERATE_NEW_LAPACK ACCELERATE_LAPACK_ILP64)
	# libraries
	# set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} "-framework Accelerate")
	# set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} "-framework Accelerate")

	include(${SIMULICORE_ROOT}/cmake/3rd/armpl.mac.cmake)

	message(STATUS "Arm Performance Libraries Root: ${ARMPL_ROOT}")
	message(STATUS "Arm Performance Libraries Root: ${ARMPL_ROOT}")

	set(CLA3P_CMAKE_ARMPL true)

	# definitions
	set(CLA3P_3RD_PARTY_DEF ${CLA3P_3RD_PARTY_DEF} ${ARMPL_DEF} CLA3P_ARMPL)
	set(CLA3P_3RD_PARTY_I64_DEF ${CLA3P_3RD_PARTY_I64_DEF} ${ARMPL_I64_DEF} CLA3P_ARMPL)
	# includes
	set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${ARMPL_INC})
	# libraries
	set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${ARMPL_LIB})
	set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} ${ARMPL_I64_LIB})

endif()

if(${SIMULICORE_CMAKE_LINUX_ARM64} OR ${SIMULICORE_CMAKE_WIN32_ARM64})
	message(FATAL "Arm Performance Libraries for Linux/Windows not yet supported")
endif()

#-----------------------------------------------
# mkl setup
#-----------------------------------------------
set(CLA3P_CMAKE_INTEL_MKL false)
if(${SIMULICORE_CMAKE_LINUX_X86_64} OR ${SIMULICORE_CMAKE_WIN32_X86_64})

	if(${SIMULICORE_CMAKE_LINUX_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.lin.cmake)
	elseif(${SIMULICORE_CMAKE_WIN32_X86_64})
		include(${SIMULICORE_ROOT}/cmake/3rd/mkl.win.cmake)
	endif()

	message(STATUS "Intel MKL Root: ${INTEL_MKL_ROOT}")
	message(STATUS "Intel ICC Root: ${INTEL_ICC_ROOT}")

	set(CLA3P_CMAKE_INTEL_MKL true)

	# definitions
	set(CLA3P_3RD_PARTY_DEF ${CLA3P_3RD_PARTY_DEF} ${INTEL_MKL_DEF} CLA3P_INTEL_MKL)
	set(CLA3P_3RD_PARTY_I64_DEF ${CLA3P_3RD_PARTY_I64_DEF} ${INTEL_MKL_I64_DEF} CLA3P_INTEL_MKL)

	# includes
	set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${INTEL_MKL_INC})

	# libraries
	set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${INTEL_MKL_LIB})
	set(CLA3P_3RD_PARTY_I64_LIB ${CLA3P_3RD_PARTY_I64_LIB} ${INTEL_MKL_I64_LIB})

endif()

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(cla3p)

#-----------------------------------------------
# end
#-----------------------------------------------
