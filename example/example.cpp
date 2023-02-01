#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/types.hpp"
#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/dns_generic.hpp"
#include "cla3p/src/dns_dmat.hpp"

#include "cla3p/src/proxies/mkl_proxy.hpp"
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
/*-------------------------------------------------*/
using namespace cla3p;
using namespace cla3p::dns;

int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

	uint_t m = 3;
	uint_t n = 3;

	dMat A;
	try {
		A = dMat::random(prop_t::SYMMETRIC, m, n, m+2);
	} catch (const NoConsistency& exc2) {
		printf("CAUGHT CONSISTENCY EXCEPTION\n");
	} catch (const Exception& exc1) {
		printf("CAUGHT EXCEPTION\n");
	} // exception

	A(5,7) = 0;

	dMat B = dMat::random(m, 2);
	A.info("A");
	B.info("B");
	A.print();
	B.print();

	A = B.copy().move().move().move();
	A.info("A");
	B.info("B");

	return 0;
}
/*-------------------------------------------------*/
