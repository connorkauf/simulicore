#-----------------------------------------------
# set library name
#-----------------------------------------------
set(CLA3P_INC "${CMAKE_CURRENT_SOURCE_DIR}/.." CACHE INTERNAL "The cla3p includes")
set(CLA3P_LIB "cla3p" CACHE INTERNAL "The lp64 cla3p library")
set(CLA3P_I64_LIB "${CLA3P_LIB}_i64" CACHE INTERNAL "The ilp64 cla3p library")

#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC
	)

set(CLA3P_HPP
	types.hpp
	error.hpp
	support.hpp
	dense.hpp
	sparse.hpp
	perms.hpp
	virtuals.hpp
	algebra.hpp
	linsol.hpp
	svd.hpp
	qr.hpp
	)

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(types)
add_subdirectory(error)
add_subdirectory(bulk)
add_subdirectory(checks)
add_subdirectory(proxies)
add_subdirectory(support)
add_subdirectory(generic)
add_subdirectory(dense)
add_subdirectory(sparse)
add_subdirectory(perms)
add_subdirectory(virtuals)
add_subdirectory(algebra)
add_subdirectory(linsol)
add_subdirectory(svd)
add_subdirectory(qr)

#-----------------------------------------------
# target setup
#-----------------------------------------------
add_library(${CLA3P_LIB} SHARED ${CLA3P_SRC})
add_library(${CLA3P_I64_LIB} SHARED ${CLA3P_SRC})

#-----------------------------------------------
# dependencies setup
#-----------------------------------------------
target_compile_definitions(${CLA3P_LIB} PRIVATE ${CLA3P_3RD_PARTY_DEF})
target_compile_definitions(${CLA3P_I64_LIB} PRIVATE ${CLA3P_3RD_PARTY_I64_DEF})

target_include_directories(${CLA3P_LIB} PRIVATE ${CLA3P_INC} ${CLA3P_3RD_PARTY_INC})
target_include_directories(${CLA3P_I64_LIB} PRIVATE ${CLA3P_INC} ${CLA3P_3RD_PARTY_INC})

target_link_libraries(${CLA3P_LIB} ${CLA3P_3RD_PARTY_LIB})
target_link_libraries(${CLA3P_I64_LIB} ${CLA3P_3RD_PARTY_I64_LIB})

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_HPP_INSTALL include/cla3p)
set(CLA3P_LIB_INSTALL lib)

install(FILES ${CLA3P_HPP} DESTINATION ${CLA3P_HPP_INSTALL})
install(TARGETS ${CLA3P_LIB} DESTINATION ${CLA3P_LIB_INSTALL})
install(TARGETS ${CLA3P_I64_LIB} DESTINATION ${CLA3P_LIB_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
