/**
 * @example ex03d_permutation_matrix_create_random.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/* 
	 * (4x4) permutation matrix 
	 * with randomly generated unique values
	 */

	cla3p::prm::PiMatrix P = cla3p::prm::PiMatrix::random(4);

	std::cout << P.info("P") << P;

	return 0;
}
