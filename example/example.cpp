#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

#include "cla3p/src/test.hpp"
#include "cla3p/src/types.hpp"
#include "cla3p/src/error.hpp"
#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/dns.hpp"
#include "cla3p/src/dns_io.hpp"
#include "cla3p/src/mkl_proxy.hpp"

/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());

	cla3p::uint_t m = 10;
	cla3p::uint_t n =  8;
	cla3p::uint_t lda = m + 5;

	cla3p::real_t *a = cla3p::dns::alloc<cla3p::real_t>(m, n, lda);
	cla3p::dns::fill(cla3p::prop_t::GENERAL, m, n, a, lda, 1.);
	cla3p::dns::print(m, n, a, lda);
	cla3p::dns::scale(cla3p::prop_t::GENERAL, m, n, a, lda, 2.);
	cla3p::dns::print(m, n, a, lda);

	return 0;
}
/*-------------------------------------------------*/
