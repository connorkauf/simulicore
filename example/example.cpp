#include <iostream>
#include <cstdio>
#include <complex>

#include <omp.h>

//#include "cla3p/src/types.hpp"
//#include "cla3p/src/error.hpp"
//#include "cla3p/src/imalloc.hpp"
#include "cla3p/src/utils.hpp"
#include "cla3p/src/error_internal.hpp"
#include "cla3p/src/dns_generic.hpp"

#include "cla3p/src/proxies/mkl_proxy.hpp"
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
/*-------------------------------------------------*/
using Generic = cla3p::dns::GenericObject<cla3p::real_t>;
/*-------------------------------------------------*/
class dMatrix : private Generic {
	public:
		dMatrix(){}
		~dMatrix(){};

		dMatrix(const dMatrix&) = delete;
		dMatrix& operator=(const dMatrix&) = delete;

		dMatrix(dMatrix&& src)
		{
			*this = static_cast<Generic&&>(src);
		}
		dMatrix& operator=(dMatrix&& src)
		{
			*this = static_cast<Generic&&>(src);
			return *this;
		}

		void print() const
		{
			Generic::print();
		}

		static dMatrix random(const cla3p::Property& prop, cla3p::uint_t nrows, cla3p::uint_t ncols, cla3p::uint_t ld = Generic::defaultld)
		{
			return Generic::random(prop, nrows, ncols, ld);
		}

		cla3p::real_t& operator()(cla3p::uint_t i, cla3p::uint_t j)
		{
			return Generic::operator()(i,j);
		}
		const cla3p::real_t& operator()(cla3p::uint_t i, cla3p::uint_t j) const
		{
			return Generic::operator()(i,j);
		}

	private:
		dMatrix(Generic&& src)
		{
			Generic& generic_this = *this;
			generic_this = src.move();
		}

		dMatrix& operator=(Generic&& src)
		{
			Generic& generic_this = *this;
			generic_this = src.move();
			return *this;
		}
};
/*-------------------------------------------------*/
int main()
{
	std::printf("MKL_VERSION: '%s'\n", cla3p::mkl::version().c_str());
	cla3p::enable_dbg_messages();

#if 1
	{
		//using DataType = cla3p::real_t;
		//using DataType = cla3p::real4_t;
		//using DataType = cla3p::complex_t;
		using DataType = cla3p::complex8_t;

		cla3p::uint_t m = 3;
		cla3p::uint_t n = 3;
		cla3p::Property prop(cla3p::prop_t::HERMITIAN);

		cla3p::dns::GenericObject<DataType> ob1 = cla3p::dns::GenericObject<DataType>::init(prop, m, n);
		cla3p::dns::GenericObject<DataType> ob2 = cla3p::dns::GenericObject<DataType>::zero(prop, m, n);
		cla3p::dns::GenericObject<DataType> ob3 = cla3p::dns::GenericObject<DataType>::random(prop, m, n);

		ob3.print();
		//std::cout << ob3(2,1) << std::endl;;
		//ob3(2,1) = -1.;
		//std::cout << ob3(2,1) << std::endl;;
	}
#endif

	cla3p::uint_t m = 3;
	cla3p::uint_t n = 3;
	cla3p::Property prop(cla3p::prop_t::HERMITIAN);
	dMatrix A = dMatrix::random(prop, m, n);
	A.print();


	std::cout << A(2,1) << std::endl;;
	A(2,1) = -1.;
	std::cout << A(2,1) << std::endl;;





	return 0;
}
/*-------------------------------------------------*/
