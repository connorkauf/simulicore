#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);

	A = 3.;
	std::cout << "A:\n" << A;

	/*
	 * Scale A using operators and the scale function respectively
	 */

	A *= 2.;
	std::cout << "2*A:\n" << A;

	A.scale(.5);
	std::cout << "A.scale(.5):\n" << A;

	return 0;
}
