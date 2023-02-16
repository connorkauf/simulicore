#include <iostream>
//#include <cstdio>
//#include <complex>

//#include <omp.h>

//#include "cla3p/src/types.hpp"
#include "cla3p/src/dns_rdmatrix.hpp"
#include "cla3p/src/dns_rfmatrix.hpp"
#include "cla3p/src/dns_rimatrix.hpp"
#include "cla3p/src/perm_matrix.hpp"

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
#include "cla3p/src/support/error_internal.hpp"
//#include "cla3p/src/support/imalloc.hpp"
//#include "cla3p/src/support/utils.hpp"

/*-------------------------------------------------*/

using Matrix = cla3p::dns::RiMatrix;

int main()
{
	cla3p::enable_dbg_messages();

	Matrix A = Matrix::random(10,10);
	cla3p::PermMatrix P = cla3p::PermMatrix::random(10);

	std::cout << A.info("A");
	std::cout << A;

	std::cout << P.info("P");
	std::cout << P;

	A.print();
	P.print();
	A.permuteLeft(P).print();

	return 0;
}
/*-------------------------------------------------*/
