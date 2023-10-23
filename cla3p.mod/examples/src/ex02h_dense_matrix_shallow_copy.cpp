/**
 * @example ex02h_dense_matrix_shallow_copy.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfMatrix A(3,3);
	A = 2;

	std::cout << A.info("A") << A;

	/*
	 * Shallow Copy A to B (A & B share contents)
	 */

	cla3p::dns::RfMatrix B = A.rcopy();

	std::cout << B.info("B") << B << "\n";

	B(0,1) = 0;
	B(1,1) = 0;
	B(0,2) = 0;
	B(1,2) = 0;

	std::cout << "A after zero set:\n" << A;
	std::cout << "B after zero set:\n" << B;

	return 0;
}
