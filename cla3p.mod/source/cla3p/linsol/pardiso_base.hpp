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

#ifndef CLA3P_PARDISO_BASE_HPP_
#define CLA3P_PARDISO_BASE_HPP_

/**
 * @file
 */

#include <string>

#include "cla3p/types.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/linsol/pardiso_options.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The Pardiso linear solver base for sparse matrices.
 */
template <typename T_Matrix>
class PardisoBase : 
	private pardiso::ImmutableParams<typename T_Matrix::value_type>,
	public pardiso::GlobalParams,
	public pardiso::AnalysisParams,
	public pardiso::DecompParams,
	public pardiso::SolveParams {

	private:
		using T_Scalar = typename T_Matrix::value_type;
		using T_DnsMatrix = typename TypeTraits<T_Matrix>::dns_type;
		using T_Vector = typename TypeTraits<T_DnsMatrix>::vector_type;

	private:
		enum class mtype_t : int_t {
			Undefined                    =  0,
			RealStructurallySymmetric    =  1,
			RealSymmetricPosdef          =  2,
			RealSymmetricIndef           = -2,
			ComplexStructurallySymmetric =  3,
			ComplexHermitianPosdef       =  4,
			ComplexHermitianIndef        = -4,
			ComplexSymmetric             =  6,
			RealNonSymmetric             = 11,
			ComplexNonSymmetric          = 13
		};

		enum class phase_t : int_t {
			Analysis              =  11,
			AnalysisNumeric       =  12,
			AnalysisNumericSolve  =  13,
			Numeric               =  22,
			NumericSolve          =  23,
			Solve                 =  33,
			ForwardSolve          = 331,
			DiagonalSolve         = 332,
			BackwardSolve         = 333,
			ClearNumeric          =   0,
			ClearAll              =  -1,
		};

	protected:
		PardisoBase(decomp_t decompType);
		~PardisoBase();

	public:
		std::string name() const;

		/**
		 * @brief Clears the solver internal data.
		 *
		 * Clears the solver internal data and resets all settings. 
		 */
		void clear();

		/**
		 * @brief Clears the solver numeric factor data.
		 *
		 * Clears memory allocated for the factor storage.
		 */
		void clearNumeric();

		/**
		 * @brief Performs matrix analysis & symbolic decomposition.
		 * @param[in] mat The matrix to be analyzed.
		 *
		 * Performs matrix analysis & symbolic decomposition.
		 * Uses settings from the pardiso::GlobalParams & pardiso::AnalysisParams classes.
		 */
		void analysis(const T_Matrix& mat);

		/**
		 * @brief Performs matrix decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 *
		 * Performs matrix numerical decomposition.
		 * Uses settings from the pardiso::GlobalParams & pardiso::DecompParams classes.
		 */
		void decompose(const T_Matrix& mat);

		/**
		 * @brief Performs matrix solution.
		 * @param[in] rhs The right hand side matrix.
		 * @param[out] sol The matrix containing with the solution.
		 *
		 * Calculates the solution `sol` using the decomposed matrix.
		 * Uses settings from the pardiso::GlobalParams & pardiso::SolveParams classes.
		 */
		void solve(const T_DnsMatrix& rhs, T_DnsMatrix& sol);

		/**
		 * @brief Performs vector solution.
		 * @param[in] rhs The right hand side vector.
		 * @param[out] sol The vector containing with the solution.
		 *
		 * Calculates the solution `sol` using the decomposed matrix.
		 * Uses settings from the pardiso::GlobalParams & pardiso::SolveParams classes.
		 */
		void solve(const T_Vector& rhs, T_Vector& sol);

		/**
		 * @brief Message level information.
		 * @param[in] flg Enables/disables Pardiso verbosity.
		 *
		 *  - flg = false, Pardiso generates no output
		 *  - flg = true, Pardiso prints statistical information to the screen.
		 */
		void setVerbose(bool flg);

		/**
		 * @brief Gets the calculated fill-reducing permutation matrix.
		 * @return The currently used fill-reducing permutation matrix.
		 *
		 * You can access the fill-reducing ordering calculated in the analysis phase.
		 * Useful for testing reordering algorithms, adapting the code to special applications problems, 
		 * or for using the permutation vector more than once for matrices with identical sparsity structures.
		 *
		 * Set before analysis.
		 */
		const prm::PiMatrix& fillReducingOrdering() const;

		/**
		 * @brief Iterative refinement steps performed.
		 * @return The number of iterative refinement steps performed.
		 *
		 * Reports the number of iterative refinement steps that were actually performed during the solve step.
		 *
		 * Available after solve.
		 */
		int_t iterativeRefinementSteps() const;

		/**
		 * @brief Number of perturbed pivots.
		 * @return The number of perturbed pivots applied.
		 *
		 * Contains the number of perturbed pivots (not for positive definite matrices).
		 *
		 * Available after decomposition.
		 */
		int_t perturbedPivots() const;

		/**
		 * @brief Peak memory on symbolic factorization.
		 * @return The peak analysis memory (Kb).
		 *
		 * The total peak memory in kilobytes that the solver needs
		 * during the analysis and symbolic factorization phase.
		 *
		 * Available after analysis.
		 */
		int_t peakAnalysisMemory() const;

		/**
		 * @brief Permanent memory on symbolic factorization.
		 * @return The permanent analysis memory (Kb).
		 *
		 * Permanent memory from the analysis and symbolic factorization phase 
		 * in kilobytes that the solver needs in the factorization and solve phases.
		 *
		 * Available after analysis.
		 */
		int_t permanentAnalysisMemory() const;

		/**
		 * @brief Size of factors/Peak memory on numerical factorization and solution.
		 * @return The permanent analysis memory (Kb).
		 *
		 * This parameter provides the size in kilobytes of the total memory consumed
		 * by (in-core) Pardiso for internal floating point arrays.
		 *
		 * Available after analysis.
		 */
		int_t factorMemory() const;

	protected:
		int_t inertiaPositive() const;
		int_t inertiaNegative() const;

	private:
		static constexpr std::size_t PT_DIM = 64;
		static constexpr std::size_t IPARM_DIM = 64;

		std::size_t m_pt[PT_DIM];
		int_t m_iparm[IPARM_DIM];

		mtype_t m_mtype;
		int_t m_maxfct;
		int_t m_msglvl;	

		uint_t m_dim;
		const int_t *m_colptr;
		const int_t *m_rowidx;
		const T_Scalar *m_values;
		prm::PiMatrix m_permBuffer;
		prm::PiMatrix m_permMatrix;

		void defaults();

	private:
		const decomp_t m_decompType;
		decomp_t decompType() const;

		void prepareForAnalysis(const T_Matrix&);
		void prepareForDecomposition(const T_Matrix&);
		void prepareForSolution(const T_DnsMatrix&, T_DnsMatrix&);

		mtype_t deduceMtype(const T_Matrix&);
		void updateMatrixInfo(const T_Matrix&);

		void updateIparmAnalysis();
		void updateIparmDecomposition();
		void updateIparmSolve();

		void resizePerm(uint_t size);
		void configureFillReducer();

		void callDriver(phase_t phase, int_t nrhs = 0, T_Scalar *b = nullptr, T_Scalar *x = nullptr);
		void checkError(int_t error) const;

		void clearReservedParams();
		void clearOutputParams();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PARDISO_BASE_HPP_
