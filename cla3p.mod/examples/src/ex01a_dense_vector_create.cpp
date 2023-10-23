/**
 * @example ex01a_dense_vector_create.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Double precision real empty vector
	 */

	cla3p::dns::RdVector X;

	std::cout << X.info("X");

	/*
	 * Single precision real vector with size 3 (uninitialized values)
	 */

	cla3p::dns::RfVector Y(3);

	std::cout << Y.info("Y");

	/*
	 * Allocate space for X (size 5, uninitialized values)
	 */

	X = cla3p::dns::RdVector::init(5);

	std::cout << X.info("X");

	return 0;
}
