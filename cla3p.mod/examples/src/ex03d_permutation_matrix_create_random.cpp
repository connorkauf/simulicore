/**
 * @example ex03d_permutation_matrix_create_random.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/* 
	 * (4x4) permutation matrix (randomly generated unique values)
	 */

	cla3p::PiMatrix P = cla3p::PiMatrix::random(4);

	std::cout << P.info("P") << P;

	return 0;
}
