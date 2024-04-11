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
#include "cla3p/dense/dns_rxvector.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define RxVectorTmpl RxVector<T_Scalar>
#define RxVectorTlst template <typename T_Scalar>
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector()
{
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector(uint_t n)
	: RxVectorTmpl::XxVector(n)
{
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::~RxVector()
{
}
/*-------------------------------------------------*/
RxVectorTlst
const RxVectorTmpl& RxVectorTmpl::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl& RxVectorTmpl::self()
{
	return (*this);
}
/*-------------------------------------------------*/
RxVectorTlst
void RxVectorTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector(const VirtualVector<RxVectorTmpl>& v)
	: RxVectorTmpl::XxVector(v)
{ 
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl& RxVectorTmpl::operator=(const VirtualVector<RxVectorTmpl>& v)
{ 
	RxVectorTmpl::XxVector::operator=(v);
	return *this; 
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector(const VirtualProdMv<RxMatrix<T_Scalar>,RxVectorTmpl>& v)
	: RxVectorTmpl::XxVector(v)
{ 
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl& RxVectorTmpl::operator=(const VirtualProdMv<RxMatrix<T_Scalar>,RxVectorTmpl>& v)
{ 
	RxVectorTmpl::XxVector::operator=(v);
	return *this; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxVectorTmpl
#undef RxVectorTlst
/*-------------------------------------------------*/
template class RxVector<real_t>;
template class RxVector<real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

