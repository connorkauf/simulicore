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
#include "cla3p/dense/dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XxVector<T_Scalar,T_Vector>
#define XxVectorTlst template <typename T_Scalar, typename T_Vector>
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector(uint_t n)
	: XxObject<T_Scalar,T_Vector>(n, 1, n, defaultProperty())
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
T_Scalar& XxVectorTmpl::operator()(uint_t i)
{
	if(i >= size()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
XxVectorTlst
const T_Scalar& XxVectorTmpl::operator()(uint_t i) const
{
	if(i >= size()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
XxVectorTlst
uint_t XxVectorTmpl::size() const
{
	return this->rsize();
}
/*-------------------------------------------------*/
XxVectorTlst
std::string XxVectorTmpl::info(const std::string& msg) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::ostringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << TypeTraits<T_Vector>::type_name() << "\n";
	ss << "  Datatype............. " << TypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << TypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Size................. " << size() << "\n";
	ss << "  Values............... " << this->values() << "\n";
	ss << "  Owner................ " << bool2yn(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxVectorTlst
VirtualVector<T_Vector> XxVectorTmpl::transpose() const
{
	VirtualVector<T_Vector> ret(this->self());
	ret.itranspose();
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
VirtualVector<T_Vector> XxVectorTmpl::ctranspose() const
{
	VirtualVector<T_Vector> ret(this->self());
	ret.ictranspose();
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
VirtualVector<T_Vector> XxVectorTmpl::conjugate() const
{
	VirtualVector<T_Vector> ret(this->self());
	ret.iconjugate();
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(size(), this->values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::permuteLeft(const PiMatrix& P) const
{
	T_Vector ret;
	this->gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::ipermuteLeft(const PiMatrix& P) 
{ 
	this->gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::block(uint_t ibgn, uint_t ni) const
{
	return rblock(ibgn,ni).get().copy();
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::rblock(uint_t ibgn, uint_t ni)
{
	return this->getBlockReference(ibgn, 0, ni, 1);
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
{
	return this->getBlockReference(ibgn, 0, ni, 1);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::setBlock(uint_t ibgn, const XxVectorTmpl& src)
{
	this->setBlockCopy(src, ibgn, 0);
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_Matrix XxVectorTmpl::matrix() const
{ 
	return rmatrix().get().copy();
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_Matrix XxVectorTmpl::rmatrix()
{
	return T_Matrix::wrap(size(), 1, this->values(), this->lsize(), false);
};
/*-------------------------------------------------*/
XxVectorTlst
Guard<typename XxVectorTmpl::T_Matrix> XxVectorTmpl::rmatrix() const 
{ 
	return T_Matrix::wrap(size(), 1, this->values(), this->lsize());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::init(uint_t n)
{
	T_Vector ret(n);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::random(uint_t n, T_RScalar lo, T_RScalar hi)
{
	T_Vector ret(n);
	bulk::dns::rand(uplo_t::Full, ret.rsize(), ret.csize(), ret.values(), ret.lsize(), lo, hi);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::wrap(uint_t n, T_Scalar *vals, bool bind)
{
	T_Vector ret;
	ret.wrapper(n, 1, n, vals, bind, defaultProperty());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::wrap(uint_t n, const T_Scalar *vals)
{
	Guard<T_Vector> ret(wrap(n, const_cast<T_Scalar*>(vals), false));
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
template class XxVector<real_t,RdVector>;
template class XxVector<real4_t,RfVector>;
template class XxVector<complex_t,CdVector>;
template class XxVector<complex8_t,CfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
