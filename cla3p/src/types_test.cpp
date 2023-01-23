// this file inc
#include "types_test.hpp"

// system
#include <complex>

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
int_t test_complex()
{
#define check_res(x, y) \
	do{ \
		if(x.real != y.real() || x.imag != y.imag()) return 1; \
	} while(0)
	complex_t c1 = cval( 3., -2.);
	complex_t c2 = cval(-9.,  5.);
	complex_t c3;

	std::complex<real_t> cc1(c1.real, c1.imag);
	std::complex<real_t> cc2(c2.real, c2.imag);
	std::complex<real_t> cc3;

	c3 = c1 + c2; cc3 = cc1 + cc2; check_res(c3, cc3);
	c3 = c1 - c2; cc3 = cc1 - cc2; check_res(c3, cc3);
	c3 = c1 * c2; cc3 = cc1 * cc2; check_res(c3, cc3);
	c3 = c1 / c2; cc3 = cc1 / cc2; check_res(c3, cc3);
#undef check_res

	return 0;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
