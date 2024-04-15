/**
 * @example ex01k_dense_vector_algebra_dot.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::dns::RdVector X(3);
	cla3p::dns::RdVector Y(3);

	X = 3.;
	Y = 2.;

	std::cout << "X:\n" << X;
	std::cout << "Y:\n" << Y << "\n";

	/*
	 * Perform the operation (X' * Y) using operators and the dot function respectively
	 */

	cla3p::real_t d1 = X.transpose() * Y;
	std::cout << "d1: " << d1 << std::endl;

	cla3p::real_t d2 = cla3p::ops::dot(X, Y);
	std::cout << "d2: " << d2 << std::endl;

	return 0;
}
