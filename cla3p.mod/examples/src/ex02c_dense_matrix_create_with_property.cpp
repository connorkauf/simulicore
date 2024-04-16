/**
 * @example ex02c_dense_matrix_create_with_property.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Create properties for A, B and C
	 */

	cla3p::Property prA = cla3p::Property::General();
	cla3p::Property prB = cla3p::Property::SymmetricLower();
	cla3p::Property prC = cla3p::Property::HermitianUpper();

	/*
	 * Declare matrices with a property
	 */

	{
		cla3p::dns::RfMatrix A(3, 4, prA);
		cla3p::dns::RfMatrix B(3, 3, prB);
		cla3p::dns::CdMatrix C(3, 3, prC);
		std::cout << A.info("A") << B.info("B") << C.info("C");
	}

	/*
	 * Use the init() function to allocate space with property
	 */

	{
		cla3p::dns::RfMatrix A = cla3p::dns::RfMatrix::init(3, 4, prA);
		cla3p::dns::RfMatrix B = cla3p::dns::RfMatrix::init(3, 3, prB);
		cla3p::dns::CdMatrix C = cla3p::dns::CdMatrix::init(3, 3, prC);
	}

	return 0;
}
