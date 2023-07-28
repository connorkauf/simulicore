#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::dns::RdVector V1(5);
	V1 = 2;
	std::cout << V1.info("V1") << V1;

	cla3p::dns::RdMatrix A(5,3);
	A = 3;
	std::cout << A.info("A") << A;

	cla3p::dns::RdVector Aj = A.column(2);
	std::cout << Aj.info("Aj") << Aj;

	return 0;
}
/*-------------------------------------------------*/
