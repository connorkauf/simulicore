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

#ifndef CLA3P_COO_RXMATRIX_HPP_
#define CLA3P_COO_RXMATRIX_HPP_

/**
 * @file
 */

#include "cla3p/types/literals.hpp"
#include "cla3p/sparse/coo_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace csc { template <typename T_Int, typename T_Scalar> class RxMatrix; }

/*-------------------------------------------------*/
namespace coo {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The sparse real matrix class (coordinate format).
 */
template <typename T_Int, typename T_Scalar>
class RxMatrix : public XxMatrix<T_Int,T_Scalar,RxMatrix<T_Int,T_Scalar>> {

	public:

		// no copy
		RxMatrix(const RxMatrix<T_Int,T_Scalar>&) = delete;
		RxMatrix<T_Int,T_Scalar>& operator=(const RxMatrix<T_Int,T_Scalar>&) = delete;

		const RxMatrix<T_Int,T_Scalar>& self() const override;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::coo::XxMatrix::XxMatrix()
		 */
		explicit RxMatrix();

		/**
		 * @copydoc cla3p::coo::XxMatrix::XxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
		 */
		explicit RxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::coo::XxMatrix::XxMatrix(XxMatrix&& other)
		 */
		RxMatrix(RxMatrix<T_Int,T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::coo::XxMatrix::~XxMatrix()
		 */
		~RxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::coo::XxMatrix::operator=(XxMatrix&& other)
		 */
		RxMatrix<T_Int,T_Scalar>& operator=(RxMatrix<T_Int,T_Scalar>&& other) = default;

		/** @} */

};

/*-------------------------------------------------*/
} // namespace coo
/*-------------------------------------------------*/

template<typename T_Int, typename T_Scalar>
class TypeTraits<coo::RxMatrix<T_Int,T_Scalar>> {
	public:
		static constexpr bool is_real() { return true; }
		static constexpr bool is_complex() { return false; }
		static std::string type_name() { return msg::SparseCooMatrix(); }
		using real_type = coo::RxMatrix<T_Int,T_Scalar>;
		using csc_type = csc::RxMatrix<T_Int,T_Scalar>;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_COO_RXMATRIX_HPP_
