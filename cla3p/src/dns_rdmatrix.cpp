// this file inc
#include "dns_rdmatrix.hpp"

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
using ThisDataType = real_t;
using ThisRealType = real_t;
using ThisObjectType = GenericObject<ThisDataType,ThisDataType>;
using ThisGuardType = Guard<RdMatrix>;
/*-------------------------------------------------*/
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::DOUBLE)
/*-------------------------------------------------*/
static prop_t propcheck(prop_t ptype)
{
	return (ptype == prop_t::HERMITIAN ? prop_t::SYMMETRIC : ptype);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RdMatrix::RdMatrix()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
RdMatrix::RdMatrix(uint_t nr, uint_t nc)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, nr, nc, nr, false)
{
}
/*-------------------------------------------------*/
RdMatrix::RdMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nr, nc, nr, wipe)
{
}
/*-------------------------------------------------*/
RdMatrix::~RdMatrix()
{
}
/*-------------------------------------------------*/
RdMatrix::RdMatrix(RdMatrix&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
RdMatrix& RdMatrix::operator=(RdMatrix&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t RdMatrix::nrows() const { return rsize(); }
uint_t RdMatrix::ncols() const { return csize(); }
/*-------------------------------------------------*/
uint_t          RdMatrix::ld  () const { return ThisObjectType::ld  (); }
const Property& RdMatrix::prop() const { return ThisObjectType::prop(); }
/*-------------------------------------------------*/
void RdMatrix::scale(ThisDataType coeff)
{
	ThisObjectType::scaleWith(coeff);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::copy() const 
{ 
	RdMatrix ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::move()
{ 
	RdMatrix ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::clone()
{
	RdMatrix ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::clone() const
{
	RdMGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
std::string RdMatrix::info(const std::string& msg) const
{ 
	return ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
ThisRealType RdMatrix::normOne() const { return ThisObjectType::normOne(); }
ThisRealType RdMatrix::normInf() const { return ThisObjectType::normInf(); }
ThisRealType RdMatrix::normMax() const { return ThisObjectType::normMax(); }
ThisRealType RdMatrix::normFro() const { return ThisObjectType::normFro(); }
/*-------------------------------------------------*/
ThisDataType& RdMatrix::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& RdMatrix::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RdMatrix RdMatrix::transpose() const
{
	RdMatrix ret;
	ThisObjectType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::permute(const PermMatrix& P, const PermMatrix& Q) const
{
	RdMatrix ret;
	ThisObjectType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::permuteLeft(const PermMatrix& P) const
{
	RdMatrix ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::permuteRight(const PermMatrix& Q) const
{
	RdMatrix ret;
	ThisObjectType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::permuteMirror(const PermMatrix& P) const
{
	RdMatrix ret;
	ThisObjectType::xxPermuteToMirror(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void RdMatrix::ipermute      (const PermMatrix& P, const PermMatrix& Q) { return ThisObjectType::gePermuteIp      (P, Q); }
void RdMatrix::ipermuteLeft  (const PermMatrix& P                     ) { return ThisObjectType::gePermuteIpLeft  (P);    }
void RdMatrix::ipermuteRight (const PermMatrix& Q                     ) { return ThisObjectType::gePermuteIpRight (Q);    }
void RdMatrix::ipermuteMirror(const PermMatrix& P                     ) { return ThisObjectType::xxPermuteIpMirror(P);    }
/*-------------------------------------------------*/
RdMatrix RdMatrix::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RdMatrix ret;
	ThisObjectType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	RdMatrix ret;
	ThisObjectType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RdMGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<RdMatrix&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void RdMatrix::setBlock(uint_t ibgn, uint_t jbgn, const RdMatrix& src)
{
	ThisObjectType::setBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RdMatrix RdMatrix::init(uint_t nr, uint_t nc) 
{ 
	return init(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::init(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RdMatrix ret;
	ret.blankCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::zero(uint_t nr, uint_t nc) 
{ 
	return zero(prop_t::GENERAL, nr, nc) ;
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::zero(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RdMatrix ret;
	ret.zeroCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::random(uint_t nr, uint_t nc) 
{ 
	return random(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::random(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RdMatrix ret;
	ret.randomCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::wrap(uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv, false);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv, bool bind)
{
	RdMatrix ret;
	ret.wrapCreator(propcheck(ptype), nr, nc, vals, ldv, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::wrap(uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv);
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	RdMGuard ret;
	ThisGuardType& trg = ret;
	trg = RdMatrix::wrap(propcheck(ptype), nr, nc, const_cast<ThisDataType*>(vals), ldv, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RdMGuard::RdMGuard()
{
}
/*-------------------------------------------------*/
RdMGuard::~RdMGuard()
{
}
/*-------------------------------------------------*/
RdMGuard::RdMGuard(const RdMGuard& other)
	:ThisGuardType(other)
{
}
/*-------------------------------------------------*/
RdMGuard& RdMGuard::operator=(const RdMGuard& other)
{
	ThisGuardType::operator=(other);
	return *this;
}
/*-------------------------------------------------*/
const RdMatrix& RdMGuard::mat() const
{ 
	return ThisGuardType::obj(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
