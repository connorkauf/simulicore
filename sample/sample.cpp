#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::dns::RdVector V1(5);
	cla3p::dns::RdVector V2(5);
	V1 = 1;
	V2 = 2;
	std::cout << V1.info("V1") << V1;
	std::cout << V2.info("V2") << V2;

	cla3p::dns::RdVector V3 = V1 + V2;
	std::cout << V3.info("V3") << V3;

	V3 += V1;
	std::cout << V3.info("V3") << V3;

	cla3p::dns::RfMatrix A(5,3);
	A = -1;
	std::cout << A.info("A") << A;

	cla3p::PiMatrix P = cla3p::PiMatrix::random(5);
	std::cout << P.info("P") << P;


	return 0;
}
/*-------------------------------------------------*/
