#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/

int main()
{
	const cla3p::dns::RdVector V1(5);
	std::cout << V1.info("V1") << V1;

	cla3p::Guard<cla3p::dns::RdMatrix> GA = V1.rmatrix();
	const cla3p::dns::RdMatrix& A = GA.get();
	std::cout << A.info("A") << A;

	return 0;
}
/*-------------------------------------------------*/
