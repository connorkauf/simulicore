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

#ifndef CLA3P_LAPACK_BASE_HPP_
#define CLA3P_LAPACK_BASE_HPP_

/**
 * @file
 */

#include <string>
#include <vector>

#include "cla3p/types.hpp"
#include "cla3p/support/heap_buffer.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The abstract linear solver base for dense matrices.
 */
template <typename T_Matrix>
class LapackBase {

	using T_Scalar = typename T_Matrix::value_type;
	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	protected:
		LapackBase(decomp_t decompType);
		LapackBase(decomp_t decompType, uint_t n);
		~LapackBase();

	public:
		std::string name() const;

		/**
		 * @brief Allocates internal buffers.
		 * @param[in] n The maximum dimension for the buffers.
		 */
		void reserve(uint_t n);
		
		/**
		 * @brief Clears the solver internal data.
		 *
		 * Clears the solver internal data and resets all settings
		 */
		void clear();
		
		/**
		 * @brief Performs matrix decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 */
		void decompose(const T_Matrix& mat);
		
		/**
		 * @brief Performs in-place matrix decomposition.
		 * @param[in] mat The matrix to be decomposed, destroyed after the operation.
		 */
		void idecompose(T_Matrix& mat);
		
		/**
		 * @brief Performs in-place matrix solution.
		 * @param[in,out] rhs On input, the right hand side matrix, on exit is overwritten with the solution.
		 */
		void solve(T_Matrix& rhs) const;
		
		/**
		 * @brief Performs in-place vector solution.
		 * @param[in,out] rhs On input, the right hand side vector, on exit is overwritten with the solution.
		 */
		void solve(T_Vector& rhs) const;

	private:
		const T_Matrix& factor() const;
		T_Matrix& factor();
		
		const std::vector<int_t>& ipiv1() const;
		std::vector<int_t>& ipiv1();
		
		const std::vector<int_t>& jpiv1() const;
		std::vector<int_t>& jpiv1();

	private:
		int_t m_info;
		T_Matrix m_factor;
		HeapBuffer<T_Scalar> m_buffer;
		std::vector<int_t> m_ipiv1;
		std::vector<int_t> m_jpiv1;
		
		void defaults();

		void resizeBuffer(uint_t n);
		void resizeFactor(const T_Matrix& mat);

		void prepareForDecomposition(const T_Matrix& mat);
		void prepareForIDecomposition(T_Matrix& mat);
		void prepareForSolution(T_Matrix& rhs) const;

		void decomposeInternallyStoredFactor();
		void decomposeLLt();
		void decomposeLDLt();
		void decomposeLU();
		void decomposeCompleteLU();

		void solveLLt(T_Matrix& rhs) const;
		void solveLDLt(T_Matrix& rhs) const;
		void solveLU(T_Matrix& rhs) const;
		void solveCompleteLU(T_Matrix& rhs) const;

	private:
		const decomp_t m_decompType;
		decomp_t decompType() const;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_BASE_HPP_
