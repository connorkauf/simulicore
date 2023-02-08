#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

#include "cla3p/src/types.hpp"
#include "cla3p/src/dns_dmat.hpp"
#include "cla3p/src/prm_mat.hpp"

#include "cla3p/src/support/error.hpp"
#include "cla3p/src/support/error_internal.hpp"
#include "cla3p/src/support/imalloc.hpp"
#include "cla3p/src/support/utils.hpp"

#include "cla3p/src/proxies/mkl_proxy.hpp"

#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
/*-------------------------------------------------*/

int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

	cla3p::dns::dMat A(10,10);
	A.info("A");

	cla3p::dns::dMat B = A.move();
	A.info("A");
	B.info("B");

	cla3p::prm::pMat P(10);
	P.info("P");

	cla3p::prm::pMat Q = P.move();
	P.info("P");
	Q.info("Q");

	return 0;
}
/*-------------------------------------------------*/
