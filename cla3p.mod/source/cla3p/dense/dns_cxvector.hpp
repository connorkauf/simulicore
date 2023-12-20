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

#ifndef CLA3P_DNS_CXVECTOR_HPP_
#define CLA3P_DNS_CXVECTOR_HPP_

#include "cla3p/types/literals.hpp"
#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

template <typename T_Scalar> class CxMatrix;
template <typename T_Scalar> class RxVector;

/**
 * @nosubgrouping 
 * @brief The dense complex vector class.
 */
template <typename T_Scalar>
class CxVector : public XxVector<T_Scalar,CxVector<T_Scalar>> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_RVector = typename TypeTraits<CxVector<T_Scalar>>::real_type;

	public:

		// no copy
		CxVector(const CxVector<T_Scalar>&) = delete;
		CxVector<T_Scalar>& operator=(const CxVector<T_Scalar>&) = delete;

		const CxVector<T_Scalar>& self() const override;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector()
		 */
		explicit CxVector();

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(uint_t n)
		 */
		explicit CxVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(XxVector&& other)
		 */
		CxVector(CxVector<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::~XxVector()
		 */
		~CxVector();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(XxVector&& other)
		 */
		CxVector<T_Scalar>& operator=(CxVector<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(T_Scalar val)
		 */
		void operator=(T_Scalar val);

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Gets a copy of the real part of the vector.
		 *
		 * @return A copy of the real part of the vector.
		 */
		T_RVector real() const;

		/**
		 * @brief Gets a copy of the imaginary part of the vector.
		 *
		 * @return A copy of the imaginary part of the vector.
		 */
		T_RVector imag() const;

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p { 
template<typename T_Scalar>
class TypeTraits<dns::CxVector<T_Scalar>> {
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
	public:
		static constexpr bool is_real() { return false; }
		static constexpr bool is_complex() { return true; }
		static std::string type_name() { return msg::DenseVector(); };
		using real_type = dns::RxVector<T_RScalar>;
		using matrix_type = dns::CxMatrix<T_Scalar>;
};
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXVECTOR_HPP_
