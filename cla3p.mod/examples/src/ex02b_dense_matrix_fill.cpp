/**
 * @example ex02b_dense_matrix_fill.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A(2,2);
	cla3p::dns::RdMatrix B(2,2);
	cla3p::dns::RdMatrix C(2,2);

	/* 
	 * Set all values in A to 1 (using member function)
	 * Set all values in B to -2 (using operator=)
	 */

	A.fill(1.);
	B = -2.;

	/* 
	 * Insert values in C manually
	 */

	C(0,0) = 3.;
	C(1,0) = 2.;
	C(0,1) = 1.;
	C(1,1) = C(0,0) + C(1,0) + C(0,1);

	std::cout << "A:\n" << A << "\n";
	std::cout << "B:\n" << B << "\n";
	std::cout << "C:\n" << C;

	return 0;
}
