// this file inc
#include "types.hpp"

// system
#include <complex>

// 3rd

// cla3p
#include "error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
complex_t cval(real_t re, real_t im)
{
  return {re, im};
}
/*-------------------------------------------------*/
complex_t czero()
{
  return cval(0.,0.);
}
/*-------------------------------------------------*/
Property::Property()
	: m_type(ptype_t::NONE)
{
}
/*-------------------------------------------------*/
Property::Property(ptype_t ptype)
	: m_type(ptype)
{
}
/*-------------------------------------------------*/
Property::Property(const Property& src)
	: m_type(src.type())
{
}
/*-------------------------------------------------*/
Property& Property::operator=(const Property& src)
{
	m_type = src.type();
	return *this;
}
/*-------------------------------------------------*/
Property::~Property()
{
}
/*-------------------------------------------------*/
ptype_t Property::type() const
{
	return m_type;
}
/*-------------------------------------------------*/
const std::string pname_none      = "None"     ;
const std::string pname_general   = "General"  ;
const std::string pname_symmetric = "Symmetric";
const std::string pname_hermitian = "Hermitian";
/*-------------------------------------------------*/
const std::string& Property::name() const
{
	if(type() == ptype_t::NONE     ) return pname_none     ;
	if(type() == ptype_t::GENERAL  ) return pname_general  ;
	if(type() == ptype_t::SYMMETRIC) return pname_symmetric;
	if(type() == ptype_t::HERMITIAN) return pname_hermitian;

	throw Exception();
}
/*-------------------------------------------------*/
bool Property::is_valid() const
{
	return (type() != ptype_t::NONE);
}
/*-------------------------------------------------*/
bool Property::is_general() const
{
	return (type() == ptype_t::GENERAL);
}
/*-------------------------------------------------*/
bool Property::is_symmetric() const
{
	return (type() == ptype_t::SYMMETRIC);
}
/*-------------------------------------------------*/
bool Property::is_hermitian() const
{
	return (type() == ptype_t::HERMITIAN);
}
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






