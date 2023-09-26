#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(3,3);

	std::cout << A.info() << A;

	return 0;
}
