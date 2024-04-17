/**
 * @example ex03g_permutation_matrix_permute_matrix_symmetric.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	/*
	 * Create a (3x3) random symmetric lower matrix
	 */

	cla3p::dns::RdMatrix A(3, 3, cla3p::Property::SymmetricLower());

	for(cla3p::uint_t j = 0, icnt = 0; j < 3; j++)
		for(cla3p::uint_t i = j; i < 3; i++)
			A(i,j) = icnt++;

	/*
	 * Create a (3x3) random permutation matrix
	 */

	cla3p::prm::PiMatrix P(3);

	P(0) = 1;
	P(1) = 2;
	P(2) = 0;

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P << "\n";

	/*
	 * Perform the operation (P * A * P') 
	 * using operators and the permute member function respectively.
	 *
	 * Permutation operators are used on general matrices.
	 * In order to use operators A needs to be converted from symmetric to general. 
	 * Resulting matrix will be general.
	 *
	 * Using permuteMirror() the resulting matrix will be symmetric.
	 */

	cla3p::dns::RdMatrix PAPT1 = P * A.general() * P.inverse();

	std::cout << "PAPT1:\n" << PAPT1;

	cla3p::dns::RdMatrix PAPT2 = A.permuteMirror(P);

	std::cout << "PAPT2:\n" << PAPT2;

	return 0;
}
