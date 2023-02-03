// this file inc
#include "utils_test.hpp"
#include "test_macros.hpp"

// system
#include <iostream>

// 3rd
#include "mkl.h"

// cla3p
#include "cla3p/src/support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace tests {
/*-------------------------------------------------*/
static int_t number_length(bool strict)
{
	uint_t u0 = 0        ; uint_t lenu0 = 1;
	uint_t u1 = 1234     ; uint_t lenu1 = 4;
	uint_t u2 = 123456789; uint_t lenu2 = 9;

	int_t i0 =  0      ; uint_t leni0 = 1;
	int_t i1 =  12345  ; uint_t leni1 = 5;
	int_t i2 = -1234567; uint_t leni2 = 7;

	if(inumlen(u0) != lenu0) fatal_error();
	if(inumlen(u1) != lenu1) fatal_error();
	if(inumlen(u2) != lenu2) fatal_error();
	if(inumlen(i0) != leni0) fatal_error();
	if(inumlen(i1) != leni1) fatal_error();
	if(inumlen(i2) != leni2) fatal_error();

	test_success();
}
/*-------------------------------------------------*/
static int_t random_numbers(bool strict)
{
	int_t   ilow = -10 ; int_t   ihigh = 10 ;
	uint_t  ulow =   5 ; uint_t  uhigh = 18 ;
	real_t  dlow = -10.; real_t  dhigh = 17.;
	real4_t slow = -12.; real4_t shigh = 15.;

	for(uint_t k = 0; k < 1000; k++) {
		int_t      i = irand(ilow, ihigh);
		uint_t     u = urand(ulow, uhigh);
		real_t     d = drand(dlow, dhigh);
		real4_t    s = srand(slow, shigh);
		complex_t  z = zrand(dlow, dhigh);
		complex8_t c = crand(slow, shigh);

		if(!(ilow <= i        && i        <= ihigh)) fatal_error();
		if(!(ulow <= u        && u        <= uhigh)) fatal_error();
		if(!(dlow <= d        && d        <= dhigh)) fatal_error();
		if(!(slow <= s        && s        <= shigh)) fatal_error();
		if(!(dlow <= z.real() && z.real() <= dhigh)) fatal_error();
		if(!(slow <= c.real() && c.real() <= shigh)) fatal_error();
		if(!(dlow <= z.imag() && z.imag() <= dhigh)) fatal_error();
		if(!(slow <= c.imag() && c.imag() <= shigh)) fatal_error();
	} // k

	test_success();
}
/*-------------------------------------------------*/
int_t utilities(bool strict)
{
	int_t numtests = 0;
	int_t numfail = 0;

	numfail += number_length(strict); numtests++;
	numfail += random_numbers(strict); numtests++;

	print_summary();
}
/*-------------------------------------------------*/
} // namespace tests
} // namespace cla3p
/*-------------------------------------------------*/
