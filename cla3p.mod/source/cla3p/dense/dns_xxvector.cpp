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
#include "cla3p/checks/dot_checks.hpp"
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
T_Vector XxVectorTmpl::random(uint_t n)
{
	T_Vector ret(n);
	bulk::dns::rand(uplo_t::Full, ret.rsize(), ret.csize(), ret.values(), ret.lsize());
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
XxVectorTlst
T_Scalar XxVectorTmpl::calcDotProductWith(const XxVectorTmpl& Y) const
{
	dot_product_consistency_check(size(), Y.size());
	return blas::dot(size(), this->values(), 1, Y.values(), 1);
}
/*-------------------------------------------------*/
XxVectorTlst
T_Scalar XxVectorTmpl::calcConjugateDotProductWith(const XxVectorTmpl& Y) const
{
	dot_product_consistency_check(size(), Y.size());
	return blas::dotc(size(), this->values(), 1, Y.values(), 1);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::updateSelfWithScaledMatVec(T_Scalar alpha, op_t opA, const XxMatrix<T_Scalar,T_Matrix>& A, const XxVectorTmpl& X)
{
	Operation _opA(opA);

	mat_x_vec_mult_check(_opA, A.prop(), A.nrows(), A.ncols(), X.size(), size());

	if(A.prop().isGeneral()) {

		bulk::dns::gem_x_vec(opA, A.nrows(), A.ncols(), alpha, A.values(), A.ld(), X.values(), 1, this->values());

	} else if(A.prop().isSymmetric()) {

		bulk::dns::sym_x_vec(A.prop().uplo(), A.ncols(), alpha, A.values(), A.ld(), X.values(), 1, this->values());

	} else if(A.prop().isHermitian()) {

		bulk::dns::hem_x_vec(A.prop().uplo(), A.ncols(), alpha, A.values(), A.ld(), X.values(), 1, this->values());

	} else if(A.prop().isTriangular()) {

		T_Vector tmp(size());
		bulk::dns::trm_x_vec(A.prop().uplo(), opA, A.nrows(), A.ncols(), alpha, A.values(), A.ld(), X.values(), tmp.values());
		this->updateSelfWithScaledOther(1, tmp);

	} else {

		throw err::Exception();

	} // property 
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::replaceSelfWithTriVec(op_t opA, const XxMatrix<T_Scalar,T_Matrix>& A)
{
	Operation _opA(opA);

	trivec_mult_replace_check(A.prop(), A.nrows(), A.ncols(), _opA, size());

	blas::trmv(A.prop().cuplo(), _opA.ctype(), 'N', A.ncols(), A.values(), A.ld(), this->values(), 1);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::replaceSelfWithInvTriVec(op_t opA, const XxMatrix<T_Scalar,T_Matrix>& A)
{
	Operation _opA(opA);

	trivec_mult_replace_check(A.prop(), A.nrows(), A.ncols(), _opA, size());

	blas::trsv(A.prop().cuplo(), _opA.ctype(), 'N', A.ncols(), A.values(), A.ld(), this->values(), 1);
}
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
