#ifndef CLA3P_DNS_XXMATRIX_HPP_
#define CLA3P_DNS_XXMATRIX_HPP_
/*-------------------------------------------------*/
#include "support/error.hpp"
#include "support/error_internal.hpp"
#include "support/utils.hpp"
#include "perm_matrix.hpp"
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
		ThisObjectType(prop_t::GENERAL, nr, nc, nr, false)
{
}
/*-------------------------------------------------*/
XxMatrix::XxMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nr, nc, nr, wipe)
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
XxMatrix XxMatrix::clone()
{
	XxMatrix ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::clone() const
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
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& XxMatrix::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
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
	return init(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::init(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.blankCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::zero(uint_t nr, uint_t nc) 
{ 
	return zero(prop_t::GENERAL, nr, nc) ;
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::zero(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.zeroCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::random(uint_t nr, uint_t nc) 
{ 
	return random(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::random(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	XxMatrix ret;
	ret.randomCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::wrap(uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv, false);
}
/*-------------------------------------------------*/
XxMatrix XxMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv, bool bind)
{
	XxMatrix ret;
	ret.wrapCreator(propcheck(ptype), nr, nc, vals, ldv, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::wrap(uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv);
}
/*-------------------------------------------------*/
XxMGuard XxMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	XxMGuard ret;
	ThisGuardType& trg = ret;
	trg = XxMatrix::wrap(propcheck(ptype), nr, nc, const_cast<ThisDataType*>(vals), ldv, false);
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
	return ThisGuardType::obj(); 
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
