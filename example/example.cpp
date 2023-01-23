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
#include "cla3p/src/mkl_proxy.hpp"


#include "cla3p/src/types_test.hpp"
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

	cla3p::ptype_t ptype = cla3p::ptype_t::GENERAL;
	cla3p::Property prop;
	cla3p::Property psym(cla3p::ptype_t::SYMMETRIC);
	std::cout << "pname0: " << prop.name() << std::endl;
	std::cout << "pname1: " << psym.name() << std::endl;
	prop = psym;
	std::cout << "pname0: " << prop.name() << std::endl;
	std::cout << "pname1: " << psym.name() << std::endl;
	prop = cla3p::Property();
	std::cout << "pname0: " << prop.name() << std::endl;
	std::cout << "pname1: " << psym.name() << std::endl;

	return 0;

	cla3p::uint_t m = 5;
	cla3p::uint_t n = 3;
	cla3p::uint_t lda = m + 2;
	cla3p::uint_t ldb = n + 2;

	{
		cla3p::real_t *a = cla3p::dns::alloc<cla3p::real_t>(m, n, lda);
		cla3p::real_t *b = cla3p::dns::alloc<cla3p::real_t>(n, m, lda);
		cla3p::dns::rand(m, n, a, lda);
		cla3p::dns::print(m, n, a, lda);
		cla3p::dns::transpose(m, n, a, lda, b, ldb, -1.0);
		cla3p::dns::print(n, m, b, ldb);
	}

	{
		//cla3p::complex_t *a = cla3p::dns::znew(m, n, lda);
		//cla3p::dns::rand(m, n, a, lda);
		//cla3p::dns::print(lda, n, a, lda);
	}

}
/*-------------------------------------------------*/
