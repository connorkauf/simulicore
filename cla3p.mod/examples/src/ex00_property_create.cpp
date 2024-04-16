/**
 * @example ex00_property_create.cpp
 */

#include <iostream>
#include "cla3p/types.hpp"

int main()
{
	/*
	 * Instantiate various properties
	 */

	cla3p::Property prG = cla3p::Property::General(); // the default property
	cla3p::Property prS = cla3p::Property::SymmetricLower(); // symmetric lower property
	cla3p::Property prH(cla3p::prop_t::Hermitian, cla3p::uplo_t::Upper); // hermitian upper property

	std::cout << "Property G: " << prG << std::endl;
	std::cout << "Property S: " << prS << std::endl;
	std::cout << "Property H: " << prH << std::endl;

	/*
	 * Instantiate an invalid property
	 */

	try {
		cla3p::Property invalidProperty(cla3p::prop_t::General, cla3p::uplo_t::Upper);
	} catch(...) {
		std::cout << "Exception throwed for invalid property" << std::endl;
	}

	return 0;
}

