#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"

int main()
{
	/*
	 * Create a (3x3) random symmetric lower matrix
	 */
	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::L);
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3,prA);

	/*
	 * Create a (3x3) random permutation matrix
	 */
	cla3p::PiMatrix P = cla3p::PiMatrix::random(3);

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;

	/*
	 * Permute A symmetrically (P * A * P')
	 */
	cla3p::dns::RdMatrix PAPT = A.permuteMirror(P);
	std::cout << "A.permuteMirror(P):\n" << PAPT;

	return 0;
}
