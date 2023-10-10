#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdVector X(3);

	X = 3.;
	std::cout << "X:\n" << X;

	/*
	 * Scale X using operators and the scale function respectively
	 */

	X *= 2.;
	std::cout << "2*X:\n" << X;

	X.scale(.5);
	std::cout << "X.scale(.5):\n" << X;

	return 0;
}
