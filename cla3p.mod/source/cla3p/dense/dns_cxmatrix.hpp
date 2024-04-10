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

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/generic/type_traits.hpp"
#include "cla3p/dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace dns { template <typename T_Scalar> class CxVector; }
namespace dns { template <typename T_Scalar> class RxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar> class CxMatrix; }

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

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

		const CxMatrix<T_Scalar>& self() const override;
		CxMatrix<T_Scalar>& self() override;

		// virtuals to matrix
		CxMatrix(const VirtualMatrix<CxMatrix<T_Scalar>>&);
		CxMatrix<T_Scalar>& operator=(const VirtualMatrix<CxMatrix<T_Scalar>>&);

		CxMatrix(const VirtualProdMm<CxMatrix<T_Scalar>>&);
		CxMatrix<T_Scalar>& operator=(const VirtualProdMm<CxMatrix<T_Scalar>>&);

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RxMatrix::RxMatrix()
		 */
		explicit CxMatrix();

		/**
		 * @copydoc cla3p::dns::RxMatrix::RxMatrix(uint_t nr, uint_t nc, const Property& pr)
		 */
		explicit CxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::dns::RxMatrix::RxMatrix(const RxMatrix& other)
		 */
		CxMatrix(const CxMatrix<T_Scalar>& other) = default;

		/**
		 * @copydoc cla3p::dns::RxMatrix::RxMatrix(RxMatrix&& other)
		 */
		CxMatrix(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::RxMatrix::~RxMatrix()
		 */
		~CxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RxMatrix::operator=(RxMatrix&& other)
		 */
		CxMatrix<T_Scalar>& operator=(const CxMatrix<T_Scalar>& other) = default;

		/**
		 * @copydoc cla3p::dns::RxMatrix::operator=(RxMatrix&& other)
		 */
		CxMatrix<T_Scalar>& operator=(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::RxMatrix::operator=(T_Scalar val)
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

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/

template<typename T_Scalar>
class TypeTraits<dns::CxMatrix<T_Scalar>> {
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
	public:
		static constexpr bool is_real() { return false; }
		static constexpr bool is_complex() { return true; }
		static std::string type_name() { return msg::DenseMatrix(); }
		using real_type = dns::RxMatrix<T_RScalar>;
		using vector_type = dns::CxVector<T_Scalar>;
		using csc_type = csc::CxMatrix<int_t,T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXMATRIX_HPP_
