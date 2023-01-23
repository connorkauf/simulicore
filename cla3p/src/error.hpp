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
 * @brief Consistency cla3p exception class
 */
class NoConsistency : public Exception {
	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		NoConsistency(const std::string& msg = "Untitled");
		~NoConsistency() throw();
};

/**
 * @brief Memory cla3p exception class
 */
class OutOfMemory : public Exception {
	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		OutOfMemory(const std::string& msg = "Untitled");
		~OutOfMemory() throw();
};

/**
 * @brief Consistency cla3p exception class
 */
class OutOfBounds : public Exception {
	public:
		/** 
		 * @brief Constructor
		 * @param[in] msg The message to display on throw
		 */
		OutOfBounds(const std::string& msg = "Untitled");
		~OutOfBounds() throw();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_HPP_
