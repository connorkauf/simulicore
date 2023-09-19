set(CONFIG_3RD "")

if(LINUX)
	set(CONFIG_3RD ${CONFIG_3RD} mkl.lin.cmake)
endif()

if(WIN32)
	set(CONFIG_3RD ${CONFIG_3RD} mkl.win.cmake)
endif()

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CONFIG_3RD_INSTALL 3rd)

install(FILES ${CONFIG_3RD} DESTINATION ${CONFIG_3RD_INSTALL})

