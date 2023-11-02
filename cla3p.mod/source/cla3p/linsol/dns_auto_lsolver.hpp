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

#ifndef CLA3P_DNS_AUTO_LSOLVER_HPP_
#define CLA3P_DNS_AUTO_LSOLVER_HPP_

/**
 * @file
 * Dense linear system solver with automatic method detection.
 */

#include "cla3p/linsol/dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup module_index_linsol_dense
 * @nosubgrouping
 * @brief The linear solver for dense matrices with automatic method detection.
 */
template <typename T_Matrix>
class LSolverAuto : public LSolverBase<T_Matrix> {

	using T_Vector = typename BasicTypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LSolverAuto(const LSolverAuto&) = delete;
		LSolverAuto& operator=(const LSolverAuto&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverAuto();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n<sup>2</sup> buffered size.
		 */
		LSolverAuto(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverAuto();

		/**
		 * @copydoc cla3p::dns::LSolverBase::reserve(uint_t n)
		 */
		void reserve(uint_t n) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::decompose()
		 */
		void decompose(const T_Matrix& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::idecompose()
		 */
		void idecompose(T_Matrix& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::solve(T_Matrix& rhs) const
		 */
		void solve(T_Matrix& rhs) const override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::solve(T_Vector& rhs) const
		 */
		void solve(T_Vector& rhs) const override;

	private:
		void fdecompose();
};

template <typename T_Matrix, typename T_Rhs>
void default_linear_solver(const T_Matrix& mat, T_Rhs& rhs)
{
	LSolverAuto<T_Matrix> solver;
	solver.decompose(mat);
	solver.solve(rhs);
}

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_AUTO_LSOLVER_HPP_
