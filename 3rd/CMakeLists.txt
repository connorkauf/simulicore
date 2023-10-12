set(CONFIG_3RD 
	mkl.md
	mkl.lin.cmake
	mkl.win.cmake
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CONFIG_3RD_INSTALL 3rd)

install(FILES ${CONFIG_3RD} DESTINATION ${CONFIG_3RD_INSTALL})

