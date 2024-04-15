/**
 * @example ex02f_dense_matrix_copy.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfMatrix A(3,3);
	A = 2;

	std::cout << A.info("A") << A;

	/*
	 * Copy A to B using assignment
	 * Copy A to C using copy()
	 */

	cla3p::dns::RfMatrix B = A;
	cla3p::dns::RfMatrix C = A.copy();

	std::cout << B.info("B") << B;
	std::cout << C.info("C") << C;

	/*
	 * Copy B to C using assignment 
	 * C is already allocated 
	 * No re-allocation performed 
	 * Needs matching dimensions/property
	 */

	C = B;

	std::cout << C.info("C") << C;

	return 0;
}
