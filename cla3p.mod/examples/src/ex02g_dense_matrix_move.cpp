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

	/*
	 * Move B to C
	 * C is non-empty, so it is cleared
	 */

	cla3p::dns::RfMatrix C(2,2);
	C = B.move();

	std::cout << C.info("C") << C;

	return 0;
}
