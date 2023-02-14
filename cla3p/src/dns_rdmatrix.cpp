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
RdMatrix::RdMatrix(uint_t nrows, uint_t ncols)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, nrows, ncols, nrows, false)
{
}
/*-------------------------------------------------*/
RdMatrix::RdMatrix(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nrows, ncols, ld, wipe)
{
}
/*-------------------------------------------------*/
RdMatrix::~RdMatrix()
{
}
/*-------------------------------------------------*/
RdMatrix::RdMatrix(RdMatrix&& src)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(src))
{
}
/*-------------------------------------------------*/
RdMatrix& RdMatrix::operator=(RdMatrix&& src)
{
	ThisObjectType::operator=(std::move(src));
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
void RdMatrix::info(const std::string& msg) const
{ 
	ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
real_t RdMatrix::normOne() const { return ThisObjectType::normOne(); }
real_t RdMatrix::normInf() const { return ThisObjectType::normInf(); }
real_t RdMatrix::normMax() const { return ThisObjectType::normMax(); }
real_t RdMatrix::normFro() const { return ThisObjectType::normFro(); }
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
RdMatrix RdMatrix::permute(const PermMatrix& P) const
{
	RdMatrix ret;
	ThisObjectType::shPermuteTo(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void RdMatrix::ipermute     (const PermMatrix& P, const PermMatrix& Q) { return ThisObjectType::gePermuteIp     (P, Q); }
void RdMatrix::ipermuteLeft (const PermMatrix& P                    ) { return ThisObjectType::gePermuteIpLeft (P);    }
void RdMatrix::ipermuteRight(const PermMatrix& Q                    ) { return ThisObjectType::gePermuteIpRight(Q);    }
void RdMatrix::ipermute     (const PermMatrix& P                    ) { return ThisObjectType::shPermuteIp     (P);    }
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
RdMatrix RdMatrix::init(uint_t nrows, uint_t ncols) 
{ 
	return init(prop_t::GENERAL, nrows, ncols, nrows);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::init(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	RdMatrix ret;
	ret.blankCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::zero(uint_t nrows, uint_t ncols) 
{ 
	return zero(prop_t::GENERAL, nrows, ncols, nrows) ;
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::zero(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	RdMatrix ret;
	ret.zeroCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::random(uint_t nrows, uint_t ncols) 
{ 
	return random(prop_t::GENERAL, nrows, ncols, nrows);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::random(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	RdMatrix ret;
	ret.randomCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::wrap(uint_t nrows, uint_t ncols, ThisDataType *values)
{
	return wrap(prop_t::GENERAL, nrows, ncols, values, nrows, false);
}
/*-------------------------------------------------*/
RdMatrix RdMatrix::wrap(prop_t ptype, uint_t nrows, uint_t ncols, ThisDataType *values, uint_t ld, bool bind)
{
	RdMatrix ret;
	ret.wrapCreator(propcheck(ptype), nrows, ncols, values, ld, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::wrap(uint_t nrows, uint_t ncols, const ThisDataType *values)
{
	return wrap(prop_t::GENERAL, nrows, ncols, values, nrows);
}
/*-------------------------------------------------*/
RdMGuard RdMatrix::wrap(prop_t ptype, uint_t nrows, uint_t ncols, const ThisDataType *values, uint_t ld)
{
	RdMGuard ret;
	ThisGuardType& trg = ret;
	trg = RdMatrix::wrap(propcheck(ptype), nrows, ncols, const_cast<ThisDataType*>(values), ld, false);
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
RdMGuard::RdMGuard(const RdMGuard& src)
	:ThisGuardType(src)
{
}
/*-------------------------------------------------*/
RdMGuard& RdMGuard::operator=(const RdMGuard& src)
{
	ThisGuardType::operator=(src);
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
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdMGuard& grd)
{
	os << grd.mat().printToString();
	return os;
}
/*-------------------------------------------------*/
