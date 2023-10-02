#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfMatrix A = cla3p::dns::RfMatrix::random(3,3);
	std::cout << A.info("A") << A;

	/*
	 * Copy A to B
	 */
	// cla3p::dns::RfMatrix B = A; // this operation is not allowed
	cla3p::dns::RfMatrix B = A.copy();
	std::cout << B.info("B") << B;

	/*
	 * Move A to C
	 */
	cla3p::dns::RfMatrix C = A.move();
	std::cout << A.info("A") << A;
	std::cout << C.info("C") << C;

	return 0;
}
