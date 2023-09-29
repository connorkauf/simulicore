#ifndef CLA3P_OPERATION_HPP_
#define CLA3P_OPERATION_HPP_

/** 
 * @file
 * Operation configuration
 */

#include <ostream>
#include <string>

#include "cla3p/types/enums.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes
 * @brief The operation class.
 */
class Operation {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty operation.
		 */
		Operation();

		/**
		 * @brief The member constructor.
		 *
		 * Constructs an operation with type otype.
		 */
		explicit Operation(op_t otype);

		/**
		 * @brief Destructs the operation.
		 */
		~Operation();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs an operation with the copy of the contents of other.
		 */
		Operation(const Operation& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of operation with a copy of the contents of other.
		 */
		Operation& operator=(const Operation& other);

		/**
		 * @brief The operation type.
		 */
		op_t type() const;

		/**
		 * @brief The operation type as a char.
		 */
		char ctype() const;

		/**
		 * @brief The operation name.
		 */
		std::string name() const;

		/**
		 * @brief Checks weather the operation is (conjugate) transpose
		 */
		bool isTranspose() const;

	private:
		op_t m_type;
};

/*-------------------------------------------------*/

inline Operation noOp()
{
	return Operation(op_t::N);
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the type of op.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATION_HPP_
