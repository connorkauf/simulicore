/**
 * @example ex01b_dense_vector_fill.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdVector X(3);
	cla3p::dns::RdVector Y(3);
	cla3p::dns::RdVector Z(3);

	/* 
	 * Set all values in X to 1.5 (using member function)
	 * Set all values in Y to -2.7 (using operator=)
	 */

	X.fill(1.5);
	Y = -2.7;

	/* 
	 * Insert values in Z manually
	 */

	Z(0) = 3.;
	Z(1) = 2.;
	Z(2) = Z(0) + Z(1);

	std::cout << "X:\n" << X << "\n";
	std::cout << "Y:\n" << Y << "\n";
	std::cout << "Z:\n" << Z;

	return 0;
}
