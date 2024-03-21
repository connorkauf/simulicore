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
#include "cla3p/dense/dns_cxvector.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/virtuals.hpp"

#include "cla3p/bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxVectorTmpl CxVector<T_Scalar>
#define CxVectorTlst template <typename T_Scalar>
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector()
{
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector(uint_t n)
	: CxVectorTmpl::XxVector(n)
{
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::~CxVector()
{
}
/*-------------------------------------------------*/
CxVectorTlst
const CxVectorTmpl& CxVectorTmpl::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl& CxVectorTmpl::self()
{
	return (*this);
}
/*-------------------------------------------------*/
CxVectorTlst
void CxVectorTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector(const VirtualVector<CxVectorTmpl>& v)
	: CxVectorTmpl::XxVector(v)
{ 
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl& CxVectorTmpl::operator=(const VirtualVector<CxVectorTmpl>& v)
{ 
	CxVectorTmpl::XxVector::operator=(v);
	return *this; 
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector(const VirtualProdMv<CxVectorTmpl>& v)
	: CxVectorTmpl::XxVector(v)
{ 
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl& CxVectorTmpl::operator=(const VirtualProdMv<CxVectorTmpl>& v)
{ 
	CxVectorTmpl::XxVector::operator=(v);
	return *this; 
}
/*-------------------------------------------------*/
CxVectorTlst
typename CxVectorTmpl::T_RVector CxVectorTmpl::real() const
{
	T_RVector ret(this->size());
	bulk::dns::get_real(uplo_t::Full, this->size(), 1, this->values(), this->size(), ret.values(), ret.size());
	return ret;
}
/*-------------------------------------------------*/
CxVectorTlst
typename CxVectorTmpl::T_RVector CxVectorTmpl::imag() const
{
	T_RVector ret(this->size());
	bulk::dns::get_imag(uplo_t::Full, this->size(), 1, this->values(), this->size(), ret.values(), ret.size());
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxVectorTmpl
#undef CxVectorTlst
/*-------------------------------------------------*/
template class CxVector<complex_t>;
template class CxVector<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

