/**
 * @example ex03f_permutation_matrix_permute_matrix.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);

	for(cla3p::uint_t j = 0, icnt = 0; j < 3; j++)
		for(cla3p::uint_t i = 0; i < 3; i++)
			A(i,j) = icnt++;

	cla3p::prm::PiMatrix P(3);
	cla3p::prm::PiMatrix Q(3);

	P(0) = 1;
	P(1) = 2;
	P(2) = 0;

	Q(0) = 2;
	Q(1) = 0;
	Q(2) = 1;

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;
	std::cout << "Q:\n" << Q << "\n";

	/*
	 * Perform the operation (P * A) 
	 * using operators and the permute member function respectively
	 */

	cla3p::dns::RdMatrix PA1 = P * A;

	std::cout << "PA1:\n" << PA1;

	cla3p::dns::RdMatrix PA2 = A.permuteLeft(P);

	std::cout << "PA2:\n" << PA2 << "\n";

	/*
	 * Perform the operation (A * Q) 
	 * using operators and the permute member function respectively
	 */

	cla3p::dns::RdMatrix AQ1 = A * Q;

	std::cout << "AQ1:\n" << AQ1;

	cla3p::dns::RdMatrix AQ2 = A.permuteRight(Q);

	std::cout << "AQ2:\n" << AQ2 << "\n";

	/*
	 * Perform the operation (P * A * Q) 
	 * using operators and the permute member function respectively
	 */

	cla3p::dns::RdMatrix PAQ1 = P * A * Q;

	std::cout << "PAQ1:\n" << PAQ1;

	cla3p::dns::RdMatrix PAQ2 = A.permuteLeftRight(P, Q);

	std::cout << "PAQ2:\n" << PAQ2;

	return 0;
}
