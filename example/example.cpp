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

	cla3p::uint_t m = 12;
	cla3p::uint_t n = 100;
	cla3p::uint_t ld = m + 15;
	cla3p::Property prop(cla3p::prop_t::GENERAL);

	cla3p::dns::dMat A = cla3p::dns::dMat::random(prop, m, n, ld);
	A.info("A");
	A.print();
	cla3p::dns::dMat B;
	B = A.move();
	A.info("A");
	B.info("B");

	cla3p::prm::pMat P = cla3p::prm::pMat::random(m);
	cla3p::prm::pMat Q = cla3p::prm::pMat::random(n);

	P.info("P");
	Q.info("Q");
	P.print();
	Q.print();

	cla3p::dns::dMat PAQ = B.permute(P, Q);
	std::cout << PAQ;

	return 0;
}
/*-------------------------------------------------*/
