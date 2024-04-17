/**
 * @example ex03h_permutation_matrix_permute_permutation_matrix.cpp
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
	Q(1) = 1;
	Q(2) = 0;

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;
	std::cout << "Q:\n" << Q << "\n";

	/*
	 * Perform the operation ((P * Q) * A) 
	 * using operators and the permute member function respectively
	 */

	cla3p::prm::PiMatrix PQ = Q.permuteLeft(P);

	cla3p::dns::RdMatrix PQA1 = A.permuteLeft(PQ);

	std::cout << "PQA1:\n" << PQA1;

	cla3p::dns::RdMatrix PQA2 = (P * Q) * A;

	std::cout << "PQA2:\n" << PQA2;

	return 0;
}
