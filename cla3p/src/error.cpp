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
NoConsistency::NoConsistency(const std::string& msg)
	: Exception("Consistency error: " + msg)
{
}
/*-------------------------------------------------*/
NoConsistency::~NoConsistency() throw()
{
}
/*-------------------------------------------------*/
OutOfMemory::OutOfMemory(const std::string& msg)
	: Exception("Memory error: " + msg)
{
}
/*-------------------------------------------------*/
OutOfMemory::~OutOfMemory() throw()
{
}
/*-------------------------------------------------*/
OutOfBounds::OutOfBounds(const std::string& msg)
	: Exception("Out of bounds error: " + msg)
{
}
/*-------------------------------------------------*/
OutOfBounds::~OutOfBounds() throw()
{
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
