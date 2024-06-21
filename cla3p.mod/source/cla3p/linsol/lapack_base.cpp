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
#include "cla3p/support/utils.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/checks/decomp_llt_checks.hpp"
#include "cla3p/checks/decomp_ldlt_checks.hpp"
#include "cla3p/checks/decomp_lu_checks.hpp"
#include "cla3p/checks/solve_checks.hpp"
#include "cla3p/checks/lapack_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackBase<T_Matrix>::LapackBase(decomp_t decompType)
	: m_decompType(decompType)
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackBase<T_Matrix>::LapackBase(decomp_t decompType, uint_t n)
	: LapackBase<T_Matrix>(decompType)
{
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
decomp_t LapackBase<T_Matrix>::decompType() const
{
	return m_decompType;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
std::string LapackBase<T_Matrix>::name() const
{
	std::ostringstream ss;
	ss << "Lapack " << decompType();
	return ss.str();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::defaults()
{
	m_info = 0;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::clear()
{
	m_factor.clear();
	m_buffer.clear();

	ipiv1().clear();
	jpiv1().clear();

	defaults();
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
	resizeBuffer(n);
	ipiv1().reserve(n);
	jpiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::resizeBuffer(uint_t n)
{
	m_buffer.resize(n * n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::resizeFactor(const T_Matrix& mat)
{
	resizeBuffer(mat.ncols());

	m_factor = T_Matrix::wrap(
			mat.nrows(), 
			mat.ncols(), 
			m_buffer.data(), 
			mat.nrows(), 
			false, 
			mat.prop());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::prepareForDecomposition(const T_Matrix& mat)
{
	decomp_generic_check(mat);

	m_info = 0;
	resizeFactor(mat);
	m_factor = mat;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::prepareForIDecomposition(T_Matrix& mat)
{
	decomp_generic_check(mat);

	m_info = 0;
	m_factor.clear();
	m_factor = mat.move();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decompose(const T_Matrix& mat)
{
	prepareForDecomposition(mat);
	decomposeInternallyStoredFactor();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::idecompose(T_Matrix& mat)
{
	prepareForIDecomposition(mat);
	decomposeInternallyStoredFactor();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decomposeInternallyStoredFactor()
{
	decomp_t dtype = determineDecompType(decompType(), m_factor.prop());

	if(dtype == decomp_t::LLT)
		decomposeLLt();

	else if(dtype == decomp_t::LDLT)
		decomposeLDLt();

	else if(dtype == decomp_t::LU)
		decomposeLU();

	else if(dtype == decomp_t::CompleteLU)
		decomposeCompleteLU();

	else
		throw err::Exception();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::prepareForSolution(T_Matrix& rhs) const
{
	if(!m_factor)
		throw err::InvalidOp("Decomposition stage is not performed");

	//if(m_info)
	//	throw err::InvalidOp("Decomposition stage is faulty");

	default_solve_input_check(m_factor.ncols(), rhs);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solve(T_Matrix& rhs) const
{
	prepareForSolution(rhs);

	decomp_t dtype = determineDecompType(decompType(), m_factor.prop());

	if(dtype == decomp_t::LLT)
		solveLLt(rhs);

	else if(dtype == decomp_t::LDLT)
		solveLDLt(rhs);

	else if(dtype == decomp_t::LU)
		solveLU(rhs);

	else if(dtype == decomp_t::CompleteLU)
		solveCompleteLU(rhs);

	else
		throw err::Exception();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solve(T_Vector& rhs) const
{
	T_Matrix tmp = rhs.rmatrix();
	solve(tmp);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decomposeLLt()
{
	llt_decomp_input_check(m_factor);

	m_info = lapack::potrf(
			m_factor.prop().cuplo(), 
			m_factor.ncols(), 
			m_factor.values(), 
			m_factor.ld());
	
	lapack_info_check(m_info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decomposeLDLt()
{
	ldlt_decomp_input_check(m_factor);

	if(m_factor.prop().isSymmetric()) {

		ipiv1().resize(m_factor.ncols());

		m_info = lapack::sytrf(
				m_factor.prop().cuplo(),
				m_factor.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data());

	} else if(m_factor.prop().isHermitian()) {

		ipiv1().resize(m_factor.ncols());

		m_info = lapack::hetrf(
				m_factor.prop().cuplo(),
				m_factor.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(m_info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decomposeLU()
{
	lu_decomp_input_check(m_factor);

	m_factor.igeneral();

	if(m_factor.prop().isGeneral()) {

		ipiv1().resize(std::min(m_factor.nrows(), m_factor.ncols()));

		m_info = lapack::getrf(
				m_factor.nrows(),
				m_factor.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(m_info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::decomposeCompleteLU()
{
	lu_decomp_input_check(m_factor);

	m_factor.igeneral();

	if(m_factor.prop().isGeneral()) {

		ipiv1().resize(std::min(m_factor.nrows(), m_factor.ncols()));
		jpiv1().resize(std::min(m_factor.nrows(), m_factor.ncols()));

		m_info = lapack::getc2(
				m_factor.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data(),
				jpiv1().data());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(m_info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solveLLt(T_Matrix& rhs) const
{
	int_t info = lapack::potrs(
			m_factor.prop().cuplo(), 
			m_factor.ncols(), 
			rhs.ncols(), 
			m_factor.values(), 
			m_factor.ld(), rhs.values(), rhs.ld());
	
	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solveLDLt(T_Matrix& rhs) const
{
	int_t info = 0;

	if(m_factor.prop().isSymmetric()) {

		info = lapack::sytrs(
				m_factor.prop().cuplo(),
				m_factor.ncols(),
				rhs.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data(),
				rhs.values(),
				rhs.ld());

	} else if(m_factor.prop().isHermitian()) {

		info = lapack::hetrs(
				m_factor.prop().cuplo(),
				m_factor.ncols(),
				rhs.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data(),
				rhs.values(),
				rhs.ld());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solveLU(T_Matrix& rhs) const
{
	int_t info = 0;

	if(m_factor.prop().isGeneral()) {

		info = lapack::getrs('N',
				m_factor.ncols(),
				rhs.ncols(),
				m_factor.values(),
				m_factor.ld(),
				ipiv1().data(),
				rhs.values(),
				rhs.ld());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackBase<T_Matrix>::solveCompleteLU(T_Matrix& rhs) const
{
	if(m_factor.prop().isGeneral()) {

		uint_t nrhs = rhs.ncols();
		T_Matrix scale(nrhs, 1);

		for(uint_t k = 0; k < rhs.ncols(); k++) {

			auto scale_k = arith::getRe(scale(k,0));
			T_Vector rhs_k = rhs.rcolumn(k);

			int_t info = lapack::gesc2(
					m_factor.ncols(),
					m_factor.values(),
					m_factor.ld(),
					rhs_k.values(),
					ipiv1().data(),
					jpiv1().data(),
					&scale_k);

			scale(k,0) = scale_k;

			// should I also scale here ???

			lapack_info_check(info);

		} // k

	} else {

		throw err::Exception("Unreachable");

	} // prop
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
