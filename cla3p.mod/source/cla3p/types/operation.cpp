// this file inc
#include "cla3p/types/operation.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"
#include "cla3p/error/error.hpp"

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
std::string Operation::name() const
{
	if(type() == op_t::N) return msg::NoOperation();
	if(type() == op_t::T) return msg::TransposeOperation();
	if(type() == op_t::C) return msg::ConjugateTransposeOperation();

	throw err::Exception("Unknown operation");
	return msg::NoOperation();
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
