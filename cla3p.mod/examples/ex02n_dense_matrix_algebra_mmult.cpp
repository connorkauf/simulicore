#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);
	cla3p::dns::RdMatrix B(3,3);

	A = 3.;
	B = 2.;
	std::cout << "A:\n" << A;
	std::cout << "B:\n" << B;

	/*
	 * Perform the operation (A * B) using operators and the mult function respectively
	 */

	cla3p::dns::RdMatrix C1 = A * B;
	std::cout << "C1 = A * B:\n" << C1;

	cla3p::op_t opA = cla3p::op_t::N;
	cla3p::op_t opB = cla3p::op_t::N;
	cla3p::dns::RdMatrix C2 = cla3p::ops::mult(1., opA, A, opB, B);
	std::cout << "C2 = mult(1.,opA,A,opB,B):\n" << C2;

	/*
	 * Perform the operation (Cx += A * B) using operators and the mult function respectively
	 */

	C1 += A * B;
	std::cout << "C1 += A * B:\n" << C1;

	cla3p::ops::mult(1., opA, A, opB, B, C2);
	std::cout << "mult(1,opA,A,opB,B,C2):\n" << C2;

	return 0;
}
