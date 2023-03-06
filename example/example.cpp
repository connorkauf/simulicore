#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"

#if 0
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#endif
#include "cla3p/src/support/error_internal.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	cla3p::dns::RiMatrix A = cla3p::dns::RiMatrix::random(10,5);
	cla3p::dns::RiMatrix B = cla3p::dns::RiMatrix::random(5,10);
	std::cout << A << B;

	cla3p::dns::RiMatrix C = A * B;
	std::cout << C;

	return 0;
}
/*-------------------------------------------------*/
