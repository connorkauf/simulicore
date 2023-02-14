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
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
Property::Property()
	: m_type(prop_t::NONE)
{
}
/*-------------------------------------------------*/
Property::Property(const Property& other)
	: m_type(other.type())
{
}
/*-------------------------------------------------*/
Property& Property::operator=(const Property& other)
{
	m_type = other.type();
	return *this;
}
/*-------------------------------------------------*/
Property::Property(prop_t ptype)
	: m_type(ptype)
{
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
const std::string pname_none      = "None"     ;
const std::string pname_general   = "General"  ;
const std::string pname_symmetric = "Symmetric";
const std::string pname_hermitian = "Hermitian";
/*-------------------------------------------------*/
const std::string& Property::name() const
{
	if(type() == prop_t::NONE     ) return pname_none     ;
	if(type() == prop_t::GENERAL  ) return pname_general  ;
	if(type() == prop_t::SYMMETRIC) return pname_symmetric;
	if(type() == prop_t::HERMITIAN) return pname_hermitian;

	throw Exception("Unknown property");
}
/*-------------------------------------------------*/
bool Property::is_valid() const
{
	return (type() != prop_t::NONE);
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
bool Property::is_lower() const
{
	return (is_symmetric() || is_hermitian());
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


