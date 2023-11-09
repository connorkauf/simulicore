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

#ifndef CLA3P_DNS_CXMATRIX_HPP_
#define CLA3P_DNS_CXMATRIX_HPP_

#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

template <typename T_Scalar> class CxVector;
template <typename T_Scalar> class RxMatrix;

/**
 * @nosubgrouping 
 * @brief The dense complex matrix class.
 */
template <typename T_Scalar>
class CxMatrix : public XxMatrix<T_Scalar,CxMatrix<T_Scalar>> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_RMatrix = typename TypeTraits<CxMatrix<T_Scalar>>::real_type;

	public:

		// no copy
		CxMatrix(const CxMatrix<T_Scalar>&) = delete;
		CxMatrix<T_Scalar>& operator=(const CxMatrix<T_Scalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix()
		 */
		explicit CxMatrix();

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
		 */
		explicit CxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(XxMatrix&& other)
		 */
		CxMatrix(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::~XxMatrix()
		 */
		~CxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(XxMatrix&& other)
		 */
		CxMatrix<T_Scalar>& operator=(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(T_Scalar val)
		 */
		void operator=(T_Scalar val);

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Gets a copy of the real part of the matrix.
		 *
		 * @return A copy of the real part of the matrix.
		 */
		T_RMatrix real() const;

		/**
		 * @brief Gets a copy of the imaginary part of the matrix.
		 *
		 * @return A copy of the imaginary part of the matrix.
		 */
		T_RMatrix imag() const;

		/**
		 * @brief Conjugate-transposes a general matrix.
		 * @return The consjugate-transposed copy of the matrix.
		 */
		CxMatrix<T_Scalar> ctranspose() const;

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
template<typename T_Scalar>
class TypeTraits<dns::CxMatrix<T_Scalar>> {
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
	public:
		static std::string type_name();
		using real_type = dns::RxMatrix<T_RScalar>;
		using vector_type = dns::CxVector<T_Scalar>;
};
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXMATRIX_HPP_
