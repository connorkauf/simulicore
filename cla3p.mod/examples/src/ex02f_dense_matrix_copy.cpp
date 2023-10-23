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
	 * Copy A to B using copy()
	 *
	 * Copy assignment: 
	 * cla3p::dns::RfMatrix B = A;
	 * is not allowed
	 */

	cla3p::dns::RfMatrix B = A.copy();

	std::cout << B.info("B") << B;

	return 0;
}
