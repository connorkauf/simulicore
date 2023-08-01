#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/
template <typename T_Matrix>
static T_Matrix perm2mat(const cla3p::PiMatrix& P)
{
	T_Matrix ret(P.size(), P.size());

	ret = 0;
	for(cla3p::uint_t i = 0; i < P.size(); i++) {
		ret(i,P(i)) = 1;
	}

	return ret;
}
/*-------------------------------------------------*/
static void check_perm_of_perm()
{
	cla3p::uint_t n = 7;

	cla3p::PiMatrix P1 = cla3p::PiMatrix::random(n);
	cla3p::PiMatrix P2 = cla3p::PiMatrix::random(n);
	cla3p::PiMatrix P12 = P1 * P2;

	cla3p::dns::RdMatrix dP1 = perm2mat<cla3p::dns::RdMatrix>(P1);
	cla3p::dns::RdMatrix dP2 = perm2mat<cla3p::dns::RdMatrix>(P2);
	cla3p::dns::RdMatrix dP12 = dP1 * dP2;

	cla3p::dns::RdMatrix Err = dP12 - perm2mat<cla3p::dns::RdMatrix>(P12);
	std::cout << Err.info("Err") << Err;
}
/*-------------------------------------------------*/
static void check_perm_on_vec()
{
	cla3p::uint_t n = 7;

	cla3p::PiMatrix P = cla3p::PiMatrix::random(n);
	cla3p::dns::RdMatrix dP = perm2mat<cla3p::dns::RdMatrix>(P);
	std::cout <<  P.info(" P") <<  P;
	std::cout << dP.info("dP") << dP;

	cla3p::dns::RdVector V = cla3p::dns::RdVector::random(n);
	std::cout << V.info("V") << V;

	cla3p::dns::RdVector E1 =  P * V;
	cla3p::dns::RdVector E2 = dP * V;
	cla3p::dns::RdVector Err = E1 - E2;

	std::cout << Err.info("Err") << Err;
}
/*-------------------------------------------------*/
static void check_perm_on_ge_mat()
{
	cla3p::uint_t m = 8;
	cla3p::uint_t n = 7;

	cla3p::PiMatrix P = cla3p::PiMatrix::random(m);
	cla3p::PiMatrix Q = cla3p::PiMatrix::random(n);

	cla3p::dns::RdMatrix dP = perm2mat<cla3p::dns::RdMatrix>(P);
	cla3p::dns::RdMatrix dQ = perm2mat<cla3p::dns::RdMatrix>(Q);

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(m,n);

	{
		cla3p::dns::RdMatrix Err = (P * A) - (dP * A);
		std::cout << Err.info("Err Left") << Err;
	}

	{
		cla3p::dns::RdMatrix Err = (A * Q) - (A * dQ);
		std::cout << Err.info("Err Right") << Err;
	}

	{
		cla3p::dns::RdMatrix Err = A.permuteLeftRight(P,Q) - (dP * A * dQ);
		std::cout << Err.info("Err Left Right") << Err;
	}
}
/*-------------------------------------------------*/
static void check_perm_on_sy_mat()
{
	cla3p::uint_t n = 7;

	cla3p::PiMatrix P = cla3p::PiMatrix::random(n);

	cla3p::dns::RdMatrix dP = perm2mat<cla3p::dns::RdMatrix>(P);

	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::U);
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(n,n,prA);
	cla3p::dns::RdMatrix gA = A.general();

	cla3p::dns::RdMatrix Err = A.permuteMirror(P).general() - (dP * gA * dP.transpose());
	std::cout << Err.info("Err") << Err;
}
/*-------------------------------------------------*/
static void check_perm_on_he_mat()
{
	cla3p::uint_t n = 7;

	cla3p::PiMatrix P = cla3p::PiMatrix::random(n);

	cla3p::dns::CdMatrix cP = perm2mat<cla3p::dns::CdMatrix>(P);

	cla3p::Property prA(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::L);
	cla3p::dns::CdMatrix A = cla3p::dns::CdMatrix::random(n,n,prA);
	cla3p::dns::CdMatrix gA = A.general();

	cla3p::dns::CdMatrix Err = A.permuteMirror(P).general() - (cP * gA * cP.ctranspose());
	std::cout << Err.info("Err") << Err;
}
/*-------------------------------------------------*/

int main()
{
	check_perm_of_perm();
	check_perm_on_vec();
	check_perm_on_ge_mat();
	check_perm_on_sy_mat();
	check_perm_on_he_mat();

	return 0;
}
/*-------------------------------------------------*/
