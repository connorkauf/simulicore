set(CONFIG_3RD
	cmake.mkl.in
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CONFIG_3RD_INSTALL 3rd)

install(FILES ${CONFIG_3RD} DESTINATION ${CONFIG_3RD_INSTALL})

