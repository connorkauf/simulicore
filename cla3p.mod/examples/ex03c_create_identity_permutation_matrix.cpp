#include <iostream>
#include "cla3p/perms.hpp"

int main()
{
	/* 
	 * (5x5) permutation matrix (identity values)
	 */
	cla3p::PiMatrix Q = cla3p::PiMatrix::identity(5);

	std::cout << Q.info("Q") << Q;

	return 0;
}
