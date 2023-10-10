#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3);

	cla3p::PiMatrix P = cla3p::PiMatrix::random(3);
	cla3p::PiMatrix Q = cla3p::PiMatrix::random(3);

	std::cout << "A:\n" << A;
	std::cout << "P:\n" << P;
	std::cout << "Q:\n" << Q;

	{
		/*
		 * Perform the operation (P * A) using operators and the permute member function respectively
		 */

		cla3p::dns::RdMatrix PA1 = P * A;
		std::cout << "P * A:\n" << PA1;

		cla3p::dns::RdMatrix PA2 = A.permuteLeft(P);
		std::cout << "A.permuteLeft(P):\n" << PA2;
	}

	{
		/*
		 * Perform the operation (A * Q) using operators and the permute member function respectively
		 */

		cla3p::dns::RdMatrix AQ1 = A * Q;
		std::cout << "A * Q:\n" << AQ1;

		cla3p::dns::RdMatrix AQ2 = A.permuteRight(Q);
		std::cout << "A.permuteRight(Q):\n" << AQ2;
	}

	{
		/*
		 * Perform the operation (P * A * Q) using operators and the permute member function respectively
		 */

		cla3p::dns::RdMatrix PAQ1 = P * A * Q;
		std::cout << "P * A * Q:\n" << PAQ1;

		cla3p::dns::RdMatrix PAQ2 = A.permuteLeftRight(P, Q);
		std::cout << "A.permuteLeftRight(P,Q):\n" << PAQ2;
	}

	return 0;
}
