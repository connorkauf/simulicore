/**
 * @example ex01e_dense_vector_copy.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X(3);
	X = 1;

	std::cout << X.info("X") << X;

	/*
	 * Copy X to Y using assignment
	 * Copy X to Z using copy()
	 */
	
	cla3p::dns::RfVector Y = X;
	cla3p::dns::RfVector Z = X.copy();

	std::cout << Y.info("Y") << Y;
	std::cout << Z.info("Z") << Z;

	/*
	 * Copy Y to Z using assignment
	 * Z is already allocated 
	 * No re-allocation performed 
	 * Needs matching sizes
	 */

	Z = Y;

	std::cout << Z.info("Z") << Z;

	return 0;
}
