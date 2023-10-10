#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X = cla3p::dns::RfVector::random(3);
	std::cout << X.info("X") << X;

	/*
	 * Copy X to Y
	 */

	// cla3p::dns::RfVector Y = X; // this operation is not allowed
	cla3p::dns::RfVector Y = X.copy();
	std::cout << Y.info("Y") << Y;

	return 0;
}
