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

	using namespace cla3p;

	prop_t ptype1 = prop_t::NONE;
	prop_t ptype2 = prop_t::GENERAL;
	prop_t ptype3 = prop_t::SYMMETRIC;
	prop_t ptype4 = prop_t::HERMITIAN;
	Property prop1(ptype1);
	Property prop2(ptype2);
	Property prop3(ptype3);
	Property prop4(ptype4);
	std::cout << prop1 << std::endl;
	std::cout << prop2 << std::endl;
	std::cout << prop3 << std::endl;
	std::cout << prop4 << std::endl;

	return 0;
}
/*-------------------------------------------------*/
