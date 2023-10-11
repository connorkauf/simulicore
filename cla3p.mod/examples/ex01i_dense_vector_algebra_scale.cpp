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

	X /= 2.;
	std::cout << "X/2:\n" << X;

	X.scale(.5);
	std::cout << "X.scale(.5):\n" << X;

	cla3p::dns::RdVector Y1 = X  / 2.;
	cla3p::dns::RdVector Y2 = X  * 2.;
	cla3p::dns::RdVector Y3 = 2. * X ;

	return 0;
}
