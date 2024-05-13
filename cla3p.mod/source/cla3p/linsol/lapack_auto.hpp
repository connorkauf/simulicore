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

#ifndef CLA3P_LAPACK_AUTO_HPP_
#define CLA3P_LAPACK_AUTO_HPP_

/**
 * @file
 */

#include "cla3p/linsol/lapack_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The linear solver for dense matrices with automatic method detection.
 */
template <typename T_Matrix>
class LapackAuto : public LapackBase<T_Matrix> {

	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LapackAuto(const LapackAuto&) = delete;
		LapackAuto& operator=(const LapackAuto&) = delete;

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt()
		 */
		LapackAuto();

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt(uint_t n)
		 */
		LapackAuto(uint_t n);

		/**
		 * @copydoc cla3p::LapackLLt::~LapackLLt()
		 */
		~LapackAuto();

	private:
		void decomposeFactor() override;
		void solveForRhs(T_Matrix& rhs) const override;
};

template <typename T_Matrix, typename T_Rhs>
void default_linear_solver(const T_Matrix& mat, T_Rhs& rhs)
{
	LapackAuto<T_Matrix> solver;
	solver.decompose(mat);
	solver.solve(rhs);
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_AUTO_HPP_
