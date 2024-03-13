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

#ifndef CLA3P_DNS_LSOLVER_BASE_HPP_
#define CLA3P_DNS_LSOLVER_BASE_HPP_

/**
 * @file
 */

#include <vector>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The abstract linear solver base for dense matrices.
 */
template <typename T_Matrix>
class LSolverBase {

	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LSolverBase(const LSolverBase&) = delete;
		LSolverBase& operator=(const LSolverBase&) = delete;

		LSolverBase();
		~LSolverBase();

		/**
		 * @brief Allocates internal buffers.
		 */
		virtual void reserve(uint_t n);

		/**
		 * @brief Clears the solver internal data.
		 */
		virtual void clear();

		/**
		 * @brief Performs matrix decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 */
		virtual void decompose(const T_Matrix& mat) = 0;

		/**
		 * @brief Performs in-place matrix decomposition.
		 * @param[in] mat The matrix to be decomposed, destroyed after the operation.
		 */
		virtual void idecompose(T_Matrix& mat) = 0;

		/**
		 * @brief Performs in-place matrix solution.
		 * @param[in] rhs The right hand side matrix, overwritten with the solution.
		 */
		virtual void solve(T_Matrix& rhs) const = 0;

		/**
		 * @brief Performs in-place vector solution.
		 * @param[in] rhs The right hand side vector, overwritten with the solution.
		 */
		virtual void solve(T_Vector& rhs) const = 0;

	protected:
		int_t& info();
		const int_t& info() const;
		T_Matrix& factor();
		const T_Matrix& factor() const;
		std::vector<int_t>& ipiv1();
		const std::vector<int_t>& ipiv1() const;
		std::vector<int_t>& jpiv1();
		const std::vector<int_t>& jpiv1() const;

		void reserveBuffer(uint_t n);
		void reserveIpiv(uint_t n);
		void reserveJpiv(uint_t n);
		void absorbInput(const T_Matrix& mat);
		void clearAll();

	private:
		int_t m_info;
		T_Matrix m_factor;
		T_Matrix m_buffer;
		std::vector<int_t> m_ipiv1;
		std::vector<int_t> m_jpiv1;

		T_Matrix& buffer();
		const T_Matrix& buffer() const;

		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_LSOLVER_BASE_HPP_
