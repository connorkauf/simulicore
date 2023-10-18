// this file inc
#include "cla3p/types/property.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"
#include "cla3p/error/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Property::Property()
{
	defaults();
}
/*-------------------------------------------------*/
Property::Property(const Property& other)
	: m_type(other.type()), m_uplo(other.uplo())
{
}
/*-------------------------------------------------*/
Property& Property::operator=(const Property& other)
{
	m_type = other.type();
	m_uplo = other.uplo();
	return *this;
}
/*-------------------------------------------------*/
bool Property::operator==(const Property& other) const
{
	return (m_type == other.type() && m_uplo == other.uplo());
}
/*-------------------------------------------------*/
bool Property::operator!=(const Property& other) const
{
	return !(*this == other);
}
/*-------------------------------------------------*/
Property::Property(prop_t ptype, uplo_t ftype)
	: m_type(ptype), m_uplo(ftype)
{
	check();
}
/*-------------------------------------------------*/
Property::~Property()
{
}
/*-------------------------------------------------*/
void Property::defaults()
{
	m_type = prop_t::Undefined;
	m_uplo = uplo_t::Full;
}
/*-------------------------------------------------*/
void Property::clear()
{
	defaults();
}
/*-------------------------------------------------*/
prop_t Property::type() const
{
	return m_type;
}
/*-------------------------------------------------*/
uplo_t Property::uplo() const
{
	return m_uplo;
}
/*-------------------------------------------------*/
char Property::cuplo() const
{
	return static_cast<char>(uplo());
}
/*-------------------------------------------------*/
void Property::check() const
{
	if(isGeneral() && !isFull()) {
		throw err::NoConsistency("Bad type/uplo combo");
	} 
	if(!isGeneral() && isFull()) {
		throw err::NoConsistency("Bad type/uplo combo");
	} 
}
/*-------------------------------------------------*/
std::string Property::name() const
{
	std::string strProp = msg::Unknown();
	std::string strUplo = "";

	if(type() == prop_t::General   ) strProp = msg::General();
	if(type() == prop_t::Symmetric ) strProp = msg::Symmetric();
	if(type() == prop_t::Hermitian ) strProp = msg::Hermitian();
	if(type() == prop_t::Triangular) strProp = msg::Triangular();
	if(type() == prop_t::Skew      ) strProp = msg::Skew();

	if(uplo() == uplo_t::Upper) strUplo = msg::Upper();
	if(uplo() == uplo_t::Lower) strUplo = msg::Lower();

	return (strProp + " " + strUplo);
}
/*-------------------------------------------------*/
bool Property::isValid() const
{
	return (type() != prop_t::Undefined);
}
/*-------------------------------------------------*/
bool Property::isSquare() const
{
	return (isSymmetric() || isHermitian() || isSkew());
}
/*-------------------------------------------------*/
bool Property::isGeneral() const
{
	return (type() == prop_t::General);
}
/*-------------------------------------------------*/
bool Property::isSymmetric() const
{
	return (type() == prop_t::Symmetric);
}
/*-------------------------------------------------*/
bool Property::isHermitian() const
{
	return (type() == prop_t::Hermitian);
}
/*-------------------------------------------------*/
bool Property::isTriangular() const
{
	return (type() == prop_t::Triangular);
}
/*-------------------------------------------------*/
bool Property::isSkew() const
{
	return (type() == prop_t::Skew);
}
/*-------------------------------------------------*/
bool Property::isFull() const
{
	return (uplo() == uplo_t::Full);
}
/*-------------------------------------------------*/
bool Property::isUpper() const
{
	return (uplo() == uplo_t::Upper);
}
/*-------------------------------------------------*/
bool Property::isLower() const
{
	return (uplo() == uplo_t::Lower);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::Property& prop)
{
	os << prop.name();
	return os;
}
/*-------------------------------------------------*/
