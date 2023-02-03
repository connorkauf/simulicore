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
#include "cla3p/src/prm_mat.hpp"

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
	uint_t n = 4;

	//dMat A(m, n);
	dMat A = dMat::random(m,n);
	A.info("A");
	A.print();
	std::cout << "normA: " << A.norm_one() << std::endl;
	std::cout << "normA: " << A.norm_inf() << std::endl;
	std::cout << "normA: " << A.norm_max() << std::endl;
	std::cout << "normA: " << A.norm_fro() << std::endl;

	dMat B = A.transpose();
	B.print();
	std::cout << "normB: " << B.norm_one() << std::endl;
	std::cout << "normB: " << B.norm_inf() << std::endl;
	std::cout << "normB: " << B.norm_max() << std::endl;
	std::cout << "normB: " << B.norm_fro() << std::endl;

	B.scale(-3.);
	B.print();
	std::cout << "normB: " << B.norm_one() << std::endl;
	std::cout << "normB: " << B.norm_inf() << std::endl;
	std::cout << "normB: " << B.norm_max() << std::endl;
	std::cout << "normB: " << B.norm_fro() << std::endl;

	prm::pMat P = prm::pMat::random(m+1);
	prm::pMat Q = prm::pMat::random(n);

	P.info();
	P.print();
	Q.info();
	Q.print();
	dMat C1 = A.permute(P,Q);
	dMat C2 = A.lpermute(P);
	dMat C3 = A.rpermute(Q);
	A.print();
	C1.print();
	C2.print();
	C3.print();

	return 0;
}
/*-------------------------------------------------*/
