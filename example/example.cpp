#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"

#if 0
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/bulk/dns_math.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#endif
#include "cla3p/src/support/error_internal.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	cla3p::uint_t m = 5;
	cla3p::uint_t n = 5;
	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::U);

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(prA, m, n);
	std::cout << A;

	cla3p::dns::RdMatrix B = A.general();
	A.igeneral();

	std::cout << A << B;

	return 0;
}
/*-------------------------------------------------*/
