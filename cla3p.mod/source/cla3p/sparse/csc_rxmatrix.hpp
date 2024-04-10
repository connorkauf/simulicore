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

#ifndef CLA3P_CSC_RXMATRIX_HPP_
#define CLA3P_CSC_RXMATRIX_HPP_

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/sparse/csc_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace dns { template <typename T_Scalar> class RxMatrix; }

/*-------------------------------------------------*/
namespace csc {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The sparse real matrix class (compressed sparse column format).
 */
template <typename T_Int, typename T_Scalar>
class RxMatrix : public XxMatrix<T_Int,T_Scalar,RxMatrix<T_Int,T_Scalar>> {

	public:

		const RxMatrix<T_Int,T_Scalar>& self() const override;
		RxMatrix<T_Int,T_Scalar>& self() override;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty matrix.
		 */
		explicit RxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a (nr x nc) matrix with nz non-zero uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] nz The number of matrix non zeros.
		 * @param[in] pr The matrix property.
		 */
		explicit RxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a matrix with a copy of the contents of `other`, `other` is destroyed.
		 */
		RxMatrix(const RxMatrix<T_Int,T_Scalar>& other) = default;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of `other`, `other` is destroyed.
		 */
		RxMatrix(RxMatrix<T_Int,T_Scalar>&& other) = default;

		/**
		 * @brief Destroys the matrix.
		 *
		 * Destroy the matrix and free content memory if needed.
		 */
		~RxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 * If `(*this)` is empty, constructs a matrix with a copy of the contents of `other`, `other` is unchanged.@n
		 * If `(*this)` is not empty, performs a deep copy of the data of `other` to `(*this)`. The sizes, non-zeros and property of `(*this)` should match those of `other`.
		 */
		RxMatrix<T_Int,T_Scalar>& operator=(const RxMatrix<T_Int,T_Scalar>& other) = default;

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 */
		RxMatrix<T_Int,T_Scalar>& operator=(RxMatrix<T_Int,T_Scalar>&& other) = default;

		/** @} */

};

/*-------------------------------------------------*/
} // namespace csc
/*-------------------------------------------------*/

template<typename T_Int, typename T_Scalar>
class TypeTraits<csc::RxMatrix<T_Int,T_Scalar>> {
	public:
		static constexpr bool is_real() { return true; }
		static constexpr bool is_complex() { return false; }
		static std::string type_name() { return msg::SparseCscMatrix(); }
		using real_type = csc::RxMatrix<T_Int,T_Scalar>;
		using dns_type = dns::RxMatrix<T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_CSC_RXMATRIX_HPP_
