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

#ifndef CLA3P_PARDISO_OPTIONS_HPP_
#define CLA3P_PARDISO_OPTIONS_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"
#include "cla3p/perms.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace pardiso {
/*-------------------------------------------------*/

inline int_t Undefined()
{
	return static_cast<int_t>(-1);
}

/**
 * @ingroup module_index_special_enums
 * @enum reorder_t
 * @brief The method for calculating fill-reducing orderings.
 */
enum class reorder_t : int_t {
	MMD   =  0, /**< The minimum degree algorithm */
	Metis =  2  /**< The nested dissection algorithm from the METIS package */
};

/**
 * @ingroup module_index_special_enums
 * @enum pivot_t
 * @brief The pivoting strategy for symmetric indefinite matrices.
 */
enum class pivot_t : int_t {
	Diagonal1x1              = 0, /**< 1x1 diagonal pivoting */
	BunchKaufman             = 1, /**< 1x1 and 2x2 Bunch-Kaufman pivoting */
	Diagonal1x1NoRefinement  = 2, /**< 1x1 diagonal pivoting (no auto-refinement) */
	BunchKaufmanNoRefinement = 3, /**< 1x1 and 2x2 Bunch-Kaufman pivoting (no auto-refinement) */
};

/*-------------------------------------------------*/

template <typename T_Scalar>
class ImmutableParams {

	protected:
		ImmutableParams();
		~ImmutableParams() = default;

		void setToIparm(int_t *iparm) const;

	private:
		int_t m_iparm00; // User custom values
		int_t m_iparm03; // Preconditioned CGS/CG
		int_t m_iparm05; // Write solution on x
		int_t m_iparm08; // Tolerance level for the relative residual in the iterative refinement process
		int_t m_iparm17; // Report the number of non-zero elements in the factors
		int_t m_iparm18; // Report number of floating point operations
		int_t m_iparm23; // Parallel factorization control
		int_t m_iparm24; // Parallel forward/backward solve control
		int_t m_iparm27; // Single or double precision Intel® oneAPI Math Kernel Library
		int_t m_iparm30; // Partial solve and computing selected components of the solution vectors
		int_t m_iparm33; // Optimal number of OpenMP threads for conditional numerical reproducibility (CNR) mode
		int_t m_iparm34; // One- or zero-based indexing of columns and rows
		int_t m_iparm35; // Schur complement matrix computation control
		int_t m_iparm36; // Format for matrix storage (CSR)
		int_t m_iparm38; // Enable low rank update
		int_t m_iparm42; // Control parameter for the computation of the diagonal of inverse matrix
		int_t m_iparm55; // Diagonal and pivoting control
		int_t m_iparm59; // Intel® oneAPI Math Kernel Library (oneMKL) PARDISO mode
};

/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The Pardiso global parameters.
 */
class GlobalParams {

	public:

		/**
		 * @brief Forces Pardiso to check input matrix.
		 * @param[in] flg Enables/disables input matrix checking.
		 *
		 * When on, Pardiso checks integer arrays colptr and rowidx.
		 * In particular, Pardiso checks whether column indices are sorted in increasing order within each row.
		 */
		void setMatrixChecker(bool flg);

	protected:
		GlobalParams();
		~GlobalParams();

		void clear();

		void setToIparm(int_t *iparm) const;

	private:
		int_t m_iparm26; // Matrix checker

		void defaults();
};

/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The Pardiso analysis phase parameters.
 */
class AnalysisParams {

	private:

		enum class perm_t : int_t {
			UserSuppliedPerm =  1,
			DefaultPerm      =  2
		};

	public:

		/**
		 * @brief Sets the fill reducing ordering method.
		 * @param[in] reorderMethod The desired reordering method (MMD/Metis).
		 *
		 * Pardiso will internally calculate a fill-reducing ordering based on the method provided.
		 *
		 * Default value is pardiso::reorder_t::Metis.
		 */
		void setFillReducer(pardiso::reorder_t reorderMethod);

		/**
		 * @brief Sets a custom fill-reducing permutation.
		 * @param[in] permMatrix The user supplied permutation matrix.
		 *
		 * Pardiso will skip the fill-reducing ordering calculation 
		 * and use the user supplied permutation matrix in the analysis phase.
		 */
		void setFillReducer(const prm::PiMatrix& permMatrix);

	protected:
		AnalysisParams();
		~AnalysisParams();

		void clear();

		void setToIparm(int_t *iparm) const;

		void setScaling(bool flg);
		void setMatching(bool flg);

		bool userDefinedPermutation() const;
		const prm::PiMatrix& userPermMatrix() const;

	private:
		pardiso::reorder_t m_iparm01; // Fill-in reducing ordering for the input matrix
		perm_t             m_iparm04; // User permutation
		int_t              m_iparm10; // Scaling vectors
		int_t              m_iparm12; // Improved accuracy using (non-) symmetric weighted matching

		prm::PiMatrix m_permMatrix;

		void defaults();
};

/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The Pardiso decomposition phase parameters.
 */
class DecompParams {

	protected:
		DecompParams();
		~DecompParams();

		void clear();

		void setToIparm(int_t *iparm) const;

		void setPivotingPerturbation(int_t p);
		void setPivoting(pardiso::pivot_t pivot);

	private:
		int_t            m_iparm09; // Pivoting perturbation
		pardiso::pivot_t m_iparm20; // Pivoting for symmetric indefinite matrices

		void defaults();
};

/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The Pardiso solution phase parameters.
 */
class SolveParams {

	public:

		/**
		 * @brief Sets maximum number of iterative refinement steps.
		 * @param[in] numIters The maximum iteration number.
		 *
		 * Sets the maximum number of iterative refinement steps that the solver performs.
		 *
		 *  - numIters = 0, (default) Automatically performs two steps of iterative refinement 
		 *                  when perturbed pivots are obtained during the numerical factorization.)
		 *  - numIters > 0, The solver performs not more than the absolute value of `numIters` steps of iterative refinement.
		 *                  The solver might stop the process before the maximum number of steps.
		 *  - numIters < 0, The solver performs not more than the absolute value of `numIters` steps of iterative refinement.
		 *                  The accumulation of the residuum uses extended precision real and complex data types.
		 */
		void setMaxIterativeRefinements(int_t numIters);

	protected:
		SolveParams();
		~SolveParams();

		void clear();

		void setToIparm(int_t *iparm) const;

	private:
		int_t m_iparm07; // Iterative refinement step
		int_t m_iparm11; // Solve with transposed or conjugate transposed matrix

		void defaults();
};

/*-------------------------------------------------*/
} // namespace pardiso
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PARDISO_OPTIONS_HPP_
