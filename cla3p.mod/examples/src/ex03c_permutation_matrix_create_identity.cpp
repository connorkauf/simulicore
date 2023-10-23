/**
 * @example ex03c_permutation_matrix_create_identity.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/* 
	 * (5x5) permutation matrix (identity -> Q[i] = i)
	 */

	cla3p::PiMatrix Q = cla3p::PiMatrix::identity(5);

	std::cout << Q.info("Q") << Q;

	return 0;
}
