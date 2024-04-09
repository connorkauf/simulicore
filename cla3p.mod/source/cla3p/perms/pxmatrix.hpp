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

#ifndef CLA3P_PXMATRIX_HPP_
#define CLA3P_PXMATRIX_HPP_

/** 
 * @file
 */

#include <string>

#include "cla3p/types/literals.hpp"
#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The permutation matrix object.
 *
 * Permutation matrices are represented by an array of (unsigned) integers. @n
 * Their purpose is to rearrange indices using a predefined mapping. @n
 * So an n-sized PermMatrix is a 1D entity and its individual values lie in [0, n-1] (0-based indexing).
 */
template <typename T_Int>
class PxMatrix : public dns::XiVector<T_Int,PxMatrix<T_Int>> {

	public:

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty permutation matrix.
		 */
		explicit PxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs an n-sized permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 */
		explicit PxMatrix(uint_t n);

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a permutation matrix with a copy of the contents of `other`, `other` is unchanged.
		 */
		PxMatrix(const PxMatrix<T_Int>& other) = default;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a permutation matrix with the contents of `other`, `other` is destroyed.
		 */
		PxMatrix(PxMatrix<T_Int>&& other) = default;

		/**
		 * @brief Destroys the permutation matrix.
		 */
		~PxMatrix();

		/** @} */

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The copy assignment operator.
		 *
		 * If `(*this)` is empty, constructs a permutation matrix with a copy of the contents of `other`, `other` is unchanged.@n
		 * If `(*this)` is not empty, performs a deep copy of the data of `other` to `(*this)`. The size of `(*this)` should match the size of `other`.
		 */
		PxMatrix& operator=(const PxMatrix<T_Int>& other) = default;

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of `other`, `other` is destroyed.
		 */
		PxMatrix<T_Int>& operator=(PxMatrix<T_Int>&& other) = default;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of `(*this)` to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Int val);

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief The inverse permutation matrix.
		 * @return The inverse (transpose) of the permutation matrix.
		 */
		PxMatrix<T_Int> inverse() const;

		/**
		 * @brief Permutes a permutation matrix.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permutated permutation matrix (P * (*this)).
		 */
		PxMatrix<T_Int> permuteLeft(const PxMatrix<T_Int>& P) const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates an identity permutation matrix
		 *
		 * Creates an n-sized permutation matrix with P(i) = i.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix<T_Int> identity(uint_t n);

		/**
		 * @brief Creates a random permutation matrix
		 *
		 * Creates an n-sized permutation matrix with randomly rearranged indexes.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix<T_Int> random(uint_t n);

		/** @} */
};

/*-------------------------------------------------*/
} // namespace prm
/*-------------------------------------------------*/

template<typename T_Int>
class TypeTraits<prm::PxMatrix<T_Int>> {
	public:
		static std::string type_name() { return msg::PermutationMatrix(); };
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PXMATRIX_HPP_
