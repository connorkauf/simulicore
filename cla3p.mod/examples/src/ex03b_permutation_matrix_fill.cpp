/**
 * @example ex03b_permutation_matrix_fill.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	cla3p::prm::PiMatrix P1(3);
	cla3p::prm::PiMatrix P2(3);
	cla3p::prm::PiMatrix P3(3);

	/* 
	 * Set all values in P1 to 0 (not a valid permutation matrix)
	 * Set all values in P2 to -1 (not a valid permutation matrix)
	 * Insert values in P3
	 */

	P1.fill(0);

	P2 = -1;

	P3(0) = 2;
	P3(1) = 0;
	P3(2) = 1;

	std::cout << "P1:\n" << P1 << "\n";
	std::cout << "P2:\n" << P2 << "\n";
	std::cout << "P3:\n" << P3;

	return 0;
}
