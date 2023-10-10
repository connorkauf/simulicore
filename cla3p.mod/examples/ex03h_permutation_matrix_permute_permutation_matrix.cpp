#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/operations.hpp"

int main()
{
	/*
	 * Create a (3x3) random matrix
	 */

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(4,4);

	/*
	 * Create a (3x3) random permutation matrix
	 */

	cla3p::PiMatrix P = cla3p::PiMatrix::random(4);
	cla3p::PiMatrix Q = cla3p::PiMatrix::random(4);

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;
	std::cout << "Q:\n" << Q;

	/*
	 * Perform the operation ((P * Q) * A) using operators and the permute member function respectively
	 */

	{
		cla3p::PiMatrix PQ = Q.permuteLeft(P);
		cla3p::dns::RdMatrix PQA = A.permuteLeft(PQ);
		std::cout << "Permuted A:\n" << PQA;
	}

	{
		cla3p::dns::RdMatrix PQA = (P * Q) * A;
		std::cout << "Permuted A:\n" << PQA;
	}

	return 0;
}
