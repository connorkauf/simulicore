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

#ifndef CLA3P_DNS_RXVECTOR_HPP_
#define CLA3P_DNS_RXVECTOR_HPP_

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace dns { template <typename T_Scalar> class RxMatrix; }

template <typename T_Vector> class VirtualVector;
template <typename T_Vector> class VirtualProdMv;

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense real vector class.
 */
template <typename T_Scalar>
class RxVector : public XxVector<T_Scalar,RxVector<T_Scalar>> {

	public:

		const RxVector<T_Scalar>& self() const override;
		RxVector<T_Scalar>& self() override;

		// virtuals to vector
		RxVector(const VirtualVector<RxVector<T_Scalar>>&);
		RxVector<T_Scalar>& operator=(const VirtualVector<RxVector<T_Scalar>>&);

		RxVector(const VirtualProdMv<RxVector<T_Scalar>>&);
		RxVector<T_Scalar>& operator=(const VirtualProdMv<RxVector<T_Scalar>>&);

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty vector.
		 */
		explicit RxVector();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 */
		explicit RxVector(uint_t n);

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a vector with the contents of `other`, `other` is unchanged.
		 */
		RxVector(const RxVector<T_Scalar>& other) = default;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a vector with the contents of `other`, `other` is destroyed.
		 */
		RxVector(RxVector<T_Scalar>&& other) = default;

		/**
		 * @brief Destroys the vector.
		 *
		 * Destroy the vector and free content memory if needed.
		 */
		~RxVector();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The copy assignment operator.
		 *
		 * If `(*this)` is empty, constructs a vector with a copy of the contents of `other`, `other` is unchanged.@n
		 * If `(*this)` is not empty, performs a deep copy of the data of `other` to `(*this)`. The size of `(*this)` should match the size of `other`.
		 */
		RxVector<T_Scalar>& operator=(const RxVector<T_Scalar>& other) = default;

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 */
		RxVector<T_Scalar>& operator=(RxVector<T_Scalar>&& other) = default;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of `(*this)` to a single value.
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
class TypeTraits<dns::RxVector<T_Scalar>> {
	public:
		static constexpr bool is_real() { return true; }
		static constexpr bool is_complex() { return false; }
		static std::string type_name() { return msg::DenseVector(); }
		using real_type = dns::RxVector<T_Scalar>;
		using matrix_type = dns::RxMatrix<T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RXVECTOR_HPP_
