/**
 * @example ex02n_dense_matrix_algebra_mmult.cpp
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
	 * Perform the operation (A * B) using operators and the mult function respectively
	 */

	cla3p::dns::RdMatrix C1 = A * B;
	std::cout << "C1:\n" << C1;

	cla3p::dns::RdMatrix C2(3,3);
	C2 = 0;
	cla3p::ops::mult(1., cla3p::op_t::N, A, cla3p::op_t::N, B, C2);
	std::cout << "C2:\n" << C2 << "\n";

	/*
	 * Perform the operation (Cx += A * B) using operators and the mult function respectively
	 */

	C1 += A * B;
	std::cout << "C1:\n" << C1;

	cla3p::ops::mult(1., cla3p::op_t::N, A, cla3p::op_t::N, B, C2);
	std::cout << "C2:\n" << C2;

	return 0;
}
