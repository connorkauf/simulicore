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
#if 0
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject2<T_Scalar,T_Object>
#define XxObjectTlst template <typename T_Scalar, typename T_Object>
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject2()
{
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject2(uint_t nr, uint_t nc, uint_t nl, const Property& pr)
	: Array2D<T_Scalar>(nr, nc, nl, pr)
{
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::~XxObject2()
{
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::operator-() const
{
	T_Object ret = this->copy();
	ret.iscale(-1);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::copy() const
{
	T_Object ret;
	this->copyTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::rcopy()
{
	T_Object ret;
	this->copyToShallow(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_Object> XxObjectTmpl::rcopy() const
{
	T_Object tmp;
	const_cast<XxObjectTmpl&>(*this).copyToShallow(tmp);
	Guard<T_Object> ret(tmp);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::move()
{
	T_Object ret;
	this->moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::iscale(T_Scalar val)
{
	hermitian_coeff_check(this->property(), val);

	bulk::dns::scale(
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize(), val);
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::iconjugate()
{
	bulk::dns::conjugate(
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normOne() const
{ 
	return bulk::dns::norm_one(
			this->property().type(),
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(
			this->property().type(),
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normMax() const
{ 
	return bulk::dns::norm_max(
			this->property().type(), 
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normFro() const
{ 
	return bulk::dns::norm_fro(
			this->property().type(), 
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Guard<T_Object> tmp = getBlockReference(ibgn, jbgn, ni, nj);
	return tmp.get().copy();
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	Property pr = block_op_consistency_check(
			this->property(),
			this->rsize(),
			this->csize(),
			ibgn, jbgn, ni, nj);
	
	T_Scalar *p_vij = bulk::dns::ptrmv(
			this->lsize(),
			this->values(),
			ibgn, jbgn);
	
	T_Object ret;
	ret.wrapper(ni, nj, this->lsize(), p_vij, false, pr);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_Object> XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	T_Object tmp = const_cast<XxObjectTmpl&>(*this).getBlockReference(ibgn, jbgn, ni, nj);
	Guard<T_Object> ret(tmp);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setBlockCopy(const XxObjectTmpl& src, uint_t ibgn, uint_t jbgn)
{
	T_Object tmp = getBlockReference(ibgn, jbgn, src.rsize(), src.csize());
	src.copyToAllocated(tmp);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
template class XxObject2<real_t,RdMatrix>;
template class XxObject2<real4_t,RfMatrix>;
template class XxObject2<complex_t,CdMatrix>;
template class XxObject2<complex8_t,CfMatrix>;
#endif // 0 FIXME: DELETE
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
