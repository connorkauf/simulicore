/**
 * @example ex01h_dense_vector_shallow_copy.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X(3);
	X = 1;

	std::cout << X.info("X") << X;

	/*
	 * Shallow copy X to Y (X & Y share contents)
	 */

	cla3p::dns::RfVector Y = X.rcopy();

	std::cout << Y.info("Y") << Y << "\n";

	Y(0) = 0;
	Y(2) = 0;

	std::cout << "X:\n" << X;
	std::cout << "Y:\n" << Y;

	return 0;
}
