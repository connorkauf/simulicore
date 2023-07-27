#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/operations.hpp"

/*-------------------------------------------------*/
template <typename T>
static void traitPrinter()
{
	std::cout << cla3p::BasicTypeTraits<T>::typeStr() << " " << cla3p::BasicTypeTraits<T>::precStr() << std::endl;
}
/*-------------------------------------------------*/

int main()
{
	traitPrinter<cla3p::int_t>();
	traitPrinter<cla3p::uint_t>();
	traitPrinter<cla3p::real_t>();
	traitPrinter<cla3p::real4_t>();
	traitPrinter<cla3p::complex_t>();
	traitPrinter<cla3p::complex8_t>();

	traitPrinter<cla3p::BasicTypeTraits<cla3p::complex_t>::real_type>();

	return 0;

	cla3p::dns::RdVector V1(5);
	cla3p::dns::RdVector V2(5);
	V1 = 1;
	V2 = 2;
	std::cout << V1.info("V1") << V1;
	std::cout << V2.info("V2") << V2;

	cla3p::dns::RdVector V3 = V1 + V2;
	std::cout << V3.info("V3") << V3;

	V3 += V1;
	std::cout << V3.info("V3") << V3;

	return 0;
}
/*-------------------------------------------------*/
