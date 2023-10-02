#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * double precision real empty vector
	 */
	cla3p::dns::RdVector X;

	/*
	 * single precision real vector with size 3 (uninitialized values)
	 */
	cla3p::dns::RfVector Y(3);

	/*
	 * allocate space for X (size 5, uninitialized values)
	 */
	X = cla3p::dns::RdVector::init(5);

	return 0;
}
