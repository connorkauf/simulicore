/**
 * @example ex02k_dense_matrix_algebra_scale.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/algebra.hpp"

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

	A.iscale(.5);
	std::cout << "A.iscale(.5):\n" << A << "\n";

	cla3p::dns::RdMatrix B1 = A  / 2.;
	cla3p::dns::RdMatrix B2 = A  * 2.;
	cla3p::dns::RdMatrix B3 = 2. * A ;

	std::cout << "B1:\n" << B1;
	std::cout << "B2:\n" << B2;
	std::cout << "B3:\n" << B3;

	return 0;
}
