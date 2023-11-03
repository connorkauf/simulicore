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

set(CLA3P_3RD_PARTY_INC)
set(CLA3P_3RD_PARTY_LIB)
set(CLA3P_3RD_PARTY_I64_LIB)

# mkl setup
add_definitions(-DMKL_Complex8=std::complex<float>)
add_definitions(-DMKL_Complex16=std::complex<double>)
if(LINUX)
  include(${COMPACT_SUITE_ROOT}/3rd/mkl.lin.cmake)
elseif(WIN32)
  include(${COMPACT_SUITE_ROOT}/3rd/mkl.win.cmake)
endif()
set(CLA3P_3RD_PARTY_INC ${CLA3P_3RD_PARTY_INC} ${MKL_INC})
set(CLA3P_3RD_PARTY_LIB ${CLA3P_3RD_PARTY_LIB} ${MKL_LIB})
set(CLA3P_3RD_PARTY_I64_LIB  ${CLA3P_3RD_PARTY_I64_LIB} ${MKL_I64_LIB})

#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(cla3p)

#-----------------------------------------------
# end
#-----------------------------------------------
