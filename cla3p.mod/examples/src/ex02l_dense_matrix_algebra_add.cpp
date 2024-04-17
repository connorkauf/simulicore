/**
 * @example ex02l_dense_matrix_algebra_add.cpp
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
	 * Perform the operation (A + 2 * B) using operators and the add function respectively
	 */

	cla3p::dns::RdMatrix C1 = A + 2. * B;
	std::cout << "C1:\n" << C1;

	cla3p::dns::RdMatrix C2 = cla3p::ops::add(1., A, 2., B);
	std::cout << "C2:\n" << C2 << "\n";

	/*
	 * Perform the operation (Cx += 3 * A) using operators and the update function respectively
	 */

	C1 += 3. * A;
	std::cout << "C1:\n" << C1;

	cla3p::ops::update(3., B, C2);
	std::cout << "C2:\n" << C2;

	return 0;
}
