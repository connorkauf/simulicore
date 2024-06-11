set(CONFIG_3RD 
	mkl.md
	mkl.lin.cmake
	mkl.win.cmake
	armpl.mac.cmake
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CONFIG_3RD_INSTALL cmake/3rd)

install(FILES ${CONFIG_3RD} DESTINATION ${CONFIG_3RD_INSTALL})

