/**
 * @example ex01i_dense_vector_algebra_scale.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::dns::RdVector X(3);

	X = 3.;
	std::cout << "X:\n" << X << "\n";

	/*
	 * Scale X using operators and the scale function respectively
	 */

	X *= 2.;
	std::cout << "X *= 2:\n" << X << "\n";

	X /= 2.;
	std::cout << "X /= 2:\n" << X << "\n";

	X.iscale(.5);
	std::cout << "X.iscale(.5):\n" << X << "\n";

	cla3p::dns::RdVector Y1 = X  / 2.;
	cla3p::dns::RdVector Y2 = X  * 2.;
	cla3p::dns::RdVector Y3 = 2. * X ;

	std::cout << "Y = X/2:\n" << Y1 << "\n";
	std::cout << "Y = X*2:\n" << Y2 << "\n";
	std::cout << "Y = 2*X:\n" << Y3;

	return 0;
}
