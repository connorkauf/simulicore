// this file inc
#include "types.hpp"

// system
#include <complex>

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
using stdcomplex_t = std::complex<cla3p::real_t>;
/*-------------------------------------------------*/
static inline stdcomplex_t complex2stdc(const cla3p::complex_t& c)
{
	return stdcomplex_t(c.real, c.imag);
}
/*-------------------------------------------------*/
static inline cla3p::complex_t stdc2complex(const stdcomplex_t& c)
{
	return cla3p::cval(c.real(), c.imag());
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::complex_t& c) {
	os << complex2stdc(c);
	return os;
}
/*-------------------------------------------------*/
cla3p::complex_t operator+(const cla3p::complex_t& c1, const cla3p::complex_t& c2)
{
	return stdc2complex(complex2stdc(c1) + complex2stdc(c2));
}
/*-------------------------------------------------*/
cla3p::complex_t operator-(const cla3p::complex_t& c1, const cla3p::complex_t& c2)
{
	return stdc2complex(complex2stdc(c1) - complex2stdc(c2));
}
/*-------------------------------------------------*/
cla3p::complex_t operator*(const cla3p::complex_t& c1, const cla3p::complex_t& c2)
{
	return stdc2complex(complex2stdc(c1) * complex2stdc(c2));
}
/*-------------------------------------------------*/
cla3p::complex_t operator/(const cla3p::complex_t& c1, const cla3p::complex_t& c2)
{
	return stdc2complex(complex2stdc(c1) / complex2stdc(c2));
}
/*-------------------------------------------------*/






