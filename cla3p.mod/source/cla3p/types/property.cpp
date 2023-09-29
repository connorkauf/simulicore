// this file inc
#include "cla3p/types/property.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"
#include "cla3p/support/error.hpp"

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
	m_type = prop_t::NONE;
	m_uplo = uplo_t::F;
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
		throw NoConsistency("Bad type/uplo combo");
	} 
	if(!isGeneral() && isFull()) {
		throw NoConsistency("Bad type/uplo combo");
	} 
}
/*-------------------------------------------------*/
std::string Property::name() const
{
	std::string strProp = stringUnknown();
	std::string strUplo = "";

	if(type() == prop_t::GENERAL   ) strProp = stringGeneral();
	if(type() == prop_t::SYMMETRIC ) strProp = stringSymmetric();
	if(type() == prop_t::HERMITIAN ) strProp = stringHermitian();
	if(type() == prop_t::TRIANGULAR) strProp = stringTriangular();
	if(type() == prop_t::SKEW      ) strProp = stringSkew();

	if(uplo() == uplo_t::U) strUplo = stringUpper();
	if(uplo() == uplo_t::L) strUplo = stringLower();

	return (strProp + " " + strUplo);
}
/*-------------------------------------------------*/
bool Property::isValid() const
{
	return (type() != prop_t::NONE);
}
/*-------------------------------------------------*/
bool Property::isSquare() const
{
	return (isSymmetric() || isHermitian() || isSkew());
}
/*-------------------------------------------------*/
bool Property::isGeneral() const
{
	return (type() == prop_t::GENERAL);
}
/*-------------------------------------------------*/
bool Property::isSymmetric() const
{
	return (type() == prop_t::SYMMETRIC);
}
/*-------------------------------------------------*/
bool Property::isHermitian() const
{
	return (type() == prop_t::HERMITIAN);
}
/*-------------------------------------------------*/
bool Property::isTriangular() const
{
	return (type() == prop_t::TRIANGULAR);
}
/*-------------------------------------------------*/
bool Property::isSkew() const
{
	return (type() == prop_t::SKEW);
}
/*-------------------------------------------------*/
bool Property::isFull() const
{
	return (uplo() == uplo_t::F);
}
/*-------------------------------------------------*/
bool Property::isUpper() const
{
	return (uplo() == uplo_t::U);
}
/*-------------------------------------------------*/
bool Property::isLower() const
{
	return (uplo() == uplo_t::L);
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
