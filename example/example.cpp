#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"
#include "cla3p/src/linsol.hpp"

#if 0
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/bulk/dns_math.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#include "cla3p/src/support/error_internal.hpp"
#endif
/*-------------------------------------------------*/
template <typename T>
static void linsol_test()
{
	cla3p::uint_t n = 10;
	cla3p::uint_t nrhs = 5;
	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::L);
	//cla3p::Property prA(cla3p::prop_t::GENERAL, cla3p::uplo_t::F);
	//cla3p::Property prA(cla3p::prop_t::TRIANGULAR, cla3p::uplo_t::U);


	T A = T::random(prA, n, n);
	T B = T::random(n, nrhs);

	for(cla3p::uint_t i = 0; i < n; i++) A(i,i) *= 1000;

	std::cout << A << B;

	cla3p::dns::DefaultLSolver<T> def(n);
	cla3p::dns::LSolverLLt<T> llt(n);

	cla3p::dns::LSolverBase<T>& solver = llt;

	T X = B.copy();

	solver.decompose(A);
	solver.solve(X);

	std::cout << (B - A * X).normInf() << std::endl;
}
/*-------------------------------------------------*/

int main()
{
	linsol_test<cla3p::dns::RdMatrix>();
	//linsol_test<cla3p::dns::RfMatrix>();
	//linsol_test<cla3p::dns::CdMatrix>();
	//linsol_test<cla3p::dns::CfMatrix>();

	return 0;
}
/*-------------------------------------------------*/
