#include <iostream>
#include "cla3p/types.hpp"

int main()
{
	//
	// Instantiate various properties
	//

	cla3p::Property prG(cla3p::prop_t::General  , cla3p::uplo_t::F); // the default property
	cla3p::Property prS(cla3p::prop_t::Symmetric, cla3p::uplo_t::L); // symmetric lower property
	cla3p::Property prH(cla3p::prop_t::Hermitian, cla3p::uplo_t::U); // hermitian upper property

	std::cout << prG << std::endl;
	std::cout << prS << std::endl;
	std::cout << prH << std::endl;

	return 0;
}

