#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	cla3p::PiMatrix P1(3);
	cla3p::PiMatrix P2(3);
	cla3p::PiMatrix P3(3);

	/* 
	 * set all values in P1 to 0
	 */
	P1.fill(0);

	/* 
	 * set all values in P2 to -1
	 */
	P2 = -1;

	/* 
	 * insert values in P3
	 */
	P3(0) = 2;
	P3(1) = 0;
	P3(2) = 1;

	/* 
	 * print contents
	 */
	std::cout << P1 << P2 << P3;

	return 0;
}
