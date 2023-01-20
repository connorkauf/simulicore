#include <iostream>
#include <cstdio>

#include <omp.h>

#include "cla3p/src/test.hpp"
#include "cla3p/src/types.hpp"
#include "cla3p/src/error.hpp"
#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/dns.hpp"
#include "cla3p/src/dns_io.hpp"
/*-------------------------------------------------*/
#if 0
static void omp_print()
{
	printf("tid: %d in parallel: %d dynamic: %d max levels: %d num procs: %d num threads: %d max threads: %d\n", 
			omp_get_thread_num(),
			omp_get_dynamic(),
			omp_get_max_active_levels(),
			omp_in_parallel(),
			omp_get_num_procs(),
			omp_get_num_threads(),
			omp_get_max_threads()
			);
}
#endif
/*-------------------------------------------------*/
//using namespace cla3p;
int main()
{
#if 1
	cla3p::uint_t m = 7;
	cla3p::uint_t n = 10;
	cla3p::uint_t lda = m + 10;

	cla3p::real_t *a = cla3p::dns::rnew(m, n, lda);
	cla3p::complex_t *b = cla3p::dns::cnew(m, n, lda);

	bool lower = false;
	cla3p::uint_t nsd = 6;
	cla3p::uint_t line_maxlen = 128;

	cla3p::dns::print(m, n, a, lda, lower, nsd, line_maxlen);
	cla3p::dns::print(m, n, b, lda, lower, nsd, line_maxlen);

	cla3p::i_free(a);
	cla3p::i_free(b);
#else
	cla3p::complex_t c1 = cla3p::cval(1,2);
	cla3p::complex_t c2 = cla3p::cval(3,5);
	std::cout << "complex1: '" << c1 << "'\n";
	std::cout << "complex2: '" << c2 << "'\n";
	std::cout << "complex1+2: '" << c1 + c2 << "'\n";
	std::cout << "complex1-2: '" << c1 - c2 << "'\n";
	std::cout << "complex1*2: '" << c1 * c2 << "'\n";
	std::cout << "complex1/2: '" << c1 / c2 << "'\n";
#endif

}
/*-------------------------------------------------*/
