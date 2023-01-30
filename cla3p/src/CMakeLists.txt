#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC
	types.cpp
	error.cpp
	error_internal.cpp
	utils.cpp
	imalloc.cpp
	dns_generic.cpp
	)

set(CLA3P_HPP
	types.hpp
	error.hpp
	dns_generic.hpp
	)

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(bulk)
add_subdirectory(proxies)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_library(${CLA3P_LIB} SHARED ${CLA3P_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_include_directories(${CLA3P_LIB} PRIVATE ${MKL_INC})
target_link_libraries(${CLA3P_LIB} ${MKL_LIB})

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_HPP_INSTALL include/cla3p)
set(CLA3P_LIB_INSTALL lib)

install(FILES   ${CLA3P_HPP} DESTINATION ${CLA3P_HPP_INSTALL})
install(TARGETS ${CLA3P_LIB} DESTINATION ${CLA3P_LIB_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
