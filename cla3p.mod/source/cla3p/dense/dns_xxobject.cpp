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
#include "cla3p/dense/dns_xxobject.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject<T_Scalar>
#define XxObjectTlst template <typename T_Scalar>
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject()
{
  defaults();
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject(std::size_t numElements)
{
	T_Scalar *vals = i_malloc<T_Scalar>(numElements);
	wrapper(vals, true);
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::~XxObject()
{
  clear();
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::defaults()
{
	setValues(nullptr);
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setValues(T_Scalar *vals)
{
	m_values = vals;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Scalar* XxObjectTmpl::values()
{
	return m_values;
}
/*-------------------------------------------------*/
XxObjectTlst
const T_Scalar* XxObjectTmpl::values() const
{
	return m_values;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	Ownership::clear();

	defaults();
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::wrapper(T_Scalar *vals, bool bind)
{
	clear();
	setValues(vals);
	setOwner(bind);
}
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
#define instantiate_xxobject(T_Scl) \
template class XxObject<T_Scl>
instantiate_xxobject(int_t);
instantiate_xxobject(real_t);
instantiate_xxobject(real4_t);
instantiate_xxobject(complex_t);
instantiate_xxobject(complex8_t);
#undef instantiate_xxobject
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
