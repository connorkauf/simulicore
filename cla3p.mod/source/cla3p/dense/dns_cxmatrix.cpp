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
#include "cla3p/dense/dns_cxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/dense/dns_rxmatrix.hpp"
#include "cla3p/checks/transp_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxMatrixTmpl CxMatrix<T_Scalar>
#define CxMatrixTlst template <typename T_Scalar>
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix()
{
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: CxMatrixTmpl::XxMatrix(nr, nc, pr)
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
CxMatrixTmpl& CxMatrixTmpl::self()
{
	return (*this);
}
/*-------------------------------------------------*/
CxMatrixTlst
void CxMatrixTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::real() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Symmetric, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), ret_prop);

	blk::dns::get_real(
			this->prop().uplo(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld(), 
			ret.values(), ret.ld());

	return ret;
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::imag() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Skew, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), ret_prop);

	blk::dns::get_imag(
			this->prop().uplo(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld(), 
			ret.values(), ret.ld());

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxMatrixTmpl
#undef CxMatrixTlst
/*-------------------------------------------------*/
template class CxMatrix<complex_t>;
template class CxMatrix<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

