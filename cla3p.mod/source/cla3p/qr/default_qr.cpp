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
#include "cla3p/qr/default_qr.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/checks/lapack_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultQR<T_Matrix>::DefaultQR()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultQR<T_Matrix>::DefaultQR(uint_t m, uint_t n, qpolicy_t qPolicy)
	: 
		DefaultQR<T_Matrix>::DefaultQR()
{
	setQMatPolicy(qPolicy);
	reserve(m, n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
DefaultQR<T_Matrix>::~DefaultQR()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::defaults()
{
	setQMatPolicy(qpolicy_t::Reflection);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::clearInternalWrappers()
{
	m_matrixA.clear();
	m_tauVector.clear();
	m_matrixR.clear();
	m_matrixQ.clear();

	m_scalarBuffers.rewind();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::clearInternalBuffers()
{
	m_scalarBuffers.clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::clear()
{
	clearInternalWrappers();
	clearInternalBuffers();

	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::reserve(uint_t m, uint_t n)
{
	uint_t k = std::min(m,n);

	std::size_t bufferSize = 
		m * n + // matrixBackup
		k +     // tau
		k * n;  // matrixR

	if(qMatPolicy() == qpolicy_t::Full)
		bufferSize += m * k; // matrixQ

	m_scalarBuffers.resize(bufferSize);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
qpolicy_t DefaultQR<T_Matrix>::qMatPolicy() const
{
	return m_qPolicy;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::setQMatPolicy(qpolicy_t qPolicy)
{
	m_qPolicy = qPolicy;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const typename DefaultQR<T_Matrix>::T_Vector& DefaultQR<T_Matrix>::tau() const
{
	return m_tauVector; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& DefaultQR<T_Matrix>::R() const
{ 
	return m_matrixR; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& DefaultQR<T_Matrix>::Q() const
{ 
	return m_matrixQ; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& DefaultQR<T_Matrix>::elementaryReflectors() const
{ 
	return m_matrixA; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::resizeInternalObjects(const T_Matrix& mat)
{
	uint_t m = mat.nrows();
	uint_t n = mat.ncols();

	reserve(m, n);

	uint_t k = std::min(m,n);

	clearInternalWrappers();

	{
		m_matrixA = T_Matrix::wrap(m, n, m_scalarBuffers.request(m * n), m, false, mat.prop());
		m_tauVector = T_Vector::wrap(k, m_scalarBuffers.request(k), false);
		m_matrixR = T_Matrix::wrap(k, n, m_scalarBuffers.request(k * n), k, false);

		if(qMatPolicy() == qpolicy_t::Full) {
			m_matrixQ = T_Matrix::wrap(m, k, m_scalarBuffers.request(m * k), m, false);
		}
	}
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::decompose(const T_Matrix& mat)
{ 
	resizeInternalObjects(mat);

	m_matrixA = mat;
	m_matrixA.igeneral();

	int_t info = lapack::geqrf(
			m_matrixA.nrows(), 
			m_matrixA.ncols(), 
			m_matrixA.values(),
			m_matrixA.ld(),
			m_tauVector.values());

	lapack_info_check(info);

	fillMatrixR();
	fillMatrixQ();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::fillMatrixR()
{
	uint_t m = m_matrixR.nrows();
	uint_t n = m_matrixR.ncols();
	uint_t k = std::min(m,n);

	m_matrixR = m_matrixA.rblock(0,0,m,n);

	for(uint_t j = 0; j < k; j++) {
		for(uint_t i = j+1; i < k; i++) {
			m_matrixR(i,j) = T_Scalar(0);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void DefaultQR<T_Matrix>::fillMatrixQ()
{
	if(m_matrixQ) {

		uint_t m = m_matrixQ.nrows();
		uint_t n = m_matrixQ.ncols();

		m_matrixQ = m_matrixA.rblock(0,0,m,n);

		int_t info = lapack::xxgqr(m, n, n, 
				m_matrixQ.values(), 
				m_matrixQ.ld(), 
				m_tauVector.values());

		lapack_info_check(info);

	} // explicit calculation of Q
}
/*-------------------------------------------------*/
template class DefaultQR<dns::RdMatrix>;
template class DefaultQR<dns::RfMatrix>;
template class DefaultQR<dns::CdMatrix>;
template class DefaultQR<dns::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
