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

	cla3p::uint_t m = 3;
	cla3p::uint_t n = 3;
	/* */ cla3p::dns::dMat A = cla3p::dns::dMat::random(m, n);
	A.info("A");
	const cla3p::dns::dMat B = cla3p::dns::dMat::random(m, n);
	B.info("B");

	cla3p::dns::dMat  mA = cla3p::dns::dMat::map(A.prop(),m,n,A.values(),A.ld(), false);
	mA.info("A");
	cla3p::dns::dMMap mB = cla3p::dns::dMat::map(B.prop(),m,n,B.values(),B.ld());
	mB.mat().info("B");

	return 0;
}
/*-------------------------------------------------*/
