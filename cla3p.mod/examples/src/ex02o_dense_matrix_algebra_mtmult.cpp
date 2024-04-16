/**
 * @example ex02o_dense_matrix_algebra_mtmult.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);
	cla3p::dns::RdMatrix B(3,3);

	A = 3.;
	B = 2.;
	std::cout << "A:\n" << A;
	std::cout << "B:\n" << B << "\n";

	/*
	 * Perform the operation (A' * B) using operators and the mult function respectively
	 */

	cla3p::dns::RdMatrix C1 = A.transpose() * B;
	std::cout << "C1:\n" << C1;

	cla3p::dns::RdMatrix C2(3,3);
	cla3p::ops::mult(1., cla3p::op_t::T, A, cla3p::op_t::N, B, 0., C2);
	std::cout << "C2:\n" << C2;

	return 0;
}
