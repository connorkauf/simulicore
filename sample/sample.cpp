#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::Property pr(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::L);
	cla3p::dns::RdMatrix A(5,5, pr);
	A = 3;
	std::cout << A.info("A") << A;

	cla3p::dns::RdMatrix B = -A;
	std::cout << B.info("B") << B;

	//cla3p::dns::RdMatrix A1(2,2);
	//A1 = 2;
	//std::cout << A1.info("A1") << A1;
	//
	//A.setBlock(2,1,A1);
	//std::cout << A.info("A") << A;


	return 0;


	//cla3p::dns::RdVector V1(5);
	//V1 = 2;
	//std::cout << V1.info("V1") << V1;
	//
	//cla3p::dns::RdMatrix A(5,3);
	//A = 3;
	//std::cout << A.info("A") << A;
	//
	//cla3p::dns::RdVector Aj = A.column(2);
	//std::cout << Aj.info("Aj") << Aj;

	return 0;
}
/*-------------------------------------------------*/
