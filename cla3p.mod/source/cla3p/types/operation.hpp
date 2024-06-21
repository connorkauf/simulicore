/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CLA3P_OPERATION_HPP_
#define CLA3P_OPERATION_HPP_

/** 
 * @file
 */

#include <ostream>
#include <string>

#include "cla3p/types/enums.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @brief The operation class.
 *
 * Utility class for easy handling of the op_t flag.
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
		 * Constructs an operation with type `otype`.
		 */
		explicit Operation(op_t otype);

		/**
		 * @brief Destructs the operation.
		 */
		~Operation();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs an operation with the copy of the contents of `other`.
		 */
		Operation(const Operation& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of `(*this)` with a copy of the contents of `other`.
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
 * @ingroup cla3p_module_index_stream_operators
 * @brief Writes to os the type of op.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATION_HPP_
