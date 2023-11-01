#-----------------------------------------------
# set library name
#-----------------------------------------------
set(CLA3P_LIB "cla3p")
set(CLA3P_I64_LIB "cla3p_i64")

message(STATUS "Configuring CLA3P...")

#-----------------------------------------------
# set module root
#-----------------------------------------------
set(CLA3P_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CLA3P Root Directory: ${CLA3P_ROOT}")

#-----------------------------------------------
# set openmp
#-----------------------------------------------
find_package(OpenMP)
if (OPENMP_FOUND)
  message(STATUS "Configuring OpenMP ${OpenMP_CXX_VERSION}...")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
  message(WARNING "OpenMP not found")
endif()

#-----------------------------------------------
# set 3rd parties
#-----------------------------------------------

# mkl setup
add_definitions(-DMKL_Complex8=std::complex<float>)
add_definitions(-DMKL_Complex16=std::complex<double>)
if(LINUX)
  include(${COMPACT_SUITE_ROOT}/3rd/mkl.lin.cmake)
elseif(WIN32)
  include(${COMPACT_SUITE_ROOT}/3rd/mkl.win.cmake)
endif()
message(STATUS "MKL_INC: ${MKL_INC}")
message(STATUS "MKL_LIB: ${MKL_LIB}")
message(STATUS "MKL_I64_LIB: ${MKL_I64_LIB}")

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(source)
add_subdirectory(examples)

if(COMPACT_SUITE_FULL_INSTALL)
	add_subdirectory(documentation)
	add_subdirectory(images)
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
