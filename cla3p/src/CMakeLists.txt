#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC
	)

set(CLA3P_HPP
	types.hpp
	support.hpp
	dense.hpp
	perms.hpp
	operations.hpp
	linsol.hpp
	)

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(types)
add_subdirectory(bulk)
add_subdirectory(checks)
add_subdirectory(proxies)
add_subdirectory(support)
add_subdirectory(generic)
add_subdirectory(dense)
add_subdirectory(perms)
add_subdirectory(operations)
add_subdirectory(linsol)

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
