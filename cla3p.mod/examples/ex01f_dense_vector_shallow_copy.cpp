#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RfVector X = cla3p::dns::RfVector::random(3);
	std::cout << X.info("X") << X;

	/*
	 * Reference Copy X to Y (X & Y share contents)
	 */
	cla3p::dns::RfVector Y = X.rcopy();
	std::cout << Y.info("Y") << Y;

	Y(0) = -1.2;
	Y(2) =  2.7;

	std::cout << X.info("X") << X;
	std::cout << Y.info("Y") << Y;

	return 0;
}
