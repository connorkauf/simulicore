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

// this file inc
#include "cla3p/linsol/pardiso_options.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace pardiso {
/*-------------------------------------------------*/
template <typename T_Scalar>
ImmutableParams<T_Scalar>::ImmutableParams()
{
	int_t i27 = pardiso::Undefined();
	if(TypeTraits<T_Scalar>::is_single_precision()) i27 = 1;
	if(TypeTraits<T_Scalar>::is_double_precision()) i27 = 0;

	m_iparm00 =   1;
	m_iparm03 =   0;
	m_iparm05 =   0;
	m_iparm08 =   0;
	m_iparm17 =   0;
	m_iparm18 =   0;
	m_iparm23 =   0;
	m_iparm24 =   0;
	m_iparm27 = i27;
	m_iparm30 =   0;
	m_iparm33 =   0;
	m_iparm34 =   1;
	m_iparm35 =   0;
	m_iparm36 =   0;
	m_iparm38 =   0;
	m_iparm42 =   0;
	m_iparm55 =   0;
	m_iparm59 =   0;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void ImmutableParams<T_Scalar>::setToIparm(int_t *iparm) const
{
	iparm[ 0] = m_iparm00;
	iparm[ 3] = m_iparm03;
	iparm[ 5] = m_iparm05;
	iparm[ 8] = m_iparm08;
	iparm[17] = m_iparm17;
	iparm[18] = m_iparm18;
	iparm[23] = m_iparm23;
	iparm[24] = m_iparm24;
	iparm[27] = m_iparm27;
	iparm[30] = m_iparm30;
	iparm[33] = m_iparm33;
	iparm[34] = m_iparm34;
	iparm[35] = m_iparm35;
	iparm[36] = m_iparm36;
	iparm[38] = m_iparm38;
	iparm[42] = m_iparm42;
	iparm[55] = m_iparm55;
	iparm[59] = m_iparm59;
}
/*-------------------------------------------------*/
template class ImmutableParams<real_t>;
template class ImmutableParams<real4_t>;
template class ImmutableParams<complex_t>;
template class ImmutableParams<complex8_t>;
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
GlobalParams::GlobalParams()
{
	defaults();
}
/*-------------------------------------------------*/
GlobalParams::~GlobalParams()
{
	clear();
}
/*-------------------------------------------------*/
void GlobalParams::defaults()
{
	m_iparm26 = 0;
}
/*-------------------------------------------------*/
void GlobalParams::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void GlobalParams::setMatrixChecker(bool flg)
{
	m_iparm26 = (flg ? 1 : 0);
}
/*-------------------------------------------------*/
void GlobalParams::setToIparm(int_t *iparm) const
{
	iparm[26] = m_iparm26;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
AnalysisParams::AnalysisParams()
{
	defaults();
}
/*-------------------------------------------------*/
AnalysisParams::~AnalysisParams()
{
	clear();
}
/*-------------------------------------------------*/
void AnalysisParams::defaults()
{
	m_iparm01 = pardiso::reorder_t::Metis;
	m_iparm04 = perm_t::DefaultPerm;
	m_iparm10 = pardiso::Undefined();
	m_iparm12 = pardiso::Undefined();
}
/*-------------------------------------------------*/
void AnalysisParams::clear()
{
	m_permMatrix.clear();
	defaults();
}
/*-------------------------------------------------*/
void AnalysisParams::setToIparm(int_t *iparm) const
{
	iparm[ 1] = static_cast<int_t>(m_iparm01);
	iparm[ 4] = static_cast<int_t>(m_iparm04);
	iparm[10] = m_iparm10;
	iparm[12] = m_iparm12;
}
/*-------------------------------------------------*/
bool AnalysisParams::userDefinedPermutation() const
{
	return (m_iparm04 == perm_t::UserSuppliedPerm);
}
/*-------------------------------------------------*/
void AnalysisParams::setFillReducer(pardiso::reorder_t reorderMethod)
{
	m_iparm01 = reorderMethod;
}
/*-------------------------------------------------*/
void AnalysisParams::setFillReducer(const prm::PiMatrix& permMatrix)
{
	if(m_permMatrix.size() != permMatrix.size())
		m_permMatrix.clear();

	m_permMatrix = permMatrix;
	m_iparm04 = perm_t::UserSuppliedPerm;
}
/*-------------------------------------------------*/
void AnalysisParams::setScaling(bool flg)
{
	m_iparm10 = (flg ? 1 : 0);
}
/*-------------------------------------------------*/
void AnalysisParams::setMatching(bool flg)
{
	m_iparm12 = (flg ? 1 : 0);
}
/*-------------------------------------------------*/
const prm::PiMatrix& AnalysisParams::userPermMatrix() const
{
	return m_permMatrix;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
DecompParams::DecompParams()
{
	defaults();
}
/*-------------------------------------------------*/
DecompParams::~DecompParams()
{
	clear();
}
/*-------------------------------------------------*/
void DecompParams::defaults()
{
	m_iparm09 = pardiso::Undefined();
	m_iparm20 = pardiso::pivot_t::BunchKaufman;
}
/*-------------------------------------------------*/
void DecompParams::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void DecompParams::setToIparm(int_t *iparm) const
{
	iparm[ 9] = m_iparm09;
	iparm[20] = static_cast<int_t>(m_iparm20);
}
/*-------------------------------------------------*/
void DecompParams::setPivoting(pardiso::pivot_t pivot)
{
	m_iparm20 = pivot;
}
/*-------------------------------------------------*/
void DecompParams::setPivotingPerturbation(int_t p)
{
	m_iparm09 = p;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
SolveParams::SolveParams()
{
	defaults();
}
/*-------------------------------------------------*/
SolveParams::~SolveParams()
{
	clear();
}
/*-------------------------------------------------*/
void SolveParams::defaults()
{
	m_iparm07 = 0;
	m_iparm11 = 0;
}
/*-------------------------------------------------*/
void SolveParams::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void SolveParams::setToIparm(int_t *iparm) const
{
	iparm[ 7] = m_iparm07;
	iparm[11] = m_iparm11;
}
/*-------------------------------------------------*/
void SolveParams::setMaxIterativeRefinements(int_t numIters)
{
	m_iparm07 = numIters;
}
/*-------------------------------------------------*/
} // namespace pardiso
} // namespace cla3p
/*-------------------------------------------------*/
