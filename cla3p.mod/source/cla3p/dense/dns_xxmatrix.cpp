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
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"
#include "cla3p/checks/transp_checks.hpp"
#include "cla3p/linsol/dns_auto_lsolver.hpp"

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
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: XxObject<T_Scalar,T_Matrix>(nr, nc, nr, pr)
{
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::~XxMatrix()
{
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,j);
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw err::OutOfBounds(msg::IndexOutOfBounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,j);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::operator*(const XxMatrixTmpl& other) const
{
	T_Matrix ret(nrows(), other.ncols());

	ret = 0;
	ret.updateSelfWithScaledMatMat(1, op_t::N, *this, op_t::N, other);

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::nrows() const
{
	return this->rsize();
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::ncols() const
{
	return this->csize();
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::ld() const
{
	return this->lsize();
}
/*-------------------------------------------------*/
XxMatrixTlst
const Property& XxMatrixTmpl::prop() const
{
	return this->property();
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::info(const std::string& msg) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << BasicTypeTraits<T_Matrix>::type_name() << "\n";
	ss << "  Datatype............. " << BasicTypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << BasicTypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Number of rows....... " << nrows() << "\n";
	ss << "  Number of columns.... " << ncols() << "\n";
	ss << "  Leading dimension.... " << ld() << "\n";
	ss << "  Values............... " << this->values() << "\n";
	ss << "  Property............. " << prop() << "\n";
	ss << "  Owner................ " << bool2yn(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_RScalar XxMatrixTmpl::normMax() const
{ 
	return bulk::dns::norm_max(
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
	return bulk::dns::norm_fro(
			prop().type(), 
			prop().uplo(), 
			nrows(), 
			ncols(),
			this->values(), 
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::transpose() const
{
	transp_op_consistency_check(prop().type(), false);

	T_Matrix ret(ncols(), nrows());
	bulk::dns::transpose(nrows(), ncols(), this->values(), ld(), ret.values(), ret.ld());
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::general() const
{
	T_Matrix ret = this->copy();
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

		bulk::dns::sy2ge(prop().uplo(), ncols(), this->values(), ld());

	} else if(prop().isHermitian()) {

		bulk::dns::he2ge(prop().uplo(), ncols(), this->values(), ld());

	} else if(prop().isTriangular()) {

		bulk::dns::tr2ge(prop().uplo(), nrows(), ncols(), this->values(), ld());

	} else if(prop().isSkew()) {

		bulk::dns::sk2ge(prop().uplo(), ncols(), this->values(), ld());

	} else {

		throw err::Exception();

	} // property 

	bool bind = this->owner();
	this->unbind();

	*this = wrap(nrows(), ncols(), this->values(), ld(), bind);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeftRight(const PiMatrix& P, const PiMatrix& Q) const
{
	T_Matrix ret;
	this->gePermuteToLeftRight(ret, P, Q);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeft(const PiMatrix& P) const
{
	T_Matrix ret;
	this->gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteRight(const PiMatrix& Q) const
{
	T_Matrix ret;
	this->gePermuteToRight(ret, Q);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteMirror(const PiMatrix& P) const
{
	T_Matrix ret;
	this->xxPermuteToMirror(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::ipermuteLeftRight(const PiMatrix& P, const PiMatrix& Q) 
{ 
	this->gePermuteIpLeftRight(P, Q);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::ipermuteLeft(const PiMatrix& P) 
{ 
	this->gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::ipermuteRight(const PiMatrix& Q) 
{ 
	this->gePermuteIpRight(Q);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::ipermuteMirror(const PiMatrix& P) 
{ 
	this->xxPermuteIpMirror(P);
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
	return this->getBlockReference(ibgn, jbgn, ni, nj);
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	return this->getBlockReference(ibgn, jbgn, ni, nj);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setBlock(uint_t ibgn, uint_t jbgn, const XxMatrixTmpl& src)
{
	this->setBlockCopy(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::init(uint_t nr, uint_t nc, const Property& pr)
{
	T_Matrix ret(nr, nc, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::random(uint_t nr, uint_t nc, const Property& pr)
{
	T_Matrix ret = init(nr, nc, pr);
	bulk::dns::rand(ret.prop().uplo(), ret.nrows(), ret.ncols(), ret.values(), ret.ld());
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr)
{
	T_Matrix ret;
	ret.wrapper(nr, nc, ldv, vals, bind, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr)
{
	Guard<T_Matrix> ret = wrap(nr, nc, const_cast<T_Scalar*>(vals), ldv, false, pr);
	return ret;
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
	XxMatrixTmpl tmp = rblock(0, j, nrows(), 1);
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
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::updateSelfWithScaledMatMat(T_Scalar alpha,
		op_t opA, const XxMatrixTmpl& A,
		op_t opB, const XxMatrixTmpl& B)
{
	Operation _opA(opA);
	Operation _opB(opB);

	mat_x_mat_mult_check(
			A.prop(), A.nrows(), A.ncols(), _opA,
			B.prop(), B.nrows(), B.ncols(), _opB,
			prop(), 
			nrows(), 
			ncols());

	if(A.prop().isGeneral() && B.prop().isGeneral()) {

		uint_t k = (_opA.isTranspose() ? A.nrows() : A.ncols());

		bulk::dns::gem_x_gem(
				nrows(), 
				ncols(), 
				k, alpha, 
				opA, A.values(), A.ld(), 
				opB, B.values(), B.ld(), 
				1, 
				this->values(), ld());

	} else if(A.prop().isSymmetric() && B.prop().isGeneral()) {

		bulk::dns::sym_x_gem(A.prop().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				1, 
				this->values(), ld());

	} else if(A.prop().isHermitian() && B.prop().isGeneral()) {

		bulk::dns::hem_x_gem(
				A.prop().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				1, 
				this->values(), ld());

	} else if(A.prop().isGeneral() && B.prop().isSymmetric()) {

		bulk::dns::gem_x_sym(B.prop().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				1, 
				this->values(), ld());

	} else if(A.prop().isGeneral() && B.prop().isHermitian()) {

		bulk::dns::gem_x_hem(B.prop().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				1, 
				this->values(), ld());

	} else if(A.prop().isTriangular() && B.prop().isGeneral()) {

		XxMatrixTmpl tmp(nrows(), ncols(), defaultProperty());

		bulk::dns::trm_x_gem(A.prop().uplo(), opA, 
				nrows(), 
				ncols(), 
				B.nrows(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				tmp.values(), tmp.ld());

		this->updateSelfWithScaledOther(1, tmp);

	} else if(A.prop().isGeneral() && B.prop().isTriangular()) {

		XxMatrixTmpl tmp(nrows(), ncols(), defaultProperty());

		bulk::dns::gem_x_trm(B.prop().uplo(), opB, 
				nrows(), 
				ncols(), 
				A.nrows(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				tmp.values(), tmp.ld());

		this->updateSelfWithScaledOther(1, tmp);

	} else {

		throw err::Exception();

	} // property combos
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::replaceSelfWithScaledTriMat(T_Scalar alpha, 
		side_t sideA, op_t opA, const XxMatrixTmpl& A)
{
	Operation _opA(opA);

	trimat_mult_replace_check(sideA, 
			A.prop(), A.nrows(), A.ncols(), _opA, 
			prop(), nrows(), ncols());

	blas::trmm(
			static_cast<char>(sideA), A.prop().cuplo(), _opA.ctype(), 'N', 
			nrows(), ncols(), alpha, A.values(), A.ld(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::replaceSelfWithScaledInvTriMat(T_Scalar alpha, 
		side_t sideA, op_t opA, const XxMatrixTmpl& A)
{
	Operation _opA(opA);

	trimat_mult_replace_check(sideA, 
			A.prop(), A.nrows(), A.ncols(), _opA, 
			prop(), nrows(), ncols());

	blas::trsm(
			static_cast<char>(sideA), A.prop().cuplo(), _opA.ctype(), 'N', 
			nrows(), ncols(), alpha, A.values(), A.ld(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxMatrixTmpl
#undef XxMatrixTlst
/*-------------------------------------------------*/
template class XxMatrix<real_t,RdMatrix>;
template class XxMatrix<real4_t,RfMatrix>;
template class XxMatrix<complex_t,CdMatrix>;
template class XxMatrix<complex8_t,CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
