/**
 * @example ex02k_dense_matrix_algebra_scale.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);

	A = 3.;
	std::cout << "A:\n" << A << "\n";

	/*
	 * Scale A using operators and the scale function respectively
	 */

	A *= 2.;
	std::cout << "A *= 2:\n" << A;

	A /= 2.;
	std::cout << "A /= 2:\n" << A;

	A.scale(.5);
	std::cout << "A.scale(.5):\n" << A << "\n";

	cla3p::dns::RdMatrix B1 = A  / 2.;
	cla3p::dns::RdMatrix B2 = A  * 2.;
	cla3p::dns::RdMatrix B3 = 2. * A ;

	std::cout << "B = A/2:\n" << B1;
	std::cout << "B = A*2:\n" << B2;
	std::cout << "B = 2*A:\n" << B3;

	return 0;
}
