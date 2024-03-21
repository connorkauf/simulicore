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
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"

#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/dns_io.hpp"
#include "cla3p/bulk/dns_math.hpp"

#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

#include "cla3p/support/utils.hpp"
#include "cla3p/checks/dns_checks.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"
#include "cla3p/checks/perm_checks.hpp"
#include "cla3p/checks/block_ops_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XiVector<T_Scalar,T_Vector>
#define XxVectorTlst template <typename T_Scalar, typename T_Vector>
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XiVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XiVector(uint_t n)
	: Meta1D(n), XxObject<T_Scalar>(n)
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XiVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XiVector(XxVectorTmpl&& other)
{
	other.moveTo(*this);
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl& XxVectorTmpl::operator=(XxVectorTmpl&& other)
{
	other.moveTo(*this);
	return *this;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::clear()
{
	Meta1D::clear();
	XxObject<T_Scalar>::clear();
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::fill(T_Scalar val)
{
	std::fill(this->values(), this->values() + size(), val);
}
/*-------------------------------------------------*/
XxVectorTlst
T_Scalar& XxVectorTmpl::operator()(uint_t i)
{
	if(i >= size()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(size(),i));
	} // out-of-bounds

	return (this->values())[i];
}
/*-------------------------------------------------*/
XxVectorTlst
const T_Scalar& XxVectorTmpl::operator()(uint_t i) const
{
	if(i >= size()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(size(),i));
	} // out-of-bounds

	return (this->values())[i];
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::copy() const
{
	T_Vector ret(size());
	std::copy(this->values(), this->values() + size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::rcopy()
{
	return T_Vector::wrap(size(), this->values(), false);
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::rcopy() const
{
	return T_Vector::wrap(size(), this->values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::move()
{
	T_Vector ret;
	moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
std::string XxVectorTmpl::info(const std::string& header) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(header, top, bottom);

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
void XxVectorTmpl::print(uint_t nsd) const
{
	bulk::dns::print(uplo_t::Full, size(), 1, this->values(), size(), nsd);
}
/*-------------------------------------------------*/
XxVectorTlst
std::string XxVectorTmpl::toString(uint_t nsd) const
{
	return bulk::dns::print_to_string(uplo_t::Full, size(), 1, this->values(), size(), nsd);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::wrapper(uint_t n, T_Scalar *vals, bool bind)
{
	dns_consistency_check(n, 1, vals, n);
	Meta1D::wrapper(n);
	XxObject<T_Scalar>::wrapper(vals, bind);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::moveTo(XxVectorTmpl& trg)
{
	if(this != &trg) {
		trg.wrapper(size(), this->values(), this->owner());
		this->unbind();
		clear();
	} // do not apply on self
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::init(uint_t n)
{
	T_Vector ret(n);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::wrap(uint_t n, T_Scalar *vals, bool bind)
{
	T_Vector ret;
	ret.wrapper(n, vals, bind);
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
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
/*-------------------------------------------------*/
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
	: XiVector<T_Scalar,T_Vector>(n)
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
VirtualVector<T_Vector> XxVectorTmpl::operator-() const
{
	VirtualVector<T_Vector> ret(this->self());
	ret.iscale(-1);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::iscale(T_Scalar val)
{
	bulk::dns::scale(uplo_t::Full, this->size(), 1, this->values(), this->size(), val);
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
void XxVectorTmpl::iconjugate()
{
	bulk::dns::conjugate(uplo_t::Full, this->size(), 1, this->values(), this->size());
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_RScalar XxVectorTmpl::normOne() const
{
	return bulk::dns::norm_one(
			prop_t::General,
			uplo_t::Full,
			this->size(),
			1,
			this->values(),
			this->size());
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_RScalar XxVectorTmpl::normInf() const
{
	return bulk::dns::norm_inf(
			prop_t::General,
			uplo_t::Full,
			this->size(),
			1,
			this->values(),
			this->size());
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(this->size(), this->values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::permuteLeft(const prm::PiMatrix& P) const
{
	T_Vector ret(this->size());

	perm_op_consistency_check(this->size(), 1, P.size(), 1);

	bulk::dns::permute(prop_t::General, uplo_t::Full, this->size(), 1, this->values(), this->size(), ret.values(), ret.size(), P.values(), nullptr);

	return ret;
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
	block_op_consistency_check(defaultProperty(), this->size(), 1, ibgn, 0, ni, 1);

	return T_Vector::wrap(ni, this->values() + ibgn, false);
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
{
	block_op_consistency_check(defaultProperty(), this->size(), 1, ibgn, 0, ni, 1);

	return T_Vector::wrap(ni, this->values() + ibgn);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::setBlock(uint_t ibgn, const XxVectorTmpl& src)
{
	T_Vector tmp = rblock(ibgn, src.size());
	std::copy(src.values(), src.values() + src.size(), tmp.values());
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
	return T_Matrix::wrap(this->size(), 1, this->values(), this->size(), false);
};
/*-------------------------------------------------*/
XxVectorTlst
Guard<typename XxVectorTmpl::T_Matrix> XxVectorTmpl::rmatrix() const 
{ 
	return T_Matrix::wrap(this->size(), 1, this->values(), this->size());
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::random(uint_t n, T_RScalar lo, T_RScalar hi)
{
	T_Vector ret(n);
	bulk::dns::rand(uplo_t::Full, ret.size(), 1, ret.values(), ret.size(), lo, hi);
	return ret;
}
/*-------------------------------------------------*/
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
#define instantiate_xxvector(T_Vec) \
template class XiVector<T_Vec::value_type,T_Vec>
instantiate_xxvector(prm::PiMatrix);
instantiate_xxvector(RdVector);
instantiate_xxvector(RfVector);
instantiate_xxvector(CdVector);
instantiate_xxvector(CfVector);
#undef instantiate_xxvector
/*-------------------------------------------------*/
#define instantiate_xxvector(T_Vec) \
template class XxVector<T_Vec::value_type,T_Vec>
instantiate_xxvector(RdVector);
instantiate_xxvector(RfVector);
instantiate_xxvector(CdVector);
instantiate_xxvector(CfVector);
#undef instantiate_xxvector
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
