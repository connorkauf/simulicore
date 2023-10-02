#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/* 
	 * single precision complex vector (size 4, random values in [0,1])
	 */
	cla3p::dns::CfVector X = cla3p::dns::CfVector::random(4);

	/* 
	 * print X info & contents
	 */
	std::cout << X.info() << std::endl;
	std::cout << X;

	return 0;
}
