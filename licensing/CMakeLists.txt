set(LICENSE_FILES 
	${SIMULICORE_ROOT}/LICENSE
	${SIMULICORE_ROOT}/NOTICE
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(LICENSE_INSTALL license)

install(FILES ${LICENSE_FILES} DESTINATION ${LICENSE_INSTALL})

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(intel_mkl)
add_subdirectory(armpl)

#-----------------------------------------------
# end
#-----------------------------------------------
