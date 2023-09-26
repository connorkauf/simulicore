#include <iostream>

#include "cla3p/dense.hpp"

/*-------------------------------------------------*/

int main()
{
	std::cout << "Hello Compact Suite!" << std::endl;

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3);
	std::cout << A.info() << A << A.normInf() << std::endl;

	return 0;
}
/*-------------------------------------------------*/
