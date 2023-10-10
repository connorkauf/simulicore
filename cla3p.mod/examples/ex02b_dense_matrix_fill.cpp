#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A(2,2);
	cla3p::dns::RdMatrix B(2,2);
	cla3p::dns::RdMatrix C(2,2);

	/* 
	 * Set all values in A to 1
	 */

	A.fill(1.);
	std::cout << A;

	/* 
	 * Set all values in B to -2
	 */

	B = -2.;
	std::cout << B;

	/* 
	 * Insert values in C
	 */

	C(0,0) = 3.;
	C(1,0) = 2.;
	C(0,1) = 1.;
	C(1,1) = 0.;
	std::cout << C;

	return 0;
}
