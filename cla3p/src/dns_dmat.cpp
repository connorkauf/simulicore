// this file inc
#include "dns_dmat.hpp"

// system

// 3rd

// cla3p
#include "support/error.hpp"
#include "support/error_internal.hpp"
#include "support/utils.hpp"
#include "prm_mat.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = real_t;
using ThisRealType = real_t;
using ThisObjectType = GenericObject<ThisDataType,ThisDataType>;
using ThisGuardType = Guard<dMat>;
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
dMat::dMat()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
dMat::dMat(uint_t nrows, uint_t ncols)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, nrows, ncols, nrows, false)
{
}
/*-------------------------------------------------*/
dMat::dMat(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
	:
		UniversalConstructor(),
		ThisObjectType(propcheck(ptype), nrows, ncols, ld, wipe)
{
}
/*-------------------------------------------------*/
dMat::~dMat()
{
}
/*-------------------------------------------------*/
dMat::dMat(dMat&& src)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(src))
{
}
/*-------------------------------------------------*/
dMat& dMat::operator=(dMat&& src)
{
	ThisObjectType::operator=(std::move(src));
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t dMat::nrows() const { return rsize(); }
uint_t dMat::ncols() const { return csize(); }
/*-------------------------------------------------*/
uint_t          dMat::ld  () const { return ThisObjectType::ld  (); }
const Property& dMat::prop() const { return ThisObjectType::prop(); }
/*-------------------------------------------------*/
dMat dMat::copy() const 
{ 
	dMat ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::move()
{ 
	dMat ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::clone()
{
	dMat ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMGuard dMat::clone() const
{
	dMGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
void dMat::info(const std::string& msg) const
{ 
	ThisObjectType::info(true, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
real_t dMat::normOne() const { return ThisObjectType::normOne(); }
real_t dMat::normInf() const { return ThisObjectType::normInf(); }
real_t dMat::normMax() const { return ThisObjectType::normMax(); }
real_t dMat::normFro() const { return ThisObjectType::normFro(); }
/*-------------------------------------------------*/
ThisDataType& dMat::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDataType& dMat::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjectType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat dMat::transpose() const
{
	dMat ret;
	ThisObjectType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P, const prm::pMat& Q) const
{
	dMat ret;
	ThisObjectType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permuteLeft(const prm::pMat& P) const
{
	dMat ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permuteRight(const prm::pMat& Q) const
{
	dMat ret;
	ThisObjectType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P) const
{
	dMat ret;
	ThisObjectType::shPermuteTo(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void dMat::ipermute     (const prm::pMat& P, const prm::pMat& Q) { return ThisObjectType::gePermuteIp     (P, Q); }
void dMat::ipermuteLeft (const prm::pMat& P                    ) { return ThisObjectType::gePermuteIpLeft (P);    }
void dMat::ipermuteRight(const prm::pMat& Q                    ) { return ThisObjectType::gePermuteIpRight(Q);    }
void dMat::ipermute     (const prm::pMat& P                    ) { return ThisObjectType::shPermuteIp     (P);    }
/*-------------------------------------------------*/
dMat dMat::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	dMat ret;
	ThisObjectType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	dMat ret;
	ThisObjectType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
dMGuard dMat::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	dMGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<dMat&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void dMat::setBlock(uint_t ibgn, uint_t jbgn, const dMat& src)
{
	ThisObjectType::setBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat dMat::init(uint_t nrows, uint_t ncols) 
{ 
	return init(prop_t::GENERAL, nrows, ncols, nrows);
}
/*-------------------------------------------------*/
dMat dMat::init(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.blankCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::zero(uint_t nrows, uint_t ncols) 
{ 
	return zero(prop_t::GENERAL, nrows, ncols, nrows) ;
}
/*-------------------------------------------------*/
dMat dMat::zero(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.zeroCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::random(uint_t nrows, uint_t ncols) 
{ 
	return random(prop_t::GENERAL, nrows, ncols, nrows);
}
/*-------------------------------------------------*/
dMat dMat::random(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.randomCreator(propcheck(ptype), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::wrap(uint_t nrows, uint_t ncols, ThisDataType *values)
{
	return wrap(prop_t::GENERAL, nrows, ncols, values, nrows, false);
}
/*-------------------------------------------------*/
dMat dMat::wrap(prop_t ptype, uint_t nrows, uint_t ncols, ThisDataType *values, uint_t ld, bool bind)
{
	dMat ret;
	ret.wrapCreator(propcheck(ptype), nrows, ncols, values, ld, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
dMGuard dMat::wrap(uint_t nrows, uint_t ncols, const ThisDataType *values)
{
	return wrap(prop_t::GENERAL, nrows, ncols, values, nrows);
}
/*-------------------------------------------------*/
dMGuard dMat::wrap(prop_t ptype, uint_t nrows, uint_t ncols, const ThisDataType *values, uint_t ld)
{
	dMGuard ret;
	ThisGuardType& trg = ret;
	trg = dMat::wrap(propcheck(ptype), nrows, ncols, const_cast<ThisDataType*>(values), ld, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMGuard::dMGuard()
{
}
/*-------------------------------------------------*/
dMGuard::~dMGuard()
{
}
/*-------------------------------------------------*/
dMGuard::dMGuard(const dMGuard& src)
	:ThisGuardType(src)
{
}
/*-------------------------------------------------*/
dMGuard& dMGuard::operator=(const dMGuard& src)
{
	ThisGuardType::operator=(src);
	return *this;
}
/*-------------------------------------------------*/
const dMat& dMGuard::mat() const
{ 
	return ThisGuardType::obj(); 
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::dMat& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
