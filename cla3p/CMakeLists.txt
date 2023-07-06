message(STATUS "Configuring ${CLA3P_LIB}...")

#-----------------------------------------------
# set module root
#-----------------------------------------------
set(CLA3P_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CLA3P_ROOT: ${CLA3P_ROOT}")

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(src)
add_subdirectory(doxy)
add_subdirectory(examples)

#-----------------------------------------------
# end
#-----------------------------------------------
