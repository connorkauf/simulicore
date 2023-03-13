#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"

#if 1
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/bulk/dns_math.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#endif
#include "cla3p/src/support/error_internal.hpp"

/*-------------------------------------------------*/
static const cla3p::op_t opA = cla3p::op_t::N;
static const cla3p::real_t alpha = 1;
/*-------------------------------------------------*/
static void check_tridmult_right(cla3p::uplo_t uplo, cla3p::uint_t m, cla3p::uint_t n, cla3p::uint_t k)
{
	cla3p::uint_t nrA = (opA == cla3p::op_t::N ? k : n);
	cla3p::uint_t ncA = (opA == cla3p::op_t::N ? n : k);

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::zero(nrA,ncA);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(m,k);
	cla3p::dns::RdMatrix C1 = cla3p::dns::RdMatrix::random(m,n);
	cla3p::dns::RdMatrix C2 = cla3p::dns::RdMatrix::random(m,n);

	cla3p::bulk::dns::rand(uplo, nrA, ncA, A.values(), A.ld());

	cla3p::bulk::dns::gem_x_gem(m, n, k, alpha, cla3p::op_t::N, B.values(), B.ld(), opA, A.values(), A.ld(), 0, C1.values(), C1.ld());

	cla3p::bulk::dns::gem_x_trm(uplo, opA, m, n, k, alpha, A.values(), A.ld(), B.values(), B.ld(), C2.values(), C2.ld());

	cla3p::bulk::dns::update(cla3p::uplo_t::F, m, n, -1, C1.values(), C1.ld(), C2.values(), C2.ld());

	printf("m/k/n: %3llu %3llu %3llu norm: %le\n", m, k, n, C2.normMax());
}
/*-------------------------------------------------*/
static void check_tridmult(cla3p::uplo_t uplo, cla3p::uint_t m, cla3p::uint_t n, cla3p::uint_t k)
{
	cla3p::uint_t nrA = (opA == cla3p::op_t::N ? m : k);
	cla3p::uint_t ncA = (opA == cla3p::op_t::N ? k : m);

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::zero(nrA,ncA);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(k,n);
	cla3p::dns::RdMatrix C1 = cla3p::dns::RdMatrix::random(m,n);
	cla3p::dns::RdMatrix C2 = cla3p::dns::RdMatrix::random(m,n);

	cla3p::bulk::dns::rand(uplo, nrA, ncA, A.values(), A.ld());

	cla3p::bulk::dns::gem_x_gem(m, n, k, alpha, opA, A.values(), A.ld(), cla3p::op_t::N, B.values(), B.ld(), 0, C1.values(), C1.ld());

	if(n == 1) {
		cla3p::bulk::dns::trm_x_vec(uplo, opA, nrA, ncA, alpha, A.values(), A.ld(), B.values(), C2.values());
	} else {
		cla3p::bulk::dns::trm_x_gem(uplo, opA, m, n, k, alpha, A.values(), A.ld(), B.values(), B.ld(), C2.values(), C2.ld());
	}

	cla3p::bulk::dns::update(cla3p::uplo_t::F, m, n, -1, C1.values(), C1.ld(), C2.values(), C2.ld());

	printf("m/k/n: %3llu %3llu %3llu norm: %le\n", m, k, n, C2.normMax());
}
/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	cla3p::uint_t m = 10;
	cla3p::uint_t n =  5;
	cla3p::uint_t k =  7;

	check_tridmult(cla3p::uplo_t::U, m, 1, k);
	check_tridmult(cla3p::uplo_t::U, k, 1, m);
	check_tridmult(cla3p::uplo_t::L, m, 1, k);
	check_tridmult(cla3p::uplo_t::L, k, 1, m);

	check_tridmult(cla3p::uplo_t::U, m, n, k);
	check_tridmult(cla3p::uplo_t::U, k, n, m);
	check_tridmult(cla3p::uplo_t::L, m, n, k);
	check_tridmult(cla3p::uplo_t::L, k, n, m);

	check_tridmult(cla3p::uplo_t::U, m, 10*n, k);
	check_tridmult(cla3p::uplo_t::U, k, 10*n, m);
	check_tridmult(cla3p::uplo_t::L, m, 10*n, k);
	check_tridmult(cla3p::uplo_t::L, k, 10*n, m);

	check_tridmult_right(cla3p::uplo_t::U, m, 1, k);
	check_tridmult_right(cla3p::uplo_t::U, k, 1, m);
	check_tridmult_right(cla3p::uplo_t::L, m, 1, k);
	check_tridmult_right(cla3p::uplo_t::L, k, 1, m);

	check_tridmult_right(cla3p::uplo_t::U, m, n, k);
	check_tridmult_right(cla3p::uplo_t::U, k, n, m);
	check_tridmult_right(cla3p::uplo_t::L, m, n, k);
	check_tridmult_right(cla3p::uplo_t::L, k, n, m);

	check_tridmult_right(cla3p::uplo_t::U, m, 10*n, k);
	check_tridmult_right(cla3p::uplo_t::U, k, 10*n, m);
	check_tridmult_right(cla3p::uplo_t::L, m, 10*n, k);
	check_tridmult_right(cla3p::uplo_t::L, k, 10*n, m);

	return 0;
}
/*-------------------------------------------------*/
