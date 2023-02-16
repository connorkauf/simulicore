//#include <iostream>
//#include <cstdio>
//#include <complex>

//#include <omp.h>

//#include "cla3p/src/types.hpp"
//#include "cla3p/src/dns_rdmatrix.hpp"
//#include "cla3p/src/perm_matrix.hpp"

//#include "cla3p/src/bulk/dns.hpp"
//#include "cla3p/src/bulk/dns_io.hpp"

//#include "cla3p/src/checks/all_checks.hpp"

//#include "cla3p/src/generic/generic_dns.hpp"
//#include "cla3p/src/generic/guard.hpp"
//#include "cla3p/src/generic/universal.hpp"

//#include "cla3p/src/proxies/blas_proxy.hpp"
//#include "cla3p/src/proxies/lapack_proxy.hpp"
//#include "cla3p/src/proxies/mkl_proxy.hpp"

//#include "cla3p/src/support/error.hpp"
//#include "cla3p/src/support/error_internal.hpp"
//#include "cla3p/src/support/imalloc.hpp"
//#include "cla3p/src/support/utils.hpp"

/*-------------------------------------------------*/

int main()
{
#if 0
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(10,10);
	cla3p::PermMatrix P = cla3p::PermMatrix::random(10);

	std::cout << A.info("A");
	std::cout << A;

	std::cout << P.info("P");
	std::cout << P;

	//A.print();
	//P.print();
	//A.permuteLeft(P).print();
#endif

	return 0;
}
/*-------------------------------------------------*/
