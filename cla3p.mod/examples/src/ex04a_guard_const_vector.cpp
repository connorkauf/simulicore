/**
 * @example ex04a_guard_const_vector.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Create a constant vector
	 */

	const cla3p::dns::RdVector X = cla3p::dns::RdVector::random(5);

	/*
	 * Get a shallow copy of the constant vector using the Guard class
	 */

	cla3p::Guard<cla3p::dns::RdVector> Ygrd = X.rcopy();

	/*
	 * Get an immutable reference of the copied vector
	 */

	const cla3p::dns::RdVector& Y = Ygrd.get();

	/*
	 * Get info of the two vectors
	 */

	std::cout << X.info("X") << Y.info("Y") << std::endl;

	return 0;
}
