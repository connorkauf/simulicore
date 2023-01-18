// this file inc
#include "types_test.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
int_t test_int_sizes()
{
#if defined (CLA3P_I64)
	if(sizeof( int_t) != 8LLU) return 1;
	if(sizeof(uint_t) != 8LLU) return 1;
#else
	if(sizeof( int_t) != 4LLU) return 1;
	if(sizeof(uint_t) != 4LLU) return 1;
#endif

	return 0;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
