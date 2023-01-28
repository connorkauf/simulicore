#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/test.hpp"
//#include "cla3p/src/types.hpp"
//#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
//#include "cla3p/src/dns.hpp"
//#include "cla3p/src/dns_io.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/mkl_proxy.hpp"
#include "cla3p/src/dns_generic.hpp"
/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

	//using DataType = cla3p::real_t;
	using DataType = cla3p::real4_t;
	//using DataType = cla3p::complex_t;
	//using DataType = cla3p::complex8_t;

	cla3p::uint_t m = 3;
	cla3p::uint_t n = 3;
	cla3p::Property prop(cla3p::prop_t::HERMITIAN);
	
	cla3p::dns::GenericObject<DataType> ob1 = cla3p::dns::GenericObject<DataType>::init(prop, m, n);
	cla3p::dns::GenericObject<DataType> ob2 = cla3p::dns::GenericObject<DataType>::zero(prop, m, n);
	cla3p::dns::GenericObject<DataType> ob3 = cla3p::dns::GenericObject<DataType>::random(prop, m, n);

	ob1.print();
	ob2.print();
	ob3.print();

	return 0;
}
/*-------------------------------------------------*/
