#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdVector X(3);
	cla3p::dns::RdVector Y(3);
	cla3p::dns::RdVector Z(3);

	/* 
	 * Set all values in X to 1.5
	 */

	X.fill(1.5);
	std::cout << X;

	/* 
	 * Set all values in Y to -2.7
	 */

	Y = -2.7;
	std::cout << Y;

	/* 
	 * Insert values in Z
	 */

	Z(0) = 3.;
	Z(1) = 2.;
	Z(2) = 1.;
	std::cout << Z;

	return 0;
}
