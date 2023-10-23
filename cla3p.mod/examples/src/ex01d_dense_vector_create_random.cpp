/**
 * @example ex01d_dense_vector_create_random.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/* 
	 * Single precision complex vector (size 4, random values in [0,1])
	 */

	cla3p::dns::CfVector X = cla3p::dns::CfVector::random(4);

	std::cout << "X:\n" << X;

	return 0;
}
