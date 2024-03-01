/**
 * @example ex03a_permutation_matrix_create.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/*
	 * An empty permutation matrix
	 */

	cla3p::prm::PiMatrix P;

	std::cout << P.info("P");

	/*
	 * (3x3) permutation matrix (uninitialized values)
	 */

	cla3p::prm::PiMatrix Q(3);

	std::cout << Q.info("Q");

	/*
	 * Allocate space for a (5x5) P (uninitialized values)
	 */

	P = cla3p::prm::PiMatrix::init(5);

	std::cout << P.info("P");

	return 0;
}
