#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Allocate space for x & y
	 */

	cla3p::real_t *x = static_cast<cla3p::real_t*>(cla3p::i_calloc(5, sizeof(cla3p::real_t))); 
	cla3p::real_t *y = static_cast<cla3p::real_t*>(cla3p::i_calloc(3, sizeof(cla3p::real_t))); 

	/*
	 * Assign pointer x in vector X but do not bind
	 * X simply hosts x, need to manually dealloc x
	 */

	cla3p::dns::RdVector X = cla3p::dns::RdVector::wrap(5, x, false);
	std::cout << X.info() << std::endl;

	/*
	 * Assign pointer y in vector Y and bind
	 * Y takes ownership of y, no free call for y is required
	 */

	cla3p::dns::RdVector Y = cla3p::dns::RdVector::wrap(3, y, true);
	std::cout << Y.info() << std::endl;

	/* 
	 * Free x and exit
	 */

	cla3p::i_free(x);

	return 0;
}
