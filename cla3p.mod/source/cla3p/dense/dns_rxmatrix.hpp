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

#ifndef CLA3P_DNS_RXMATRIX_HPP_
#define CLA3P_DNS_RXMATRIX_HPP_

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace dns { template <typename T_Scalar> class RxVector; }
namespace csc { template <typename T_Int, typename T_Scalar> class RxMatrix; }

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense real matrix class.
 */
template <typename T_Scalar>
class RxMatrix : public XxMatrix<T_Scalar,RxMatrix<T_Scalar>> {

	public:

		const RxMatrix<T_Scalar>& self() const override;
		RxMatrix<T_Scalar>& self() override;

		// virtuals to matrix
		template <typename T_Virtual>
		RxMatrix(const VirtualEntity<RxMatrix<T_Scalar>,T_Virtual>& v) { v.addToTarget(T_Scalar(0), *this); }
		template <typename T_Virtual>
		RxMatrix<T_Scalar>& operator=(const VirtualEntity<RxMatrix<T_Scalar>,T_Virtual>& v) { v.addToTarget(T_Scalar(0), *this); return *this; }

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
		 * Constructs a general (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 */
		explicit RxMatrix(uint_t nr, uint_t nc, const Property& pr = Property::General());

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a matrix with a copy of the contents of `other`, `other` is destroyed.
		 */
		RxMatrix(const RxMatrix<T_Scalar>& other) = default;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of `other`, `other` is destroyed.
		 */
		RxMatrix(RxMatrix<T_Scalar>&& other) = default;

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
		 * If `(*this)` is empty, constructs a matrix with a copy of the contents of `other`, `other` is unchanged.@n
		 * If `(*this)` is not empty, performs a deep copy of the data of `other` to `(*this)`. The size and property of `(*this)` should match those of `other`.
		 */
		RxMatrix<T_Scalar>& operator=(const RxMatrix<T_Scalar>& other) = default;

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 */
		RxMatrix<T_Scalar>& operator=(RxMatrix<T_Scalar>&& other) = default;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of `(*this)` to a single value.@n
		 * Imaginary part of diagonal is set to zero for Hermitian cases.@n
		 * Diagonal is set to zero for Skew cases.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/

template<typename T_Scalar>
class TypeTraits<dns::RxMatrix<T_Scalar>> {
	public:
		static constexpr bool is_real() { return true; }
		static constexpr bool is_complex() { return false; }
		static std::string type_name() { return msg::DenseMatrix(); }
		using real_type = dns::RxMatrix<T_Scalar>;
		using vector_type = dns::RxVector<T_Scalar>;
		using csc_type = csc::RxMatrix<int_t,T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RXMATRIX_HPP_
