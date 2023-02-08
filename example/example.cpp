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

	return 0;
}
/*-------------------------------------------------*/
