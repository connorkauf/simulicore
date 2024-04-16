/**
 * @example ex02m_dense_matrix_algebra_vmult.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);
	cla3p::dns::RdVector X(3);

	A = 3.;
	X = 2.;
	std::cout << "A:\n" << A;
	std::cout << "X:\n" << X << "\n";

	/*
	 * Perform the operation (A * X) using operators and the mult function respectively
	 */

	cla3p::dns::RdVector Y1 = A * X;
	std::cout << "Y1:\n" << Y1;

	cla3p::dns::RdVector Y2(3);
	cla3p::ops::mult(1., cla3p::op_t::N, A, X, 0., Y2);
	std::cout << "Y2:\n" << Y2 << "\n";

	/*
	 * Perform the operation (Yx += A * X) using operators and the mult function respectively
	 */

	Y1 += A * X;
	std::cout << "Y1:\n" << Y1;

	cla3p::ops::mult(1., cla3p::op_t::N, A, X, 1., Y2);
	std::cout << "Y2:\n" << Y2;

	return 0;
}
