// this file inc
#include "cla3p/types/property.hpp"

// system

// 3rd

// cla3p
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
const std::string pname_none = "None";
/*-------------------------------------------------*/
const std::string pname_general = "General";
/*-------------------------------------------------*/
const std::string pname_usymmetric = "Symmetric Upper";
const std::string pname_lsymmetric = "Symmetric Lower";
/*-------------------------------------------------*/
const std::string pname_uhermitian = "Hermitian Upper";
const std::string pname_lhermitian = "Hermitian Lower";
/*-------------------------------------------------*/
const std::string pname_utriangular = "Triangular/Trapezoidal Upper";
const std::string pname_ltriangular = "Triangular/Trapezoidal Lower";
/*-------------------------------------------------*/
const std::string pname_uskew = "Skew Upper";
const std::string pname_lskew = "Skew Lower";
/*-------------------------------------------------*/
const std::string& Property::name() const
{
	if(type() == prop_t::NONE) return pname_none;

	if(type() == prop_t::GENERAL    && uplo() == uplo_t::F) return pname_general;
	if(type() == prop_t::SYMMETRIC  && uplo() == uplo_t::U) return pname_usymmetric;
	if(type() == prop_t::SYMMETRIC  && uplo() == uplo_t::L) return pname_lsymmetric;
	if(type() == prop_t::HERMITIAN  && uplo() == uplo_t::U) return pname_uhermitian;
	if(type() == prop_t::HERMITIAN  && uplo() == uplo_t::L) return pname_lhermitian;
	if(type() == prop_t::TRIANGULAR && uplo() == uplo_t::U) return pname_utriangular;
	if(type() == prop_t::TRIANGULAR && uplo() == uplo_t::L) return pname_ltriangular;
	if(type() == prop_t::SKEW       && uplo() == uplo_t::U) return pname_uskew;
	if(type() == prop_t::SKEW       && uplo() == uplo_t::L) return pname_lskew;

	throw Exception("Unknown/Invalid property");
	return pname_none;
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
