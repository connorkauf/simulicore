// this file inc
#include "types.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Property::Property()
	: m_type(prop_t::NONE)
{
}
/*-------------------------------------------------*/
Property::Property(prop_t ptype)
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

	throw Exception();
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
} // namespace cla3p
/*-------------------------------------------------*/

