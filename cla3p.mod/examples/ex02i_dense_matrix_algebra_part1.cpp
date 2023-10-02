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
	 * Add A & B using operators and the add function respectively
	 */
	cla3p::dns::RdMatrix C1 = A + 2. * B;
	std::cout << "C1 = A + 2*B:\n" << C1;

	cla3p::dns::RdMatrix C2 = cla3p::ops::add(1., A, 3., B);
	std::cout << "C2 = cla3p::ops::add(1,A,3,B):\n" << C2;

	/*
	 * Update C1 & C2 using operators and the update function respectively
	 */
	C1 += 1.5 * A;
	std::cout << "C1 += 1.5 * A:\n" << C1;

	cla3p::ops::update(.5, B, C2);
	std::cout << "cla3p::ops::update(.5,B,C2):\n" << C2;

	return 0;
}
