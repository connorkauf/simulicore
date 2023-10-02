#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * allocate space for x & y and assume are filled with some values
	 */
	cla3p::real_t *x = static_cast<cla3p::real_t*>(cla3p::i_malloc(5)); 
	cla3p::real_t *y = static_cast<cla3p::real_t*>(cla3p::i_malloc(3)); 

	/*
	 * assign pointer x in vector X but do not bind (need to manually dealloc x)
	 */
	cla3p::dns::RdVector X = cla3p::dns::RdVector::wrap(5, x, false);
	std::cout << X.info() << std::endl;

	/*
	 * assign pointer y in vector Y and bind (no free call for y is required)
	 */
	cla3p::dns::RdVector Y = cla3p::dns::RdVector::wrap(3, y, true);
	std::cout << Y.info() << std::endl;

	/* 
	 * free x and exit
	 */
	cla3p::i_free(x);

	return 0;
}
