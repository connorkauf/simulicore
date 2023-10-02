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
	 * Add X & Y using operators and the add function respectively
	 */
	cla3p::dns::RdVector Z1 = X + 2. * Y;
	std::cout << "Z1 = X + 2*Y:\n" << Z1;
	cla3p::dns::RdVector Z2 = cla3p::ops::add(1., X, 3., Y);

	std::cout << "Z2 = cla3p::ops::add(1,X,3,Y):\n" << Z2;

	/*
	 * Update Z1 & Z2 using operators and the update function respectively
	 */
	Z1 += 1.5 * X;
	std::cout << "Z1 += 1.5 * X:\n" << Z1;

	cla3p::ops::update(.5, Y, Z2);
	std::cout << "cla3p::ops::update(.5,Y,Z2):\n" << Z2;

	return 0;
}
