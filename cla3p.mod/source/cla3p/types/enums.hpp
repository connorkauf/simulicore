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

#ifndef CLA3P_ENUMS_HPP_
#define CLA3P_ENUMS_HPP_

/** 
 * @file
 */

#include <ostream>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_datatypes
 * @enum prop_t
 * @brief The property type.
 *
 * List of matrix algebraic properties.@n
 * Used to construct a Property class that characterizes a matrix in order to take advantage of its properties.
 */
enum class prop_t {
	Undefined   = 0, /**< No property */
	General        , /**< General matrix */
	Symmetric      , /**< Symmetric matrix */
	Hermitian      , /**< Hermitian matrix */
	Triangular     , /**< Triangular/trapezoidal matrix */
	Skew             /**< Skew matrix */
};

/**
 * @ingroup module_index_datatypes
 * @enum uplo_t
 * @brief The fill type.
 *
 * List of matrix structural properties.@n
 * Used to construct a Property class to determine where the values of a matrix are stored.
 */
enum class uplo_t : char {
	Full  = 'F', /**< Both matrix parts are filled */
	Upper = 'U', /**< The upper matrix part is filled */
	Lower = 'L'  /**< The lower matrix part is filled */
};

/**
 * @ingroup module_index_datatypes
 * @enum op_t
 * @brief The operation type.
 *
 * List of operations (implicitly) applied on a matrix.@n
 * For efficiency purposes in matrix operations, this flag is used to designate a virtual operation that is not explicitly applied to the matrix.@n
 * For example in order for the operation Y = A<sup>T</sup> * X to be calculated we do not need to explicitly calculate A<sup>T</sup>.@n
 * Instead we can use the mult() function with the appropriate op_t value for the matrix A:
 @code
 Y = cla3p::ops::mult(1, cla3p::op_t::T, A, X);
 @endcode
 to calculate the matrix product much more efficiently.
 */
enum class op_t : char {
	N = 'N', /**< No operation: op(A) = A */
	T = 'T', /**< Transpose operation: op(A) = A<sup>T</sup> */
	C = 'C'  /**< Conjugate transpose operation: op(A) = A<sup>H</sup> */
};

enum class side_t : char {
	Left  = 'L',
	Right = 'R' 
};

enum class diag_t : char {
	NonUnit = 'N',
	Unit    = 'U' 
};

/**
 * @ingroup module_index_datatypes
 * @enum dup_t
 * @brief The duplicated policy.
 *
 * Sets the policy for duplicated entries on sparse matrices.
 */
enum class dup_t {
	Sum  = 0, /**< Adds duplicated entries */
	Prod    , /**< Multiplies duplicated entries */
	Amax    , /**< Keeps absolute maximum entry */
	Amin      /**< Keeps absolute minimum entry */
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the type of prop.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::prop_t& prop);

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the type of uplo.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::uplo_t& uplo);

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the type of op.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::op_t& op);

#endif // CLA3P_ENUMS_HPP_
