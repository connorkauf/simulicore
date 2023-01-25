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
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());

	cla3p::uint_t m = 10;
	cla3p::uint_t n =  8;
	cla3p::uint_t ld = m + 12;

	cla3p::uint_t nsd = 2;
	//bool lower = false;
	bool lower = true;
	if(lower){
		m = std::min(m,n);
		n = std::min(m,n);
	}

	{
		cla3p::real_t     *d = cla3p::dns::alloc<cla3p::real_t    >(m,n,ld);
		cla3p::real4_t    *s = cla3p::dns::alloc<cla3p::real4_t   >(m,n,ld);
		cla3p::complex_t  *z = cla3p::dns::alloc<cla3p::complex_t >(m,n,ld);
		cla3p::complex8_t *c = cla3p::dns::alloc<cla3p::complex8_t>(m,n,ld);

		cla3p::dns::rand(m, n, d, ld);
		cla3p::dns::rand(m, n, s, ld);
		cla3p::dns::rand(m, n, z, ld);
		cla3p::dns::rand(m, n, c, ld);

		cla3p::dns::print(m, n, d, ld, lower, nsd);
		cla3p::dns::print(m, n, s, ld, lower, nsd);
		cla3p::dns::print(m, n, z, ld, lower, nsd);
		cla3p::dns::print(m, n, c, ld, lower, nsd);
	}
	
	return 0;
}
/*-------------------------------------------------*/
