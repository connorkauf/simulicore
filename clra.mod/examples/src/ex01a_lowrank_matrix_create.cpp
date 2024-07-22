/**
 * @example ex01a_lowrank_matrix_create.cpp
 */

#include <iostream>
#include "clra/matrix.hpp"

int main()
{
	/*
	 * Double precision real empty matrix
	 */

	cla3p::lra::RdMatrix A;

	std::cout << A.info("A");

	/*
	 * Rank 2 (3x4) single precision real matrix (uninitialized values)
	 */

	cla3p::lra::LrMatrix<cla3p::dns::RfMatrix> B(3,4,2);

	std::cout << B.info("B");

	/*
	 * Allocate space for A (rank 2, 5x3, uninitialized values)
	 */

	A = cla3p::lra::RdMatrix::init(5,3,2);

	std::cout << A.info("A");

	return 0;
}
