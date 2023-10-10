#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/operations.hpp"

int main()
{
	/*
	 * Create a (3x3) random symmetric lower matrix
	 */

	cla3p::Property prA(cla3p::prop_t::Symmetric, cla3p::uplo_t::L);
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3,prA);

	/*
	 * Create a (3x3) random permutation matrix
	 */

	cla3p::PiMatrix P = cla3p::PiMatrix::random(3);

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;

	/*
	 * Perform the operation (P * A * P') using operators and the permute member function respectively
	 * Operators are used on general matrices 
	 * In order to use operators A needs to be converted to from symmetric general & resulting matrix will be general
	 * Using permuteMirror() the resulting matrix will be symmetric
	 */

	{
		cla3p::dns::RdMatrix Agen = A.general();
		cla3p::dns::RdMatrix PAPT = P * Agen * P.inverse();
		std::cout << "P * A * P':\n" << PAPT;
	}

	{
		cla3p::dns::RdMatrix PAPT = A.permuteMirror(P);
		std::cout << "A.permuteMirror(P):\n" << PAPT;
	}

	return 0;
}
