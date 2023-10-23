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
	 * Copy X to Y using copy()
	 *
	 * Copy assignment: 
	 * cla3p::dns::RfVector Y = X;
	 * is not allowed
	 */
	
	cla3p::dns::RfVector Y = X.copy();

	std::cout << Y.info("Y") << Y;

	return 0;
}
