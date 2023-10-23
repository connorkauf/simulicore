/**
 * @example ex04b_guard_const_matrix.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Create a constant matrix
	 */

	const cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,5);

	/*
	 * Get a shallow copy of a block of A using the Guard class
	 */

	cla3p::Guard<cla3p::dns::RdMatrix> Agrd22 = A.rblock(1, 2, 2, 2);

	/*
	 * Get an immutable reference of the block
	 */

	const cla3p::dns::RdMatrix& A22 = Agrd22.get();

	/*
	 * Get info of A22
	 */

	std::cout << A22.info("A22") << std::endl;

	return 0;
}
