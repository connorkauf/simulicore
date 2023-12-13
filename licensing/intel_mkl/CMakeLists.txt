set(INTEL_MKL_LICENSE_FILES 
	license.txt
	third-party-programs-benchmarks.txt
	third-party-programs-ipp.txt
	third-party-programs-openmp.txt
	third-party-programs-safestring.txt
	third-party-programs.txt
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(INTEL_MKL_LICENSE_INSTALL license/intel_mkl)

install(FILES ${INTEL_MKL_LICENSE_FILES} DESTINATION ${INTEL_MKL_LICENSE_INSTALL})
