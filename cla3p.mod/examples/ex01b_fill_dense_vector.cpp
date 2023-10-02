#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdVector X(3);
	cla3p::dns::RdVector Y(3);
	cla3p::dns::RdVector Z(3);

	/* 
	 * set all values in X to 1.5
	 */
	X.fill(1.5);

	/* 
	 * set all values in Y to -2.7
	 */
	Y = -2.7;

	/* 
	 * insert values in Z
	 */
	Z(0) = 3.;
	Z(1) = 2.;
	Z(2) = 1.;

	/* 
	 * print contents
	 */
	std::cout << X << Y << Z;

	return 0;
}
