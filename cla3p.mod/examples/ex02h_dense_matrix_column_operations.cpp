#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,5);
	std::cout << A.info("A") << A;

	/*
	 * Get a copy of column 1 of A as a vector
	 */
	cla3p::dns::RdVector Acol1 = A.column(1);

	/*
	 * Get a shallow copy of column 3 of A as a vector
	 */
	cla3p::dns::RdVector Arcol3 = A.rcolumn(3);

	std::cout << "Acol1:\n" << Acol1;
	std::cout << "Arcol3:\n" << Arcol3;

	Acol1 = 1; // fill Acol1 with ones
	Arcol3 = 0; // fill Arcol3 with zeros
	std::cout << "A after value changes in Acol1 & Arcol3:\n" << A;

	return 0;
}
