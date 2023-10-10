#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfMatrix A = cla3p::dns::RfMatrix::random(3,3);
	std::cout << A.info("A") << A;

	/*
	 * Shallow Copy A to B (A & B share contents)
	 */

	cla3p::dns::RfMatrix B = A.rcopy();
	std::cout << B.info("B") << B;

	B(0,1) = 0.;
	B(1,1) = 0.;
	B(0,2) = 0.;
	B(1,2) = 0.;

	std::cout << A.info("A") << A;
	std::cout << B.info("B") << B;

	return 0;
}
