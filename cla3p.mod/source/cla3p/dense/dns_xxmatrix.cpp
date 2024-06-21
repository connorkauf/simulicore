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
#include "cla3p/dense/dns_xxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"

#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/bulk/dns_io.hpp"

#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/support/utils.hpp"

#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/checks/dns_checks.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"
#include "cla3p/checks/transp_checks.hpp"
#include "cla3p/checks/perm_checks.hpp"
#include "cla3p/checks/block_ops_checks.hpp"
#include "cla3p/checks/hermitian_coeff_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxMatrixTmpl XxMatrix<T_Scalar,T_Matrix>
#define XxMatrixTlst template <typename T_Scalar, typename T_Matrix>
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix()
{
	defaults();
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: MatrixMeta(nr, nc, sanitizeProperty<T_Scalar>(pr)), XxObject<T_Scalar>(nr * nc)
{
	if(nr && nc) {
		setLd(nr);
		checker();
	} else {
		clear();
	} // nr/nc
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::~XxMatrix()
{
	clear();
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(const XxMatrixTmpl& other)
	: XxMatrix(other.nrows(), other.ncols(), other.prop())
{
	other.copyToExisting(*this);
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl& XxMatrixTmpl::operator=(const XxMatrixTmpl& other)
{
	if(!(*this)) {
		*this = init(other.nrows(), other.ncols(), other.prop());
	}
	other.copyToExisting(*this);
	return *this;
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(XxMatrixTmpl&& other)
{
	other.moveTo(*this);
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl& XxMatrixTmpl::operator=(XxMatrixTmpl&& other)
{
	other.moveTo(*this);
	return *this;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::defaults()
{
	setLd(0);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setLd(uint_t ld)
{
	m_ld = ld;
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::ld() const
{
	return m_ld;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::clear()
{
	MatrixMeta::clear();
	XxObject<T_Scalar>::clear();
	defaults();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::fill(T_Scalar val)
{
	blk::dns::fill(prop().uplo(), nrows(), ncols(), this->values(), ld(), val);
	blk::dns::set_diag_zeros(prop().type(), ncols(), this->values(), ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return blk::dns::entry(ld(), this->values(), i, j);
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return blk::dns::entry(ld(), this->values(), i, j);
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::operator-() const
{
	return VirtualMatrix<T_Matrix>(this->self()).scale(-1);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::copy() const
{
	T_Matrix ret(nrows(), ncols(), prop());
	copyToExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::rcopy()
{
	return T_Matrix::wrap(nrows(), ncols(), this->values(), ld(), false, prop());
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::rcopy() const
{
	return T_Matrix::wrap(nrows(), ncols(), this->values(), ld(), prop());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::move()
{
	T_Matrix ret;
	moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::print(uint_t nsd) const
{
	blk::dns::print(prop().uplo(), nrows(), ncols(), this->values(), ld(), nsd);
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::toString(uint_t nsd) const
{
	return blk::dns::print_to_string(prop().uplo(), nrows(), ncols(), this->values(), ld(), nsd);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::iscale(T_Scalar val)
{
	hermitian_coeff_check(prop(), val);

	blk::dns::scale(
			prop().uplo(),
			nrows(),
			ncols(),
			this->values(),
			ld(), val);
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::info(const std::string& header) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(header, top, bottom);

	std::ostringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << TypeTraits<T_Matrix>::type_name() << "\n";
	ss << "  Datatype............. " << TypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << TypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Number of rows....... " << nrows() << "\n";
	ss << "  Number of columns.... " << ncols() << "\n";
	ss << "  Leading dimension.... " << ld() << "\n";
	ss << "  Values............... " << this->values() << "\n";
	ss << "  Property............. " << prop() << "\n";
	ss << "  Owner................ " << boolToYesNo(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::transpose() const
{
	return VirtualMatrix<T_Matrix>(this->self()).transpose();
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::ctranspose() const
{
	return VirtualMatrix<T_Matrix>(this->self()).ctranspose();
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::conjugate() const
{
	return VirtualMatrix<T_Matrix>(this->self()).conjugate();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::iconjugate()
{
	blk::dns::conjugate(prop().uplo(), nrows(), ncols(), this->values(), ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_RScalar XxMatrixTmpl::normOne() const
{
	return blk::dns::norm_one(
			prop().type(),
			prop().uplo(),
			nrows(),
			ncols(),
			this->values(),
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_RScalar XxMatrixTmpl::normInf() const
{
	return blk::dns::norm_inf(
			prop().type(),
			prop().uplo(),
			nrows(),
			ncols(),
			this->values(),
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_RScalar XxMatrixTmpl::normMax() const
{
	return blk::dns::norm_max(
			prop().type(),
			prop().uplo(),
			nrows(),
			ncols(),
			this->values(),
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_RScalar XxMatrixTmpl::normFro() const
{
	return blk::dns::norm_fro(
			prop().type(),
			prop().uplo(),
			nrows(),
			ncols(),
			this->values(),
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::general() const
{
	T_Matrix ret = self();
	ret.igeneral();
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::igeneral()
{
	if(prop().isGeneral()) {

		return;

	} else if(prop().isSymmetric()) {

		blk::dns::sy2ge(prop().uplo(), ncols(), this->values(), ld());

	} else if(prop().isHermitian()) {

		blk::dns::he2ge(prop().uplo(), ncols(), this->values(), ld());

	} else if(prop().isTriangular()) {

		blk::dns::tr2ge(prop().uplo(), nrows(), ncols(), this->values(), ld());

	} else if(prop().isSkew()) {

		blk::dns::sk2ge(prop().uplo(), ncols(), this->values(), ld());

	} else {

		throw err::Exception();

	} // property 

	bool bind = this->owner();
	this->unbind();

	*this = wrap(nrows(), ncols(), this->values(), ld(), bind);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeftRight(const prm::PiMatrix& P, const prm::PiMatrix& Q) const
{
	T_Matrix ret(nrows(), ncols(), prop());
	permuteLeftRight(P, Q, ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::permuteLeftRight(const prm::PiMatrix& P, const prm::PiMatrix& Q, XxMatrix<T_Scalar,T_Matrix>& trg) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), Q.size());
	similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());
	blk::dns::permute(prop().type(), prop().uplo(), nrows(), ncols(), this->values(), ld(), trg.values(), trg.ld(), P.values(), Q.values());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeft(const prm::PiMatrix& P) const
{
	T_Matrix ret(nrows(), ncols(), prop());
	permuteLeft(P, ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::permuteLeft(const prm::PiMatrix& P, XxMatrix<T_Scalar,T_Matrix>& trg) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), ncols());
	similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());
	blk::dns::permute(prop().type(), prop().uplo(), nrows(), ncols(), this->values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteRight(const prm::PiMatrix& Q) const
{
	T_Matrix ret(nrows(), ncols(), prop());
	permuteRight(Q, ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::permuteRight(const prm::PiMatrix& Q, XxMatrix<T_Scalar,T_Matrix>& trg) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), nrows(), Q.size());
	similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());
	blk::dns::permute(prop().type(), prop().uplo(), nrows(), ncols(), this->values(), ld(), trg.values(), trg.ld(), nullptr, Q.values());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteMirror(const prm::PiMatrix& P) const
{
	T_Matrix ret(nrows(), ncols(), prop());
	permuteMirror(P, ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::permuteMirror(const prm::PiMatrix& P, XxMatrix<T_Scalar,T_Matrix>& trg) const
{
	perm_op_consistency_check(nrows(), ncols(), P.size(), P.size());
	similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());

	prm::PiMatrix iP;
	if(prop().isGeneral())
		iP = P.inverse();

	blk::dns::permute(prop().type(), prop().uplo(), nrows(), ncols(), this->values(), ld(), trg.values(), trg.ld(), P.values(), iP.values());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	return rblock(ibgn,jbgn,ni,nj).get().copy();
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	Property pr = block_op_consistency_check(
			prop(), nrows(), ncols(),
			ibgn, jbgn, ni, nj);
	
	T_Scalar *p_vij = blk::dns::ptrmv(ld(), this->values(), ibgn, jbgn);
	
	return T_Matrix::wrap(ni, nj, p_vij, ld(), false, pr);
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Property pr = block_op_consistency_check(
			prop(), nrows(), ncols(),
			ibgn, jbgn, ni, nj);
	
	const T_Scalar *p_vij = blk::dns::ptrmv(ld(), this->values(), ibgn, jbgn);
	
	return T_Matrix::wrap(ni, nj, p_vij, ld(), pr);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setBlock(uint_t ibgn, uint_t jbgn, const XxMatrixTmpl& src)
{
	T_Matrix tmp = rblock(ibgn, jbgn, src.nrows(), src.ncols());
	blk::dns::copy(src.prop().uplo(), src.nrows(), src.ncols(), src.values(), src.ld(), tmp.values(), tmp.ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_Vector XxMatrixTmpl::column(uint_t j) const
{ 
	return rcolumn(j).get().copy();
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_Vector XxMatrixTmpl::rcolumn(uint_t j)
{
	T_Matrix tmp = rblock(0, j, nrows(), 1);
	return T_Vector::wrap(tmp.nrows(), tmp.values(), false);
};
/*-------------------------------------------------*/
XxMatrixTlst
Guard<typename XxMatrixTmpl::T_Vector> XxMatrixTmpl::rcolumn(uint_t j) const 
{ 
	Guard<T_Matrix> tmp = rblock(0, j, nrows(), 1);
	return T_Vector::wrap(tmp.get().nrows(), tmp.get().values());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::init(uint_t nr, uint_t nc, const Property& pr)
{
	T_Matrix ret(nr, nc, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::random(uint_t nr, uint_t nc, const Property& pr, T_RScalar lo, T_RScalar hi)
{
	T_Matrix ret(nr, nc, pr);
	blk::dns::rand(ret.prop().uplo(), ret.nrows(), ret.ncols(), ret.values(), ret.ld(), lo, hi);
	blk::dns::set_diag_zeros(ret.prop().type(), ret.ncols(), ret.values(), ret.ld());
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr)
{
	T_Matrix ret;
	ret.wrapper(nr, nc, vals, ldv, bind, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr)
{
	Guard<T_Matrix> ret(wrap(nr, nc, const_cast<T_Scalar*>(vals), ldv, false, pr));
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::wrapper(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr)
{
	if(nr && nc) {

		MatrixMeta::wrapper(nr, nc, sanitizeProperty<T_Scalar>(pr));
		XxObject<T_Scalar>::wrapper(vals, bind);
		setLd(ldv);
		checker();

	} else {

		clear();

	} // nr/nc
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::checker() const
{
	dns_consistency_check(prop(), nrows(), ncols(), this->values(), ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::moveTo(XxMatrixTmpl& trg)
{
	if(this != &trg) {

		if(nrows() == trg.nrows() && ncols() == trg.ncols() && prop() == trg.prop()) {
			copyToExisting(trg);
		} else {
			trg.wrapper(nrows(), ncols(), this->values(), ld(), this->owner(), prop());
		} // similar

		this->unbind();
		clear();

	} // do not apply on self
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::copyToExisting(XxMatrixTmpl& trg) const
{
	if(this != &trg) {
		similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());
		blk::dns::copy(prop().uplo(), nrows(), ncols(), this->values(), ld(), trg.values(), trg.ld());
	} // do not apply on self
}
/*-------------------------------------------------*/
#undef XxMatrixTmpl
#undef XxMatrixTlst
/*-------------------------------------------------*/
#define instantiate_xxmatrix(T_Mat) \
template class XxMatrix<T_Mat::value_type,T_Mat>
instantiate_xxmatrix(RdMatrix);
instantiate_xxmatrix(RfMatrix);
instantiate_xxmatrix(CdMatrix);
instantiate_xxmatrix(CfMatrix);
#undef instantiate_xxmatrix
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
