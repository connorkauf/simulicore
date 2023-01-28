#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/test.hpp"
//#include "cla3p/src/types.hpp"
//#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
//#include "cla3p/src/dns.hpp"
//#include "cla3p/src/dns_io.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/mkl_proxy.hpp"
#include "cla3p/src/dns_generic.hpp"
/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

	cla3p::uint_t m = 10;
	cla3p::uint_t n = 10;
	cla3p::Property prop(cla3p::prop_t::SYMMETRIC);
	
	cla3p::dns::GenericObject<cla3p::real_t> ob1 = cla3p::dns::GenericObject<cla3p::real_t>::random(prop, m, n);
	cla3p::dns::GenericObject<cla3p::complex_t> ob3 = cla3p::dns::GenericObject<cla3p::complex_t>::random(prop, m/2, n/2);

	cla3p::dns::GenericObject<cla3p::real_t> ob2;
	ob1.print();
	ob2 = ob1.move();
	ob2.print();

	return 0;
}
/*-------------------------------------------------*/
