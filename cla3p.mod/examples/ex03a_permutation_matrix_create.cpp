#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/*
	 * An empty permutation matrix
	 */

	cla3p::PiMatrix P;

	/*
	 * (3x3) permutation matrix (uninitialized values)
	 */

	cla3p::PiMatrix Q(3);

	/*
	 * Allocate space for a (5x5) P (uninitialized values)
	 */

	P = cla3p::PiMatrix::init(5);

	return 0;
}
