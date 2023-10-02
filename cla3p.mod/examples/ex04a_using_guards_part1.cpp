#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Create a constant vector
	 */
	const cla3p::dns::RdVector X = cla3p::dns::RdVector::init(5);

	/*
	 * Get a shallow copy of a constant vector using the Guard class
	 */
	cla3p::Guard<cla3p::dns::RdVector> gY = X.rcopy();

	/*
	 * Get an immutable reference of the copied vector
	 */
	const cla3p::dns::RdVector& Y = gY.get();

	/*
	 * Get info of the two vectors
	 */
	std::cout << X.info("X") << Y.info("Y") << std::endl;

	return 0;
}
