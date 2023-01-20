#ifndef CLA3P_ERROR_HPP_
#define CLA3P_ERROR_HPP_

/** @file error.hpp
 * Basic error control features
 */

#include <string>
#include <exception>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @brief Basic cla3p exception class
 */
class Exception : public std::exception {

	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		Exception(const std::string& msg = "Untitled");
		~Exception() throw();
		const char *what() const throw();

	private:
		std::string m_msg;
};

/**
 * @brief Memory cla3p exception class
 */
class MemoryException : public Exception {
	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		MemoryException(const std::string& msg = "Untitled");
		~MemoryException() throw();
};

/**
 * @brief Consistency cla3p exception class
 */
class ConsistencyException : public Exception {
	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		ConsistencyException(const std::string& msg = "Untitled");
		~ConsistencyException() throw();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_HPP_
