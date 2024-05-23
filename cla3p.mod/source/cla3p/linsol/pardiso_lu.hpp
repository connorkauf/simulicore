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

#ifndef CLA3P_PARDISO_LU_HPP_
#define CLA3P_PARDISO_LU_HPP_

/**
 * @file
 */

#include "cla3p/linsol/pardiso_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The LU linear solver for non-symmetric sparse matrices.
 */
template <typename T_Matrix>
class PardisoLU : public PardisoBase<T_Matrix> {

	public:

		// no copy
		PardisoLU(const PardisoLU&) = delete;
		PardisoLU& operator=(const PardisoLU&) = delete;

		/**
		 * @copydoc cla3p::PardisoLLt::PardisoLLt()
		 */
		PardisoLU() : PardisoBase<T_Matrix>(decomp_t::LU) {}

		/**
		 * @copydoc cla3p::PardisoLLt::~PardisoLLt()
		 */
		~PardisoLU() = default;

		/**
		 * @brief Scaling vectors.
		 * @param[in] flg Enables/disables scaling.
		 *
		 * Pardiso uses a maximum weight matching algorithm to permute large elements on the diagonal 
		 * and to scale so that the diagonal elements are equal to 1 and the absolute values of the 
		 * off-diagonal entries are less than or equal to 1. 
		 *
		 * Set before analysis. Default value is true.
		 */
		void setScaling(bool flg)
		{
			return PardisoBase<T_Matrix>::AnalysisParams::setScaling(flg);
		}

		/**
		 * @brief Improved accuracy using non-symmetric weighted matching.
		 * @param[in] flg Enables/disables matching.
		 *
		 * Pardiso can use a maximum weighted matching algorithm to permute large elements close the diagonal. 
		 * This strategy adds an additional level of reliability to the factorization methods and complements 
		 * the alternative of using more complete pivoting techniques during the numerical factorization.
		 *
		 * Set before analysis. Default value is true.
		 */
		void setMatching(bool flg)
		{
			return PardisoBase<T_Matrix>::AnalysisParams::setMatching(flg);
		}
		/**
		 * @brief Small/zero pivot handling
		 * @param[in] p Negative power in the perturbation calculation formula.
		 *
		 * This parameter instructs Pardiso how to handle small pivots or zero pivots.
		 * Small pivots are perturbed with eps = 10<sup>-p</sup>.
		 * For more details, refer to the Pardiso manual (iparm[9]).
		 *
		 * Set before decomposition. Default value is 13.
		 */
		void setPivotingPerturbation(int_t p)
		{
			return PardisoBase<T_Matrix>::DecompParams::setPivotingPerturbation(p);
		}
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PARDISO_LU_HPP_
