#ifndef CLA3P_ERROR_HPP_
#define CLA3P_ERROR_HPP_

/** 
 * @file
 * Basic error control features.
 */

#include <string>
#include <exception>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup exceptions
 * @brief Basic cla3p exception class.
 */
class Exception : public std::exception {

	public:
		/** 
		 * @brief The default constructor.
		 *
		 * Constructs an exception with the given message.
		 */
		Exception(const std::string& msg = "Untitled");

		/** 
		 * @brief Destroys the exception.
		 */
		~Exception() throw();

		/** 
		 * @brief Returns the explanatory string.
		 */
		const char *what() const throw();

	private:
		std::string m_msg;
};

/**
 * @ingroup exceptions
 * @brief Consistency cla3p exception class.
 */
class NoConsistency : public Exception {
	public:
		/** 
		 * @copydoc Exception::Exception()
		 */
		NoConsistency(const std::string& msg = "Untitled");

		/** 
		 * @copydoc Exception::~Exception()
		 */
		~NoConsistency() throw();
};

/**
 * @ingroup exceptions
 * @brief Invalid operation cla3p exception class.
 */
class InvalidOp : public Exception {
	public:
		/** 
		 * @copydoc Exception::Exception()
		 */
		InvalidOp(const std::string& msg = "Untitled");

		/** 
		 * @copydoc Exception::~Exception()
		 */
		~InvalidOp() throw();
};

/**
 * @ingroup exceptions
 * @brief Numerical overflow cla3p exception class.
 */
class Overflow : public Exception {
	public:
		/** 
		 * @copydoc Exception::Exception()
		 */
		Overflow(const std::string& msg = "Untitled");

		/** 
		 * @copydoc Exception::~Exception()
		 */
		~Overflow() throw();
};

/**
 * @ingroup exceptions
 * @brief Memory cla3p exception class.
 */
class OutOfMemory : public Exception {
	public:
		/** 
		 * @copydoc Exception::Exception()
		 */
		OutOfMemory(const std::string& msg = "Untitled");

		/** 
		 * @copydoc Exception::~Exception()
		 */
		~OutOfMemory() throw();
};

/**
 * @ingroup exceptions
 * @brief Out-of-bounds cla3p exception class.
 */
class OutOfBounds : public Exception {
	public:
		/** 
		 * @copydoc Exception::Exception()
		 */
		OutOfBounds(const std::string& msg = "Untitled");

		/** 
		 * @copydoc Exception::~Exception()
		 */
		~OutOfBounds() throw();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_HPP_
