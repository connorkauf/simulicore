/**
 * @example ex01c_dense_vector_create_from_aux_data.cpp 
 */

#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Allocate space for x & y
	 */

	cla3p::real_t *x = cla3p::i_calloc<cla3p::real_t>(5); 
	cla3p::real_t *y = cla3p::i_calloc<cla3p::real_t>(3); 

	for(cla3p::uint_t i = 0; i < 5; i++)
		x[i] = i;

	for(cla3p::uint_t i = 0; i < 3; i++)
		y[i] = 3 - i;

	/*
	 * Assign pointer x in vector X but do not bind
	 * X simply hosts x, need to manually dealloc x
	 */

	cla3p::dns::RdVector X = cla3p::dns::RdVector::wrap(5, x, false);

	std::cout << X.info("X") << X;

	/*
	 * Assign pointer y in vector Y and bind
	 * Y takes ownership of y, no free call for y is required
	 */

	cla3p::dns::RdVector Y = cla3p::dns::RdVector::wrap(3, y, true);

	std::cout << Y.info("Y") << Y;

	/* 
	 * Free x and exit
	 */

	cla3p::i_free(x);

	return 0;
}
