/**
 * @example ex02g_dense_matrix_move.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfMatrix A(3,3);
	A = 2;

	std::cout << A.info("A") << A;

	/*
	 * Move A to B
	 */

	cla3p::dns::RfMatrix B = A.move();

	std::cout << A.info("A") << A;
	std::cout << B.info("B") << B;

	return 0;
}
