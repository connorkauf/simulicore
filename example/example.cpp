#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/test.hpp"
//#include "cla3p/src/types.hpp"
//#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/mkl_proxy.hpp"
#include "cla3p/src/dns_generic.hpp"

#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();


	cla3p::uint_t n = 10;
	std::vector<cla3p::uint_t> P = cla3p::create_random_perm(n);

	for(cla3p::uint_t i = 0; i < n; i++) printf("P[%3llu] = %3llu\n", i, P[i]);


	return 0;
}
/*-------------------------------------------------*/
