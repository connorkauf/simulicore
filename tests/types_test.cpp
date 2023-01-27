// this file inc
#include "types_test.hpp"
#include "test_macros.hpp"

// system
#include <iostream>

// 3rd
#include "mkl.h"

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace tests {
/*-------------------------------------------------*/
int_t datatypes(bool strict)
{
#if defined (CLA3P_I64)
	if(sizeof( int_t) != 8) fatal_error();
	if(sizeof(uint_t) != 8) fatal_error();
#else
	if(sizeof( int_t) != 4) fatal_error();
	if(sizeof(uint_t) != 4) fatal_error();
#endif

	if(sizeof( int_t) != sizeof(MKL_INT )) fatal_error();
	if(sizeof(uint_t) != sizeof(MKL_UINT)) fatal_error();

	test_success();
	return 0;
}
/*-------------------------------------------------*/
} // namespace tests
} // namespace cla3p
/*-------------------------------------------------*/
