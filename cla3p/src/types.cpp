// this file inc
#include "types.hpp"

// system

// 3rd

// cla3p
#include "support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Operation::Operation()
	: m_type(op_t::N)
{
}
/*-------------------------------------------------*/
Operation::Operation(const Operation& other)
	: m_type(other.type())
{
}
/*-------------------------------------------------*/
Operation& Operation::operator=(const Operation& other)
{
	m_type = other.type();
	return *this;
}
/*-------------------------------------------------*/
Operation::Operation(op_t otype)
	: m_type(otype)
{
}
/*-------------------------------------------------*/
Operation::~Operation()
{
}
/*-------------------------------------------------*/
op_t Operation::type() const
{
	return m_type;
}
/*-------------------------------------------------*/
const std::string oname_noop = "No operation"  ;
const std::string oname_trop = "Transpose";
const std::string oname_ctop = "Conjugate transpose";
/*-------------------------------------------------*/
const std::string& Operation::name() const
{
	if(type() == op_t::N) return oname_noop;
	if(type() == op_t::T) return oname_trop;
	if(type() == op_t::C) return oname_ctop;

	throw Exception("Unknown operation");
	return oname_noop;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
Property::Property()
	: m_type(prop_t::NONE), m_uplo(uplo_t::F)
{
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
Property::Property(prop_t type)
	: m_type(type)
{
	m_uplo = (type == prop_t::GENERAL ? uplo_t::F : uplo_t::L);
	check();
}
/*-------------------------------------------------*/
Property::Property(prop_t type, uplo_t uplo)
	: m_type(type), m_uplo(uplo)
{
	check();
}
/*-------------------------------------------------*/
Property::~Property()
{
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
	if(is_general() && !is_full()) {
		throw NoConsistency("Bad type/uplo combo");
	} 
	if(!is_general() && is_full()) {
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
const std::string& Property::name() const
{
	if(type() == prop_t::NONE) return pname_none;

	if(type() == prop_t::GENERAL   && uplo() == uplo_t::F) return pname_general;
	if(type() == prop_t::SYMMETRIC && uplo() == uplo_t::U) return pname_usymmetric;
	if(type() == prop_t::SYMMETRIC && uplo() == uplo_t::L) return pname_lsymmetric;
	if(type() == prop_t::HERMITIAN && uplo() == uplo_t::U) return pname_uhermitian;
	if(type() == prop_t::HERMITIAN && uplo() == uplo_t::L) return pname_lhermitian;

	throw Exception("Unknown/Invalid property");
	return pname_none;
}
/*-------------------------------------------------*/
bool Property::is_valid() const
{
	return (type() != prop_t::NONE);
}
/*-------------------------------------------------*/
bool Property::isSquare() const
{
	return (type() == prop_t::SYMMETRIC || type() == prop_t::HERMITIAN);
}
/*-------------------------------------------------*/
bool Property::is_general() const
{
	return (type() == prop_t::GENERAL);
}
/*-------------------------------------------------*/
bool Property::is_symmetric() const
{
	return (type() == prop_t::SYMMETRIC);
}
/*-------------------------------------------------*/
bool Property::is_hermitian() const
{
	return (type() == prop_t::HERMITIAN);
}
/*-------------------------------------------------*/
bool Property::is_full() const
{
	return (uplo() == uplo_t::F);
}
/*-------------------------------------------------*/
bool Property::is_upper() const
{
	return (uplo() == uplo_t::U);
}
/*-------------------------------------------------*/
bool Property::is_lower() const
{
	return (uplo() == uplo_t::L);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op)
{
	os << op.name();
	return os;
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::Property& prop)
{
	os << prop.name();
	return os;
}
/*-------------------------------------------------*/


