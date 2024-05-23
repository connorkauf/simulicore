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

#ifndef CLA3P_LAPACK_LDLT_HPP_
#define CLA3P_LAPACK_LDLT_HPP_

/**
 * @file
 */

#include "cla3p/linsol/lapack_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The indefinite Cholesky (LDL') linear solver for dense matrices.
 */
template <typename T_Matrix>
class LapackLDLt : public LapackBase<T_Matrix> {

	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LapackLDLt(const LapackLDLt&) = delete;
		LapackLDLt& operator=(const LapackLDLt&) = delete;

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt()
		 */
		LapackLDLt() : LapackBase<T_Matrix>(decomp_t::LDLT) {}

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt(uint_t n)
		 */
		LapackLDLt(uint_t n) : LapackBase<T_Matrix>(decomp_t::LDLT, n) {}

		/**
		 * @copydoc cla3p::LapackLLt::~LapackLLt()
		 */
		~LapackLDLt() = default;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_LDLT_HPP_
