set(LICENSE_FILES 
	${COMPACT_SUITE_ROOT}/LICENSE
	${COMPACT_SUITE_ROOT}/NOTICE
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(LICENSE_INSTALL license)

install(FILES ${LICENSE_FILES} DESTINATION ${LICENSE_INSTALL})

