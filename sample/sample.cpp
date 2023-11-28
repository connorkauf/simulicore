#include <iostream>

#include "cla3p/dense.hpp"

/*-------------------------------------------------*/

int main()
{
	std::cout << "Hello SimuliCore & CLA3P!" << std::endl;
	std::cout << "Integer size is: " << sizeof(cla3p::int_t) << std::endl;

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3);
	std::cout << A.info() << A << A.normInf() << std::endl;

	return 0;
}
/*-------------------------------------------------*/
