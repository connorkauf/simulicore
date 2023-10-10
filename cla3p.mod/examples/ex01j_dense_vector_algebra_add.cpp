#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdVector X(3);
	cla3p::dns::RdVector Y(3);

	X = 3.;
	Y = 2.;

	std::cout << "X:\n" << X;
	std::cout << "Y:\n" << Y;

	/*
	 * Perform the operation (X + 2 * Y) using operators and the add function respectively
	 */

	cla3p::dns::RdVector Z1 = X + 2. * Y;
	std::cout << "Z1 = X + 2*Y:\n" << Z1;

	cla3p::dns::RdVector Z2 = cla3p::ops::add(1., X, 2., Y);
	std::cout << "Z2 = add(1,X,2,Y):\n" << Z2;

	/*
	 * Perform the operation (Zx += 3 * X) using operators and the update function respectively
	 */

	Z1 += 3. * X;
	std::cout << "Z1 += 3 * X:\n" << Z1;

	cla3p::ops::update(3., X, Z2);
	std::cout << "update(3,X,Z2):\n" << Z2;

	return 0;
}
