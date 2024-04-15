/**
 * @example ex01g_dense_vector_block_operations.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdVector X(5);

	for(cla3p::uint_t i = 0; i < 5; i++)
		X(i) = i;

	std::cout << "X:\n" << X << "\n";

	/*
	 * Get a copy of X[1:3) in Xb
	 * Get a reference of X[2:5) in Xr
	 */

	cla3p::dns::RdVector Xb = X.block(1, 2);
	cla3p::dns::RdVector Xr = X.rblock(2, 3);

	std::cout << "Xb:\n" << Xb;
	std::cout << "Xr:\n" << Xr;

	/*
	 * Get a guarded reference of Xref[2:5) in Xg
	 */

	const cla3p::dns::RdVector& Xref = X;

	cla3p::Guard<cla3p::dns::RdVector> Xg = Xref.rblock(2, 3);

	std::cout << "Xg:\n" << Xg.get() << "\n";

	/*
	 * Change values in blocks
	 */

	Xr = -1;

	std::cout << "X:\n" << X;

	/*
	 * Set values of Xb to X, starting at index 1
	 */

	Xb = -2;
	X.setBlock(1, Xb);

	std::cout << "X:\n" << X;

	/*
	 * Set values of Xb to X, starting at index 2
	 */

	Xb = -3;
	X.rblock(2, 2) = Xb;

	std::cout << "X:\n" << X;

	return 0;
}
