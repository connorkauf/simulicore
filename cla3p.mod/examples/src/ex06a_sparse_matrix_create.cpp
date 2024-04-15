/**
 * @example ex06a_sparse_matrix_create.cpp
 */

#include <iostream>
#include "cla3p/sparse.hpp"

int main()
{
	/*
	 * Double precision real empty matrix
	 */

	cla3p::csc::RdMatrix A;
	cla3p::coo::RdMatrix B;

	std::cout << A.info("A");
	std::cout << B.info("B");

	/*
	 * (3x4) single precision real matrix
	 */

	cla3p::coo::RfMatrix C(3,4);

	std::cout << C.info("C");

	/*
	 * Initialize a (5x2) empty sparse matrix
	 */

	B = cla3p::coo::RdMatrix::init(5,2);

	std::cout << B.info("B");

	return 0;
}
