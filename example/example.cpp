#include <iostream>
#include <vector>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"
#include "cla3p/src/linsol.hpp"

#if 1
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/bulk/dns_math.hpp"
#include "cla3p/src/bulk/dns_decomp.hpp"
#include "cla3p/src/bulk/csc.hpp"
#include "cla3p/src/proxies/blas_proxy.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#include "cla3p/src/support/error_internal.hpp"
#endif
/*-------------------------------------------------*/
#if 0
static std::vector<cla3p::uint_t> ipiv2iperm(const std::vector<cla3p::int_t>& ipiv)
{
	cla3p::int_t n = ipiv.size();

	std::vector<cla3p::uint_t> ret(n);
	std::vector<cla3p::uint_t> tmp(n);

	for(cla3p::int_t i = 0; i < n; i++) tmp[i] = i;

	for(cla3p::int_t i = 0; i < n; i++) {

		if(ipiv[i] > 0) {

			cla3p::int_t ip = ipiv[i] - 1;
			if(i != ip) std::swap(tmp[i], tmp[ip]);

		} else if(ipiv[i] < 0) {

			cla3p::int_t ip = - ipiv[i] - 1;
			if(i+1 != ip) std::swap(tmp[i+1], tmp[ip]);

			i++;
		}

	} // i

#if 1
	for(cla3p::int_t i = 0; i < n; i++) ret[tmp[i]] = i;
	return ret;
#else
	return tmp;
#endif
}
#endif
/*-------------------------------------------------*/
#if 0
static cla3p::dns::RdMatrix zero_2x2_off_diag_element(const cla3p::dns::RdMatrix& F, const std::vector<cla3p::int_t>& ipiv)
{
	cla3p::int_t n = ipiv.size();
	cla3p::dns::RdMatrix ret = F.copy();

	for(cla3p::int_t i = 0; i < n; i++) {

		if(ipiv[i] < 0) {
			cla3p::int_t k = - ipiv[i] - 1;
			//cla3p::int_t k = i;
			ret(k+1,k) = 0;
			ret(k,k+1) = 0;
			i++;
		}

	} // i

	return ret.move();
}
#endif
/*-------------------------------------------------*/
static void check_custom_trsm(cla3p::uplo_t uplo)
{
	cla3p::uint_t n = 50;
	cla3p::uint_t nrhs = 5;

	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, uplo);

	cla3p::dns::RdMatrix G = cla3p::dns::RdMatrix::random(prA, n+20, n+20);
	cla3p::dns::RdMatrix A = G.rblock(0,0,n,n); //cla3p::dns::RdMatrix::random(prA, n, n);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(n, nrhs);

	//for(cla3p::uint_t i = 0; i < n; i++) A(i,i) = std::abs(A(i,i)) * 20;

	cla3p::dns::RdMatrix X1 = B.copy();
	cla3p::dns::RdMatrix X2 = B.copy();
	cla3p::dns::RdMatrix X3 = B.transpose();
	cla3p::dns::RdMatrix X4 = B.copy();

	std::vector<cla3p::int_t> ipiv(n);
	cla3p::dns::RdMatrix F = A.copy();
	cla3p::dns::RdMatrix W = A.copy();
	cla3p::lapack::sytrf(prA.cuplo(), n, F.values(), F.ld(), ipiv.data());

	cla3p::bulk::dns::print(cla3p::uplo_t::F, 1, n, ipiv.data(), 1);

	cla3p::lapack::sytrs(prA.cuplo(), n, nrhs, F.values(), F.ld(), ipiv.data(), X1.values(), X1.ld());

	if(prA.isLower()) {
		cla3p::bulk::dns::itrsm_lln(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lld(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_llt(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());

		cla3p::bulk::dns::itrsm_rlt(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rld(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rln(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
	}

	if(prA.isUpper()) {
		cla3p::bulk::dns::itrsm_lun(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lud(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lut(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());

		cla3p::bulk::dns::itrsm_rut(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rud(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_run(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
	}

	{
		if(prA.isLower()) {
			cla3p::bulk::dns::itrsm_left_blas3('L', n, F.values(), F.ld(), nrhs, X4.values(), X4.ld(), ipiv.data(), W.values());
		}

		if(prA.isUpper()) {
			cla3p::bulk::dns::itrsm_left_blas3('U', n, F.values(), F.ld(), nrhs, X4.values(), X4.ld(), ipiv.data(), W.values());
		}
	}

	std::cout << (B - A * X1).normInf() / B.normInf() << std::endl;
	std::cout << (B - A * X2).normInf() / B.normInf() << std::endl;
	std::cout << (B - A * X3.transpose()).normInf() / B.normInf() << std::endl;
	std::cout << (B - A * X4).normInf() / B.normInf() << std::endl;
}
/*-------------------------------------------------*/
template <typename T>
static void linsol_test()
{
	cla3p::uint_t n = 10;
	cla3p::uint_t nrhs = 5;
	//cla3p::Property prA(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::L);
	cla3p::Property prA(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::U);
	//cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::L);
	//cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::U);
	//cla3p::Property prA(cla3p::prop_t::GENERAL, cla3p::uplo_t::F);


	T A = T::random(prA, n, n);
	T B = T::random(n, nrhs);

	//for(cla3p::uint_t i = 0; i < n; i++) A(i,i) *= 1000;

	B.scale(1.e-10);

	//std::cout << A << B;

	cla3p::dns::LSolverAuto<T> def;
	cla3p::dns::LSolverLLt<T> llt;
	cla3p::dns::LSolverLDLt<T> ldlt;
	cla3p::dns::LSolverLU<T> lu;
	cla3p::dns::LSolverCompleteLU<T> clu;

	cla3p::dns::LSolverBase<T>& solver = clu;

	T X = B.copy();

	solver.reserve(n);
	solver.decompose(A);
	solver.solve(X);

	std::cout << (B - A * X).normInf() / B.normInf() << std::endl;
}
/*-------------------------------------------------*/

int main()
{

	{
		cla3p::uint_t n = 4;
		cla3p::uint_t IA[] = {0,   2,     4,          7,  8};
		cla3p::uint_t JA[] = { 0,  1, 3,  1,  4,  2,  3,  5};
		cla3p::real_t  A[] = {10, 20, 4, 30, 70, 50, 60, 80};

		cla3p::bulk::csc::print(n, IA, JA, A, 15);

		cla3p::bulk::csc::sort_by_ridx(n, IA, JA, A);

		cla3p::bulk::csc::print(n, IA, JA, A, 15);

		return 0;
	}




	check_custom_trsm(cla3p::uplo_t::U);
	check_custom_trsm(cla3p::uplo_t::L);
	return 0;

	linsol_test<cla3p::dns::RdMatrix>();
	linsol_test<cla3p::dns::RfMatrix>();
	linsol_test<cla3p::dns::CdMatrix>();
	linsol_test<cla3p::dns::CfMatrix>();

	return 0;
}
/*-------------------------------------------------*/
