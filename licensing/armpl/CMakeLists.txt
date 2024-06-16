set(ARMPL_LICENSE_FILES 
	license_agreement.txt
	third_party_licenses.txt
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(ARMPL_LICENSE_INSTALL license/armpl)

install(FILES ${ARMPL_LICENSE_FILES} DESTINATION ${ARMPL_LICENSE_INSTALL})
