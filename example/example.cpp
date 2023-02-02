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

	std::vector<uint_t> P = create_random_perm(m);
	std::vector<uint_t> Q = create_random_perm(n);

	for(uint_t i = 0; i < m; i++) printf("P[%llu] = %llu\n", i, P[i]);
	for(uint_t i = 0; i < n; i++) printf("Q[%llu] = %llu\n", i, Q[i]);
	dMat C = A.permute(P.data(),Q.data());
	C.print();

	return 0;
}
/*-------------------------------------------------*/
