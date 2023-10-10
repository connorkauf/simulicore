#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	cla3p::PiMatrix P1(3);
	cla3p::PiMatrix P2(3);
	cla3p::PiMatrix P3(3);

	/* 
	 * Set all values in P1 to 0
	 */

	P1.fill(0);
	std::cout << P1;

	/* 
	 * Set all values in P2 to -1
	 */

	P2 = -1;
	std::cout << P2;

	/* 
	 * Insert values in P3
	 */

	P3(0) = 2;
	P3(1) = 0;
	P3(2) = 1;
	std::cout << P3;

	return 0;
}
