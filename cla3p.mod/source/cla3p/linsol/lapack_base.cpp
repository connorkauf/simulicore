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
#include "cla3p/linsol/lapack_base.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackBase<T_Matrix>::LapackBase()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackBase<T_Matrix>::LapackBase(uint_t n)
{
	defaults();
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackBase<T_Matrix>::~LapackBase()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::defaults()
{
	setInfo(0);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t LapackBase<T_Matrix>::info() const 
{ 
	return m_info;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::setInfo(int_t info)
{ 
	m_info = info;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& LapackBase<T_Matrix>::factor() const
{ 
	return m_factor; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix&  LapackBase<T_Matrix>::factor()
{ 
	return m_factor; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const T_Matrix& LapackBase<T_Matrix>::buffer() const
{ 
	return m_buffer; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix&  LapackBase<T_Matrix>::buffer()
{
	return m_buffer; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const std::vector<int_t>& LapackBase<T_Matrix>::ipiv1() const 
{ 
	return m_ipiv1;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
std::vector<int_t>& LapackBase<T_Matrix>::ipiv1()
{ 
	return m_ipiv1; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const std::vector<int_t>& LapackBase<T_Matrix>::jpiv1() const
{ 
	return m_jpiv1;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
std::vector<int_t>& LapackBase<T_Matrix>::jpiv1()
{ 
	return m_jpiv1; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::reserve(uint_t n)
{
	if(buffer().nrows() < n && buffer().ncols() < n) {
		buffer().clear();
		buffer() = T_Matrix::init(n, n);
	}
	ipiv1().reserve(n);
	jpiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::clear()
{
	factor().clear();
	buffer().clear();
	ipiv1().clear();
	jpiv1().clear();

	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decompose(const T_Matrix& mat)
{
	initializeFactor(mat);
	decomposeFactor();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::idecompose(T_Matrix& mat)
{
	factor().clear();
	factor() = mat.move();
	decomposeFactor();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::initializeFactor(const T_Matrix& mat)
{
	factor().clear();

	if(buffer().nrows() >= mat.nrows() && buffer().ncols() >= mat.ncols()) {

		factor() = T_Matrix::wrap(
				mat.nrows(), 
				mat.ncols(), 
				buffer().values(), 
				mat.nrows(), 
				false, 
				mat.prop());

	} // sufficient buffer

	factor() = mat;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solve(T_Matrix& rhs) const
{
	solveForRhs(rhs);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solve(T_Vector& rhs) const
{
	T_Matrix tmp = rhs.rmatrix();
	solve(tmp);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LapackBase<dns::RdMatrix>;
template class LapackBase<dns::RfMatrix>;
template class LapackBase<dns::CdMatrix>;
template class LapackBase<dns::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
