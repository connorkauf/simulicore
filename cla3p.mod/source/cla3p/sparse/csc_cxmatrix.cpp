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
#include "cla3p/sparse/csc_cxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/sparse/csc_rxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace csc {
/*-------------------------------------------------*/
#define CxMatrixTmpl CxMatrix<T_Int,T_Scalar>
#define CxMatrixTlst template <typename T_Int, typename T_Scalar>
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix()
{
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
	: CxMatrixTmpl::XxMatrix(nr, nc, nz, pr)
{
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::~CxMatrix()
{
}
/*-------------------------------------------------*/
CxMatrixTlst
const CxMatrixTmpl& CxMatrixTmpl::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::real() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Symmetric, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), this->nnz(), ret_prop);

	uint_t nc = this->ncols() + 1;
	uint_t nz = this->nnz();

	bulk::dns::copy    (uplo_t::Full, nc, 1, this->colptr(), nc, ret.colptr(), nc);
	bulk::dns::copy    (uplo_t::Full, nz, 1, this->rowidx(), nz, ret.rowidx(), nz);
	bulk::dns::get_real(uplo_t::Full, nz, 1, this->values(), nz, ret.values(), nz);

	return ret;
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::imag() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Skew, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), this->nnz(), ret_prop);

	uint_t nc = this->ncols() + 1;
	uint_t nz = this->nnz();

	bulk::dns::copy    (uplo_t::Full, nc, 1, this->colptr(), nc, ret.colptr(), nc);
	bulk::dns::copy    (uplo_t::Full, nz, 1, this->rowidx(), nz, ret.rowidx(), nz);
	bulk::dns::get_imag(uplo_t::Full, nz, 1, this->values(), nz, ret.values(), nz);

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxMatrixTmpl
#undef CxMatrixTlst
/*-------------------------------------------------*/
template class CxMatrix<int_t,complex_t>;
template class CxMatrix<int_t,complex8_t>;
template class CxMatrix<uint_t,complex_t>;
template class CxMatrix<uint_t,complex8_t>;
/*-------------------------------------------------*/
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/
