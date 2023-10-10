#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,5);
	std::cout << A.info("A") << A;

	/*
	 * Get a (2x2) copy of the contents of A starting at (1,2)
	 * Get a (3x2) reference of the contents of A starting at (2,0)
	 */

	cla3p::dns::RdMatrix Ab = A.block(1, 2, 2, 2);
	cla3p::dns::RdMatrix Ar = A.rblock(2, 0, 3, 2);
	std::cout << "Ab:\n" << Ab;
	std::cout << "Ar:\n" << Ar;

	Ab = 1; // fill Ab with ones
	Ar = 0; // fill Ar with zeros
	std::cout << "A after value changes in Ab & Ar:\n" << A;

	/*
	 * Set values of Ab to A, starting at (1,1)
	 */

	A.setBlock(1, 1, Ab);
	std::cout << "A after setBlock():\n" << A;

	return 0;
}
