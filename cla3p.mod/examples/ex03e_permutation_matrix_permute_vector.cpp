#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdVector X = cla3p::dns::RdVector::random(3);

	cla3p::PiMatrix P = cla3p::PiMatrix::random(3);

	std::cout << "X:\n" << X;
	std::cout << "P:\n" << P;

	/*
	 * Perform the operation (P * X) using operators and the permute member function respectively
	 */

	cla3p::dns::RdVector PX1 = P * X;
	std::cout << "P * X:\n" << PX1;

	cla3p::dns::RdVector PX2 = X.permuteLeft(P);
	std::cout << "X.permuteLeft(P):\n" << PX2;

	return 0;
}
