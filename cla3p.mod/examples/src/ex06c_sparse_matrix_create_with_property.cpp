/**
 * @example ex06c_sparse_matrix_create_with_property.cpp
 */

#include <iostream>
#include "cla3p/sparse.hpp"

int main()
{
	/*
	 * Create properties for A, B and C
	 */

	cla3p::Property prA(cla3p::prop_t::General  , cla3p::uplo_t::Full );
	cla3p::Property prB(cla3p::prop_t::Symmetric, cla3p::uplo_t::Lower);
	cla3p::Property prC(cla3p::prop_t::Hermitian, cla3p::uplo_t::Upper);

	/*
	 * Declare matrices with a property
	 */

	{
		cla3p::coo::RfMatrix A(30, 40, 10, prA);
		cla3p::coo::RfMatrix B(30, 30, 10, prB);
		cla3p::coo::CdMatrix C(30, 30, 10, prC);
		std::cout << A.info("A") << B.info("B") << C.info("C");
	}

	/*
	 * Use the init() function to allocate space with property
	 */

	{
		cla3p::coo::RfMatrix A = cla3p::coo::RfMatrix::init(3, 4, 10, prA);
		cla3p::coo::RfMatrix B = cla3p::coo::RfMatrix::init(3, 3, 10, prB);
		cla3p::coo::CdMatrix C = cla3p::coo::CdMatrix::init(3, 3, 10, prC);
	}

	return 0;
}
