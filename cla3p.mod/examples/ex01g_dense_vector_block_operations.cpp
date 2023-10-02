#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdVector X = cla3p::dns::RdVector::random(5);
	std::cout << X.info("X") << X;

	/*
	 * Get a copy of X[1:3] in Xb
	 * Get a reference of X[2:5] in Xr
	 */
	cla3p::dns::RdVector Xb = X.block(1, 2);
	cla3p::dns::RdVector Xr = X.rblock(2, 3);
	std::cout << "Xb:\n" << Xb;
	std::cout << "Xr:\n" << Xr;

	Xb = 1; // fill Xb with ones
	Xr = 0; // fill Xr with zeros
	std::cout << "X after value changes in Xb & Xr:\n" << X;

	/*
	 * Set values of Xb to X, starting at index 1
	 */
	X.setBlock(1, Xb);
	std::cout << "X after setBlock():\n" << X;

	return 0;
}
