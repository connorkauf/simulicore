// this file inc
#include "dns_rimatrix.hpp"

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
using ThisDataType = int_t;
using ThisRealType = int_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RiMatrix>;
/*-------------------------------------------------*/
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
static prop_t propcheck(prop_t ptype)
{
	return (ptype == prop_t::HERMITIAN ? prop_t::SYMMETRIC : ptype);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RiMatrix::RiMatrix()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
RiMatrix::RiMatrix(uint_t nr, uint_t nc)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, nr, nc, nr, false)
{
}
/*-------------------------------------------------*/
RiMatrix::RiMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nr, nc, nr, wipe)
{
}
/*-------------------------------------------------*/
RiMatrix::~RiMatrix()
{
}
/*-------------------------------------------------*/
RiMatrix::RiMatrix(RiMatrix&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
RiMatrix& RiMatrix::operator=(RiMatrix&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t RiMatrix::nrows() const { return rsize(); }
uint_t RiMatrix::ncols() const { return csize(); }
/*-------------------------------------------------*/
uint_t          RiMatrix::ld  () const { return ThisObjectType::ld  (); }
const Property& RiMatrix::prop() const { return ThisObjectType::prop(); }
/*-------------------------------------------------*/
void RiMatrix::scale(ThisDataType coeff)
{
	ThisObjectType::scaleWith(coeff);
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::copy() const 
{ 
	RiMatrix ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::move()
{ 
	RiMatrix ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::clone()
{
	RiMatrix ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RiMGuard RiMatrix::clone() const
{
	RiMGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
std::string RiMatrix::info(const std::string& msg) const
{ 
	return ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
ThisDataType& RiMatrix::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& RiMatrix::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RiMatrix RiMatrix::transpose() const
{
	RiMatrix ret;
	ThisObjectType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::permute(const PermMatrix& P, const PermMatrix& Q) const
{
	RiMatrix ret;
	ThisObjectType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::permuteLeft(const PermMatrix& P) const
{
	RiMatrix ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::permuteRight(const PermMatrix& Q) const
{
	RiMatrix ret;
	ThisObjectType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::permuteMirror(const PermMatrix& P) const
{
	RiMatrix ret;
	ThisObjectType::xxPermuteToMirror(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void RiMatrix::ipermute      (const PermMatrix& P, const PermMatrix& Q) { return ThisObjectType::gePermuteIp      (P, Q); }
void RiMatrix::ipermuteLeft  (const PermMatrix& P                     ) { return ThisObjectType::gePermuteIpLeft  (P);    }
void RiMatrix::ipermuteRight (const PermMatrix& Q                     ) { return ThisObjectType::gePermuteIpRight (Q);    }
void RiMatrix::ipermuteMirror(const PermMatrix& P                     ) { return ThisObjectType::xxPermuteIpMirror(P);    }
/*-------------------------------------------------*/
RiMatrix RiMatrix::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RiMatrix ret;
	ThisObjectType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	RiMatrix ret;
	ThisObjectType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RiMGuard RiMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RiMGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<RiMatrix&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void RiMatrix::setBlock(uint_t ibgn, uint_t jbgn, const RiMatrix& src)
{
	ThisObjectType::setBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RiMatrix RiMatrix::init(uint_t nr, uint_t nc) 
{ 
	return init(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::init(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RiMatrix ret;
	ret.blankCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::zero(uint_t nr, uint_t nc) 
{ 
	return zero(prop_t::GENERAL, nr, nc) ;
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::zero(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RiMatrix ret;
	ret.zeroCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::random(uint_t nr, uint_t nc) 
{ 
	return random(prop_t::GENERAL, nr, nc);
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::random(prop_t ptype, uint_t nr, uint_t nc) 
{ 
	RiMatrix ret;
	ret.randomCreator(propcheck(ptype), nr, nc, nr); 
	return ret.move();
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::wrap(uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv, false);
}
/*-------------------------------------------------*/
RiMatrix RiMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, ThisDataType *vals, uint_t ldv, bool bind)
{
	RiMatrix ret;
	ret.wrapCreator(propcheck(ptype), nr, nc, vals, ldv, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
RiMGuard RiMatrix::wrap(uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	return wrap(prop_t::GENERAL, nr, nc, vals, ldv);
}
/*-------------------------------------------------*/
RiMGuard RiMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const ThisDataType *vals, uint_t ldv)
{
	RiMGuard ret;
	ThisGuardType& trg = ret;
	trg = RiMatrix::wrap(propcheck(ptype), nr, nc, const_cast<ThisDataType*>(vals), ldv, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
RiMGuard::RiMGuard()
{
}
/*-------------------------------------------------*/
RiMGuard::~RiMGuard()
{
}
/*-------------------------------------------------*/
RiMGuard::RiMGuard(const RiMGuard& other)
	:ThisGuardType(other)
{
}
/*-------------------------------------------------*/
RiMGuard& RiMGuard::operator=(const RiMGuard& other)
{
	ThisGuardType::operator=(other);
	return *this;
}
/*-------------------------------------------------*/
const RiMatrix& RiMGuard::mat() const
{ 
	return ThisGuardType::obj(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RiMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
