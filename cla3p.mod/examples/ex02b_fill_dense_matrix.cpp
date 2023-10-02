#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A(2,2);
	cla3p::dns::RdMatrix B(2,2);
	cla3p::dns::RdMatrix C(2,2);

	/* 
	 * set all values in A to 1
	 */
	A.fill(1.);

	/* 
	 * set all values in B to -2
	 */
	B = -2.;

	/* 
	 * insert values in Z
	 */
	C(0,0) = 3.;
	C(1,0) = 2.;
	C(0,1) = 1.;
	C(1,1) = 0.;

	/* 
	 * print contents
	 */
	std::cout << A << B << C;

	return 0;
}
