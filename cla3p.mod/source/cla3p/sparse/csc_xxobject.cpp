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
#include "cla3p/sparse/csc_xxobject.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace csc {
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject<T_Int,T_Scalar>
#define XxObjectTlst template <typename T_Int, typename T_Scalar>
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject()
{
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject(uint_t nc, uint_t nz)
{
	T_Int    *cptr = i_malloc<T_Int>(nc+1);
	T_Int    *ridx = i_malloc<T_Int>(nz);
	T_Scalar *vals = i_malloc<T_Scalar>(nz);

	cptr[nc] = nz;

	wrapper(cptr, ridx, vals, true);
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::~XxObject()
{
  clear();
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setColptr(T_Int *cptr)
{
	m_colptr = cptr;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setRowidx(T_Int *ridx)
{
	m_rowidx = ridx;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setValues(T_Scalar *vals)
{
	m_values = vals;
}
/*-------------------------------------------------*/
XxObjectTlst
const T_Int* XxObjectTmpl::colptr() const
{
  return m_colptr;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Int* XxObjectTmpl::colptr()
{
  return m_colptr;
}
/*-------------------------------------------------*/
XxObjectTlst
const T_Int* XxObjectTmpl::rowidx() const
{
  return m_rowidx;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Int* XxObjectTmpl::rowidx()
{
  return m_rowidx;
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
		i_free(colptr());
		i_free(rowidx());
		i_free(values());
	} // owner

	Ownership::clear();
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::wrapper(T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind)
{
	clear();
	setColptr(cptr);
	setRowidx(ridx);
	setValues(vals);
	setOwner(bind);
}
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
#define instantiate_xxobject(T_Scl) \
template class XxObject<int_t,T_Scl>
instantiate_xxobject(real_t);
instantiate_xxobject(real4_t);
instantiate_xxobject(complex_t);
instantiate_xxobject(complex8_t);
#undef instantiate_xxobject
/*-------------------------------------------------*/
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/
