/**
 * @example ex06m_sparse_matrix_algebra_vmult.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::coo::RdMatrix Acoo(5, 5);

	Acoo.insert(0,0,1.0);
	Acoo.insert(1,1,2.0);
	Acoo.insert(2,1,3.0);
	Acoo.insert(1,3,4.0);
	Acoo.insert(0,0,5.0);

	cla3p::csc::RdMatrix A = Acoo;

	std::cout << "A:\n" << A << "\n";

	cla3p::dns::RdVector X(5);

	X = 2.;
	std::cout << "X:\n" << X << "\n";

	/*
	 * Perform the operation (A * X) using operators and the mult function respectively
	 */

	cla3p::dns::RdVector Y1 = A * X;
	std::cout << "Y1:\n" << Y1;

	cla3p::dns::RdVector Y2(5);
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
