// this file inc
#include "operation.hpp"

// system

// 3rd

// cla3p
#include "../support/error.hpp"

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
char Operation::ctype() const
{
	return static_cast<char>(type());
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
bool Operation::isTranspose() const
{
	return (type() != op_t::N);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op)
{
	os << op.name();
	return os;
}
/*-------------------------------------------------*/
