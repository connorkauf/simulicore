#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/types.hpp"
//#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/dns_generic.hpp"
#include "cla3p/src/dns_dmat.hpp"

#include "cla3p/src/proxies/mkl_proxy.hpp"
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

#if 0
	cla3p::uint_t m = 3;
	cla3p::uint_t n = 3;
	cla3p::Property prop(cla3p::prop_t::HERMITIAN);
	cla3p::dns::dMat A = cla3p::dns::dMat::random(prop, m, n);
	A.info();
	cla3p::dns::dMat B = A.move();
	A.info("A");
	B.info();

	std::cout << B(3,3) << std::endl;;
	//A(2,1) = -1.;
	//std::cout << A(2,1) << std::endl;;
#endif

#if 1
	cla3p::dns::GenericMap<cla3p::dns::dMat> mC1;
	cla3p::dns::GenericMap<cla3p::dns::dMat> mC2;
	mC1 = mC2;
#else
	cla3p::dns::dMMap mA;
	cla3p::dns::dMMap mB;
	mB = mA;
#endif


	return 0;
}
/*-------------------------------------------------*/
