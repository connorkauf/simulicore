// this file inc
#include "error.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Exception::Exception(const std::string& msg)
{
	m_msg = msg;
}
/*-------------------------------------------------*/
Exception::~Exception() throw()
{
}
/*-------------------------------------------------*/
const char* Exception::what() const throw()
{
	return m_msg.c_str();
}
/*-------------------------------------------------*/
MemoryException::MemoryException(const std::string& msg)
	: Exception("Memory error: " + msg)
{
}
/*-------------------------------------------------*/
MemoryException::~MemoryException() throw()
{
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
