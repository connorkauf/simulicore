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

#ifndef CLA3P_DEFAULT_SVD_HPP_
#define CLA3P_DEFAULT_SVD_HPP_

/**
 * @file
 */

#include "cla3p/types/integer.hpp"
#include "cla3p/support/heap_buffer.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The default singular value decomposition class for dense matrices.
 */
template <typename T_Matrix>
class DefaultSVD {

	private:
		using T_Scalar = typename T_Matrix::value_type;
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_Vector = typename TypeTraits<T_Matrix>::vector_type;
		using T_RVector = typename TypeTraits<T_Vector>::real_type;

	public:

		/**
		 * @brief The default constructor.
		 * @details Constructs an empty svd object.
		 */
		DefaultSVD();

		/**
		 * @brief The dimensional constructor.
		 * @details Constructs a svd object with internal buffer pre-allocation.
		 * @param[in] m The maximum number of rows the buffer can fit.
		 * @param[in] n The maximum number of columns the buffer can fit.
		 * @param[in] lPolicy If true, a (m x m) buffer will be allocated for U, otherwise a (m x min(m,n)).
		 * @param[in] rPolicy If true, a (n x n) buffer will be allocated for V, otherwise a (n x min(m,n)).
		 */
		DefaultSVD(uint_t m, uint_t n, svpolicy_t lPolicy = svpolicy_t::Limited, svpolicy_t rPolicy = svpolicy_t::Limited);

		/**
		 * @brief Destroys the svd object.
		 * @details Clears all internal data and destroys the svd object.
		 */
		~DefaultSVD();

		/**
		 * @brief Clears the object internal data.
		 * @details Clears the object internal data and resets all settings.
		 */
		void clear();

		/**
		 * @brief Allocates internal buffers.
		 * @param[in] m The maximum number of rows the buffer can fit.
		 * @param[in] n The maximum number of columns the buffer can fit.
		 */
		void reserve(uint_t m, uint_t n);

		/**
		 * @brief Gets the policy for the left singular vectors.
		 * @details Informs about the singular vectors calculation options.@n
		 *          Meaning if all/some/none of the left singular vectors will be calculated.
		 */
		svpolicy_t leftPolicy() const;

		/**
		 * @brief Gets the policy for the right singular vectors.
		 * @details Informs about the singular vectors calculation options.@n
		 *          Meaning if all/some/none of the right singular vectors will be calculated.
		 */
		svpolicy_t rightPolicy() const;

		/**
		 * @brief Sets the policy for the left singular vectors.
		 * @details Informs the object about the singular vectors calculation options.@n
		 *          Meaning if all/some/none of the left singular vectors will be calculated.
		 */
		void setLeftPolicy(svpolicy_t lPolicy);

		/**
		 * @brief Sets the policy for the right singular vectors.
		 * @details Informs the object about the singular vectors calculation options.@n
		 *          Meaning if all/some/none of the right singular vectors will be calculated.
		 */
		void setRightPolicy(svpolicy_t rPolicy);

		/**
		 * @brief Performs matrix singular value decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 */
		void decompose(const T_Matrix& mat);

		/**
		 * @brief The singular values.
		 * @details The array of size min(m,n) that contains the singular values in descending order.
		 */
		const T_RVector& singularValues() const;

		/**
		 * @brief The left singular vectors (U).
		 * @details The matrix of size (m,k) that contains the left singular vectors.@n
		 *          `k`: `m` if leftPolicy is Full@n
		 *          `k`: `min(m,n)` if leftPolicy is Limited
		 */
		const T_Matrix& leftSingularVectors() const;

		/**
		 * @brief The right singular vectors (V).
		 * @details The matrix of size (n,k) that contains the right singular vectors.@n
		 *          `k`: `n` if rightPolicy is Full@n
		 *          `k`: `min(m,n)` if rightPolicy is Limited
		 */
		const T_Matrix& rightSingularVectors() const;

	private:
		svpolicy_t m_leftPolicy;
		svpolicy_t m_rightPolicy;

		T_RVector m_singularValues;
		T_RVector m_superbVector;

		T_Matrix m_matrixBackup;
		T_Matrix m_leftSingularVectors;
		T_Matrix m_rightSingularVectors;

		HeapBuffer<T_RScalar> m_realBuffers;
		HeapBuffer<T_Scalar> m_scalarBuffers;

		void defaults();

		void clearInternalWrappers();
		void clearInternalBuffers();
		void resizeInternalObjects(const T_Matrix& mat);
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DEFAULT_SVD_HPP_
