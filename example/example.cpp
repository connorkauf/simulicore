#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

#include "cla3p/src/types.hpp"
#include "cla3p/src/dns_rdmatrix.hpp"
#include "cla3p/src/perm_matrix.hpp"

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

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(10,10);
	cla3p::PermMatrix P = cla3p::PermMatrix::random(10);

	A.print();
	P.print();
	A.permuteLeft(P).print();

	return 0;
}
/*-------------------------------------------------*/
