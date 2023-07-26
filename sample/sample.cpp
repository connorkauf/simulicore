#include <iostream>

#include "cla3p/src/dense.hpp"

/*-------------------------------------------------*/

int main()
{

	cla3p::dns::RdVector V1 = cla3p::dns::RdVector::random(3);
	V1 = 1;
	V1(1) = 2;
	std::cout << V1.info("V1") << V1;

	cla3p::dns::RdVector V2 = V1.copy();
	std::cout << V2.info("V2") << V2;

	cla3p::dns::RdVector V3 = V2.rcopy();
	std::cout << V3.info("V3") << V3;

	cla3p::dns::RdVector V4 = V3.move();
	std::cout << V3.info("V3") << V3;
	std::cout << V4.info("V4") << V4;

	return 0;
}
/*-------------------------------------------------*/
