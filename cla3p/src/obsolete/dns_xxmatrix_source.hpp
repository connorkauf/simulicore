#ifndef CLA3P_DNS_XXMATRIX_HPP_
#define CLA3P_DNS_XXMATRIX_HPP_
/*-------------------------------------------------*/
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../perms/perm_matrix.hpp"
/*-------------------------------------------------*/
//
//
// Common functionality for floating point & integer dense matrices
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
XxMatrix::XxMatrix()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
XxMatrix::XxMatrix(uint_t nr, uint_t nc)
	:
		UniversalConstructor(),
		ThisObjectType(Property(prop_t::GENERAL,uplo_t::F), nr, nc, nr, false)
{
}
/*-------------------------------------------------*/
XxMatrix::XxMatrix(const Property& pr, uint_t nr, uint_t nc, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(pr), nr, nc, nr, wipe)
{
}
/*-------------------------------------------------*/
XxMatrix::~XxMatrix()
{
}
/*-------------------------------------------------*/
XxMatrix::XxMatrix(XxMatrix&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
XxMatrix& XxMatrix::operator=(XxMatrix&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t XxMatrix::nrows() const { return rsize(); }
uint_t XxMatrix::ncols() const { return csize(); }
/*-------------------------------------------------*/
uint_t          XxMatrix::ld  () const { return ThisObjectType::ld  (); }
const Property& XxMatrix::prop() const { return ThisObjectType::prop(); }
/*-------------------------------------------------*/
void XxMatrix::scale(ThisDataType coeff)
{
	ThisObjectType::scaleWith(coeff);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::copy() const 
{ 
	XxMatrix ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::move()
{ 
	XxMatrix ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::rcopy()
{
	XxMatrix ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::rcopy() const
{
	XxMGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
std::string XxMatrix::info(const std::string& msg) const
{ 
	return ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
ThisDataType& XxMatrix::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& XxMatrix::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrix XxMatrix::transpose() const
{
	XxMatrix ret;
	ThisObjectType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::general() const
{
	XxMatrix ret;
	ThisObjectType::convertToGeneral(ret);
	return ret.move();
}
/*-------------------------------------------------*/
void XxMatrix::igeneral()
{
	ThisObjectType::convertToGeneralIp();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::permute(const PermMatrix& P, const PermMatrix& Q) const
{
	XxMatrix ret;
	ThisObjectType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::permuteLeft(const PermMatrix& P) const
{
	XxMatrix ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::permuteRight(const PermMatrix& Q) const
{
	XxMatrix ret;
	ThisObjectType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::permuteMirror(const PermMatrix& P) const
{
	XxMatrix ret;
	ThisObjectType::xxPermuteToMirror(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void XxMatrix::ipermute      (const PermMatrix& P, const PermMatrix& Q) { return ThisObjectType::gePermuteIp      (P, Q); }
void XxMatrix::ipermuteLeft  (const PermMatrix& P                     ) { return ThisObjectType::gePermuteIpLeft  (P);    }
void XxMatrix::ipermuteRight (const PermMatrix& Q                     ) { return ThisObjectType::gePermuteIpRight (Q);    }
void XxMatrix::ipermuteMirror(const PermMatrix& P                     ) { return ThisObjectType::xxPermuteIpMirror(P);    }
/*-------------------------------------------------*/
XxMatrix XxMatrix::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	XxMatrix ret;
	ThisObjectType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	XxMatrix ret;
	ThisObjectType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	XxMGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<XxMatrix&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void XxMatrix::setBlock(uint_t ibgn, uint_t jbgn, const XxMatrix& src)
{
	ThisObjectType::setBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrix XxMatrix::init(uint_t nr, uint_t nc) 
{ 
	Property pr(prop_t::GENERAL,uplo_t::F);
	return init(pr, nr, nc);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::init(const Property& pr, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.blankCreator(propcheck(pr), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::zero(uint_t nr, uint_t nc) 
{ 
	Property pr(prop_t::GENERAL,uplo_t::F);
	return zero(pr, nr, nc) ;
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::zero(const Property& pr, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.zeroCreator(propcheck(pr), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::random(uint_t nr, uint_t nc) 
{ 
	Property pr(prop_t::GENERAL,uplo_t::F);
	return random(pr, nr, nc);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::random(const Property& pr, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.randomCreator(propcheck(pr), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::wrap(uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv)
{
	Property pr(prop_t::GENERAL,uplo_t::F);
	return wrap(pr, nr, nc, vals, ldv, false);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv, bool bind)
{
	XxMatrix ret;
	ret.wrapCreator(propcheck(pr), nr, nc, vals, ldv, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::wrap(uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	Property pr(prop_t::GENERAL,uplo_t::F);
	return wrap(pr, nr, nc, vals, ldv);
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	XxMGuard ret;
	ThisGuardType& trg = ret;
	trg = XxMatrix::wrap(propcheck(pr), nr, nc, const_cast<ThisDataType*>(vals), ldv, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMGuard::XxMGuard()
{
}
/*-------------------------------------------------*/
XxMGuard::~XxMGuard()
{
}
/*-------------------------------------------------*/
XxMGuard::XxMGuard(const XxMGuard& other)
	:ThisGuardType(other)
{
}
/*-------------------------------------------------*/
XxMGuard& XxMGuard::operator=(const XxMGuard& other)
{
	ThisGuardType::operator=(other);
	return *this;
}
/*-------------------------------------------------*/
const XxMatrix& XxMGuard::mat() const
{ 
	return ThisGuardType::get(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
#endif // CLA3P_DNS_XXMATRIX_HPP_
