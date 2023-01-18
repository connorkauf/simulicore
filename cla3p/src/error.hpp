#ifndef CLA3P_ERROR_HPP_
#define CLA3P_ERROR_HPP_

#include <string>
#include <exception>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

class Exception : public std::exception {

	public:
		Exception(const std::string& msg = "Untitled");
		~Exception() throw();
		const char *what() const throw();

	private:
		std::string m_msg;
};

class MemoryException : public Exception {
	public:
		MemoryException(const std::string& msg = "Untitled");
		~MemoryException() throw();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_HPP_
