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

	cla3p::BasicTypeTraits<cla3p::dns::RdVector>::element_type alpha = 0.1;

	std::cout << alpha << std::endl;

	cla3p::BasicTypeTraits<cla3p::dns::RdVector>::equivalent_matrix B(7,3);
	B = 9;
	std::cout << B.info("B") << B;

	return 0;
}
/*-------------------------------------------------*/
