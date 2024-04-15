/**
 * @example ex01f_dense_vector_move.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X(3);
	X = 1;

	std::cout << X.info("X") << X;

	/*
	 * Move X to Y
	 */

	cla3p::dns::RfVector Y = X.move();

	std::cout << X.info("X") << X;
	std::cout << Y.info("Y") << Y;

	/*
	 * Move Y to Z
	 * Z is non-empty, so it is cleared
	 */

	cla3p::dns::RfVector Z(2);
	Z = Y.move();

	std::cout << Z.info("Z") << Z;

	return 0;
}
