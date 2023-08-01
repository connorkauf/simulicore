// this file inc
#include "dns_xxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../perms.hpp"
#include "../bulk/dns.hpp"
#include "../bulk/dns_math.hpp"
#include "../bulk/dns_io.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../checks/all_checks.hpp"

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
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,j);
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
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

		throw Exception();

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
void XxMatrixTmpl::setBlock(uint_t ibgn, uint_t jbgn, const T_Matrix& src)
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
		const Operation& opA, const T_Matrix& otherA,
		const Operation& opB, const T_Matrix& otherB)
{
	mat_x_mat_mult_check(
			otherA.property(), otherA.nrows(), otherA.ncols(), opA,
			otherB.property(), otherB.nrows(), otherB.ncols(), opB,
			this->property(), 
			nrows(), 
			ncols());

	if(otherA.property().isGeneral() && otherB.property().isGeneral()) {

		uint_t k = (opA.isTranspose() ? otherA.nrows() : otherA.ncols());

		bulk::dns::gem_x_gem(
				nrows(), 
				ncols(), 
				k, alpha, 
				opA.type(), otherA.values(), otherA.lsize(), 
				opB.type(), otherB.values(), otherB.lsize(), 
				1, 
				this->values(), 
				this->lsize());

	} else if(otherA.property().isSymmetric() && otherB.property().isGeneral()) {

		bulk::dns::sym_x_gem(otherA.property().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				otherA.values(), otherA.lsize(), 
				otherB.values(), otherB.lsize(), 
				1, 
				this->values(), 
				this->lsize());

	} else if(otherA.property().isHermitian() && otherB.property().isGeneral()) {

		bulk::dns::hem_x_gem(
				otherA.property().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				otherA.values(), otherA.lsize(), 
				otherB.values(), otherB.lsize(), 
				1, 
				this->values(), 
				this->lsize());

	} else if(otherA.property().isGeneral() && otherB.property().isSymmetric()) {

		bulk::dns::gem_x_sym(otherB.property().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				otherB.values(), otherB.lsize(), 
				otherA.values(), otherA.lsize(), 
				1, 
				this->values(), 
				this->lsize());

	} else if(otherA.property().isGeneral() && otherB.property().isHermitian()) {

		bulk::dns::gem_x_hem(otherB.property().uplo(), 
				nrows(), 
				ncols(), 
				alpha, 
				otherB.values(), otherB.lsize(), 
				otherA.values(), otherA.lsize(), 
				1, 
				this->values(), 
				this->lsize());

	} else if(otherA.property().isTriangular() && otherB.property().isGeneral()) {

		XxMatrixTmpl tmp(nrows(), ncols(), defaultProperty());

		bulk::dns::trm_x_gem(otherA.property().uplo(), opA.type(), 
				nrows(), 
				ncols(), 
				otherB.nrows(), 
				alpha, 
				otherA.values(), otherA.lsize(), 
				otherB.values(), otherB.lsize(), 
				tmp.values(), tmp.lsize());

		this->updateSelfWithScaledOther(1, tmp);

	} else if(otherA.property().isGeneral() && otherB.property().isTriangular()) {

		XxMatrixTmpl tmp(nrows(), ncols(), defaultProperty());

		bulk::dns::gem_x_trm(otherB.property().uplo(), opB.type(), 
				nrows(), 
				ncols(), 
				otherA.nrows(), 
				alpha, 
				otherB.values(), otherB.lsize(), 
				otherA.values(), otherA.lsize(), 
				tmp.values(), tmp.lsize());

		this->updateSelfWithScaledOther(1, tmp);

	} else {

		throw Exception();

	} // property combos
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
