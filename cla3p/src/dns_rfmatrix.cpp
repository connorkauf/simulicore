// this file inc
#include "dns_rfmatrix.hpp"

// system

// 3rd

// cla3p
#include "support/error.hpp"
#include "support/error_internal.hpp"
#include "support/utils.hpp"
#include "perm_matrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = real4_t;
using ThisRealType = real4_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RfMatrix>;
/*-------------------------------------------------*/
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::SINGLE)
/*-------------------------------------------------*/
static prop_t propcheck(prop_t ptype)
{
	return (ptype == prop_t::HERMITIAN ? prop_t::SYMMETRIC : ptype);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RfMatrix::RfMatrix()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
RfMatrix::RfMatrix(uint_t nr, uint_t nc)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, nr, nc, nr, false)
{
}
/*-------------------------------------------------*/
RfMatrix::RfMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nr, nc, nr, wipe)
{
}
/*-------------------------------------------------*/
RfMatrix::~RfMatrix()
{
}
/*-------------------------------------------------*/
RfMatrix::RfMatrix(RfMatrix&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
RfMatrix& RfMatrix::operator=(RfMatrix&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t RfMatrix::nrows() const { return rsize(); }
uint_t RfMatrix::ncols() const { return csize(); }
/*-------------------------------------------------*/
uint_t          RfMatrix::ld  () const { return ThisObjectType::ld  (); }
const Property& RfMatrix::prop() const { return ThisObjectType::prop(); }
/*-------------------------------------------------*/
void RfMatrix::scale(ThisDataType coeff)
{
	ThisObjectType::scaleWith(coeff);
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::copy() const 
{ 
	RfMatrix ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::move()
{ 
	RfMatrix ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::clone()
{
	RfMatrix ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RfMGuard RfMatrix::clone() const
{
	RfMGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
std::string RfMatrix::info(const std::string& msg) const
{ 
	return ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
ThisRealType RfMatrix::normOne() const { return ThisObjectType::normOne(); }
ThisRealType RfMatrix::normInf() const { return ThisObjectType::normInf(); }
ThisRealType RfMatrix::normMax() const { return ThisObjectType::normMax(); }
ThisRealType RfMatrix::normFro() const { return ThisObjectType::normFro(); }
/*-------------------------------------------------*/
ThisDataType& RfMatrix::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& RfMatrix::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RfMatrix RfMatrix::transpose() const
{
	RfMatrix ret;
	ThisObjectType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::permute(const PermMatrix& P, const PermMatrix& Q) const
{
	RfMatrix ret;
	ThisObjectType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::permuteLeft(const PermMatrix& P) const
{
	RfMatrix ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::permuteRight(const PermMatrix& Q) const
{
	RfMatrix ret;
	ThisObjectType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::permuteMirror(const PermMatrix& P) const
{
	RfMatrix ret;
	ThisObjectType::xxPermuteToMirror(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void RfMatrix::ipermute      (const PermMatrix& P, const PermMatrix& Q) { return ThisObjectType::gePermuteIp      (P, Q); }
void RfMatrix::ipermuteLeft  (const PermMatrix& P                     ) { return ThisObjectType::gePermuteIpLeft  (P);    }
void RfMatrix::ipermuteRight (const PermMatrix& Q                     ) { return ThisObjectType::gePermuteIpRight (Q);    }
void RfMatrix::ipermuteMirror(const PermMatrix& P                     ) { return ThisObjectType::xxPermuteIpMirror(P);    }
/*-------------------------------------------------*/
RfMatrix RfMatrix::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RfMatrix ret;
	ThisObjectType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	RfMatrix ret;
	ThisObjectType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RfMGuard RfMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RfMGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<RfMatrix&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void RfMatrix::setBlock(uint_t ibgn, uint_t jbgn, const RfMatrix& src)
{
	ThisObjectType::setBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RfMatrix RfMatrix::init(uint_t nr, uint_t nc) 
{ 
	return init(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::init(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RfMatrix ret;
	ret.blankCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::zero(uint_t nr, uint_t nc) 
{ 
	return zero(prop_t::GENERAL, nr, nc) ;
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::zero(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RfMatrix ret;
	ret.zeroCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::random(uint_t nr, uint_t nc) 
{ 
	return random(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::random(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RfMatrix ret;
	ret.randomCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::wrap(uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv, false);
}
/*-------------------------------------------------*/
RfMatrix RfMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv, bool bind)
{
	RfMatrix ret;
	ret.wrapCreator(propcheck(ptype), nr, nc, vals, ldv, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
RfMGuard RfMatrix::wrap(uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv);
}
/*-------------------------------------------------*/
RfMGuard RfMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	RfMGuard ret;
	ThisGuardType& trg = ret;
	trg = RfMatrix::wrap(propcheck(ptype), nr, nc, const_cast<ThisDataType*>(vals), ldv, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RfMGuard::RfMGuard()
{
}
/*-------------------------------------------------*/
RfMGuard::~RfMGuard()
{
}
/*-------------------------------------------------*/
RfMGuard::RfMGuard(const RfMGuard& other)
	:ThisGuardType(other)
{
}
/*-------------------------------------------------*/
RfMGuard& RfMGuard::operator=(const RfMGuard& other)
{
	ThisGuardType::operator=(other);
	return *this;
}
/*-------------------------------------------------*/
const RfMatrix& RfMGuard::mat() const
{ 
	return ThisGuardType::obj(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RfMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
