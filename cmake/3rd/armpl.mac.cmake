set(ARMPL_ROOT /opt/arm/armpl_24.04_flang-new_clang_18)

#
# definitions
#
set(ARMPL_DEF armpl_singlecomplex_t=std::complex<float> armpl_doublecomplex_t=std::complex<double>)
set(ARMPL_I64_DEF armpl_singlecomplex_t=std::complex<float> armpl_doublecomplex_t=std::complex<double> INTEGER64)

#
# include
#
set(ARMPL_INC ${ARMPL_ROOT}/include)

#
# library path
#
set(ARMPL_LIB_DIR ${ARMPL_ROOT}/lib)

#
# libraries
#
set(ARMPL_LIB -L${ARMPL_LIB_DIR} -larmpl_lp64_mp)
set(ARMPL_I64_LIB -L${ARMPL_LIB_DIR} -larmpl_ilp64_mp)

# 
# extra libs (at the moment for MacOS only)
#
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(ARMPL_LIB ${ARMPL_LIB} -lFortranRuntime -lFortranDecimal -lm -lc++)
	set(ARMPL_I64_LIB ${ARMPL_I64_LIB} -lFortranRuntime -lFortranDecimal -lm -lc++)
else()
	set(ARMPL_LIB ${ARMPL_LIB} -lm)
	set(ARMPL_I64_LIB ${ARMPL_I64_LIB} -lm)
endif()
