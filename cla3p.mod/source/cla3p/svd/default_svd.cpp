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
#include "cla3p/svd/default_svd.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
//#include "cla3p/support/utils.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/checks/lapack_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultSVD<T_Matrix>::DefaultSVD()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultSVD<T_Matrix>::DefaultSVD(uint_t m, uint_t n, svpolicy_t lPolicy, svpolicy_t rPolicy)
	: 
		DefaultSVD<T_Matrix>::DefaultSVD()
{
	setLeftPolicy(lPolicy);
	setRightPolicy(rPolicy);
	reserve(m, n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultSVD<T_Matrix>::~DefaultSVD()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::defaults()
{
	setLeftPolicy(svpolicy_t::Limited);
	setRightPolicy(svpolicy_t::Limited);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::clearInternalWrappers()
{
	m_singularValues.clear();
	m_superbVector.clear();
	m_matrixBackup.clear();
	m_leftSingularVectors.clear();
	m_rightSingularVectors.clear();

	m_realBuffers.rewind();
	m_scalarBuffers.rewind();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::clearInternalBuffers()
{
	m_realBuffers.clear();
	m_scalarBuffers.clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::clear()
{
	clearInternalWrappers();
	clearInternalBuffers();

	defaults();
}
/*-------------------------------------------------*/
static uint_t policyToNumCols(svpolicy_t policy, uint_t n, uint_t k)
{
	uint_t ret = 0;

	if(policy == svpolicy_t::Limited)
		ret = k;
	else if(policy == svpolicy_t::Full)
		ret = n;

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::reserve(uint_t m, uint_t n)
{
	uint_t k = std::min(m,n);

	uint_t leftCols = policyToNumCols(leftPolicy(), m, k);
	uint_t rightCols = policyToNumCols(rightPolicy(), n, k);

	m_realBuffers.resize(2 * k - 1);
	m_scalarBuffers.resize(m * n + m * leftCols + n * rightCols);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::setLeftPolicy(svpolicy_t lPolicy)
{
	m_leftPolicy = lPolicy; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::setRightPolicy(svpolicy_t rPolicy)
{
	m_rightPolicy = rPolicy; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
svpolicy_t DefaultSVD<T_Matrix>::leftPolicy() const
{
	return m_leftPolicy; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
svpolicy_t DefaultSVD<T_Matrix>::rightPolicy() const
{ 
	return m_rightPolicy; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const typename DefaultSVD<T_Matrix>::T_RVector& DefaultSVD<T_Matrix>::singularValues() const
{
	return m_singularValues; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& DefaultSVD<T_Matrix>::leftSingularVectors() const
{ 
	return m_leftSingularVectors; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& DefaultSVD<T_Matrix>::rightSingularVectors() const
{ 
	return m_rightSingularVectors; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::resizeInternalObjects(const T_Matrix& mat)
{
	uint_t m = mat.nrows();
	uint_t n = mat.ncols();

	reserve(m, n);

	uint_t k = std::min(m,n);

	uint_t leftCols = policyToNumCols(leftPolicy(), m, k);
	uint_t rightCols = policyToNumCols(rightPolicy(), n, k);

	clearInternalWrappers();

	{
		m_singularValues = T_RVector::wrap(k, m_realBuffers.request(k), false);
		m_superbVector = T_RVector::wrap(k - 1, m_realBuffers.request(k-1), false);
	}

	{
		m_matrixBackup = T_Matrix::wrap(m, n, m_scalarBuffers.request(m * n), m, false, mat.prop());

		if(leftCols) {
			m_leftSingularVectors = T_Matrix::wrap(m, leftCols, m_scalarBuffers.request(m * leftCols), m, false);
		}

		if(rightCols) {
			m_rightSingularVectors = T_Matrix::wrap(rightCols, n, m_scalarBuffers.request(n * rightCols), rightCols, false);
		}
	}
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static void recursive_transpose_right_singular_vectors(T_Matrix& Vt, T_Matrix& A)
{
	using T_Scalar = typename T_Matrix::value_type;

	uint_t m = A.nrows();
	uint_t n = A.ncols();
	uint_t k = Vt.nrows();

	if(Vt.ncols() != n)
		throw err::NoConsistency("Invalid dimensions for right singular vectors matrix");

	if(k <= m) {

		T_Matrix Akn = A.rblock(0,0,k,n);
		Akn = Vt;

		T_Scalar *values = Vt.values();
		Vt.clear();
		Vt = T_Matrix::wrap(n, k, values, n, false);
		Vt = Akn.ctranspose();

	} else {

		// 
		// in this scope: k == n && n > m
		//

		T_Matrix Amm = A.rblock(0,0,m,m);
		T_Matrix Vmm = Vt.rblock(0,0,m,m);
		Amm = Vmm;
		Vmm = Amm.ctranspose();

		uint_t l = n - m;

		if(l) {

			T_Matrix Aml = A.rblock(0,m,m,l);
			T_Matrix Vml = Vt.rblock(0,m,m,l);
			T_Matrix Vlm = Vt.rblock(m,0,l,m);
			T_Matrix Vll = Vt.rblock(m,m,l,l);
			Aml = Vml;
			Vml = Vlm.ctranspose();
			Vlm = Aml.ctranspose();

			recursive_transpose_right_singular_vectors(Vll, Aml);

		} // l

	} // m?n
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultSVD<T_Matrix>::decompose(const T_Matrix& mat)
{ 
	resizeInternalObjects(mat);

	m_matrixBackup = mat;
	m_matrixBackup.igeneral();

	uint_t minld = 1;

	int_t info = lapack::gesvd(
			static_cast<char>(leftPolicy()), 
			static_cast<char>(rightPolicy()), 
			m_matrixBackup.nrows(), 
			m_matrixBackup.ncols(), 
			m_matrixBackup.values(),
			m_matrixBackup.ld(),
			m_singularValues.values(), 
			m_leftSingularVectors.values(), 
			std::max(minld, m_leftSingularVectors.ld()), // ld == 0 leads to lapack error
			m_rightSingularVectors.values(), 
			std::max(minld, m_rightSingularVectors.ld()), // ld == 0 leads to lapack error
			m_superbVector.values());

	lapack_info_check(info);

	if(m_rightSingularVectors) 
		recursive_transpose_right_singular_vectors(m_rightSingularVectors, m_matrixBackup);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class DefaultSVD<dns::RdMatrix>;
template class DefaultSVD<dns::RfMatrix>;
template class DefaultSVD<dns::CdMatrix>;
template class DefaultSVD<dns::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
