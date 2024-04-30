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

#ifndef CLA3P_CSC_CXMATRIX_HPP_
#define CLA3P_CSC_CXMATRIX_HPP_

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/sparse/csc_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace dns { template <typename T_Scalar> class CxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar> class RxMatrix; }

/*-------------------------------------------------*/
namespace csc {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The sparse complex matrix class (compressed sparse column format).
 */
template <typename T_Int, typename T_Scalar>
class CxMatrix : public XxMatrix<T_Int,T_Scalar,CxMatrix<T_Int,T_Scalar>> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_RMatrix = typename TypeTraits<CxMatrix<T_Int,T_Scalar>>::real_type;

	public:

		const CxMatrix<T_Int,T_Scalar>& self() const override;
		CxMatrix<T_Int,T_Scalar>& self() override;

		// virtuals to matrix
		template <typename T_Virtual>
		CxMatrix(const VirtualEntity<CxMatrix<T_Int,T_Scalar>,T_Virtual>& v) { v.addToTarget(T_Scalar(0), *this); }
		template <typename T_Virtual>
		CxMatrix<T_Int,T_Scalar>& operator=(const VirtualEntity<CxMatrix<T_Int,T_Scalar>,T_Virtual>& v) { v.addToTarget(T_Scalar(0), *this); return *this; }

		/* DO NOT DOCUMENT
		 * @copydoc cla3p::csc::RxMatrix::RxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
		 */
		explicit CxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr = Property::General());

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::csc::RxMatrix::RxMatrix()
		 */
		explicit CxMatrix();

		/**
		 * @copydoc cla3p::csc::RxMatrix::RxMatrix(const RxMatrix& other)
		 */
		CxMatrix(const CxMatrix<T_Int,T_Scalar>& other) = default;

		/**
		 * @copydoc cla3p::csc::RxMatrix::RxMatrix(RxMatrix&& other)
		 */
		CxMatrix(CxMatrix<T_Int,T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::csc::RxMatrix::~RxMatrix()
		 */
		~CxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::csc::RxMatrix::operator=(const RxMatrix& other)
		 */
		CxMatrix<T_Int,T_Scalar>& operator=(const CxMatrix<T_Int,T_Scalar>& other) = default;

		/**
		 * @copydoc cla3p::csc::RxMatrix::operator=(RxMatrix&& other)
		 */
		CxMatrix<T_Int,T_Scalar>& operator=(CxMatrix<T_Int,T_Scalar>&& other) = default;

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
} // namespace csc
/*-------------------------------------------------*/

template<typename T_Int, typename T_Scalar>
class TypeTraits<csc::CxMatrix<T_Int,T_Scalar>> {
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
	public:
		static constexpr bool is_real() { return false; }
		static constexpr bool is_complex() { return true; }
		static std::string type_name() { return msg::SparseCscMatrix(); }
		using real_type = csc::RxMatrix<T_Int,T_RScalar>;
		using dns_type = dns::CxMatrix<T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_CSC_CXMATRIX_HPP_
