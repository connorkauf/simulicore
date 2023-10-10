#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X = cla3p::dns::RfVector::random(3);
	std::cout << X.info("X") << X;

	/*
	 * Move X to Y
	 */

	cla3p::dns::RfVector Y = X.move();
	std::cout << X.info("X") << X;
	std::cout << Y.info("Y") << Y;

	return 0;
}
