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
using ThisDatType = real_t;
using ThisObjType = GenericObject<ThisDatType,ThisDatType>;
using ThisMapType = GenericMap<dMat>;
/*-------------------------------------------------*/
const std::string _objtype = "Matrix";
const std::string _datatype = "Real";
const std::string _prectype = "Double";
/*-------------------------------------------------*/
const std::string& objtype () { return _objtype ; }
const std::string& datatype() { return _datatype; }
const std::string& prectype() { return _prectype; }
/*-------------------------------------------------*/
static const prop_t _pproper = prop_t::SYMMETRIC;
/*-------------------------------------------------*/
static prop_t propcheck(prop_t ptype)
{
	return (ptype == prop_t::HERMITIAN ? _pproper : ptype);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat::dMat()
{
}
/*-------------------------------------------------*/
dMat::dMat(uint_t nrows, uint_t ncols)
	:ThisObjType(prop_t::GENERAL, nrows, ncols, nrows, false)
{
}
/*-------------------------------------------------*/
dMat::dMat(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
	:ThisObjType(propcheck(ptype), nrows, ncols, ld, wipe)
{
}
/*-------------------------------------------------*/
dMat::~dMat()
{
}
/*-------------------------------------------------*/
dMat::dMat(dMat&& src)
	:ThisObjType(std::move(src))
{
}
/*-------------------------------------------------*/
dMat& dMat::operator=(dMat&& src)
{
	ThisObjType::operator=(std::move(src));
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t          dMat::nrows () const { return ThisObjType::nrows (); }
uint_t          dMat::ncols () const { return ThisObjType::ncols (); }
uint_t          dMat::ld    () const { return ThisObjType::ld    (); }
const Property& dMat::prop  () const { return ThisObjType::prop  (); }
/*-------------------------------------------------*/
dMat dMat::copy() const 
{ 
	dMat ret;
	ThisObjType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::move()
{ 
	dMat ret;
	ThisObjType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::clone()
{
	dMat ret;
	ThisObjType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMMap dMat::clone() const
{
	dMMap ret;
	ThisMapType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
void dMat::info(const std::string& msg) const
{ 
	ThisObjType::info(msg, objtype(), datatype(), prectype()); 
}
/*-------------------------------------------------*/
real_t dMat::normOne() const { return ThisObjType::normOne(); }
real_t dMat::normInf() const { return ThisObjType::normInf(); }
real_t dMat::normMax() const { return ThisObjType::normMax(); }
real_t dMat::normFro() const { return ThisObjType::normFro(); }
/*-------------------------------------------------*/
ThisDatType& dMat::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjType::operator()(i,j);
}
/*-------------------------------------------------*/
const ThisDatType& dMat::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjType::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat dMat::transpose() const
{
	dMat ret;
	ThisObjType::transposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P, const prm::pMat& Q) const
{
	dMat ret;
	ThisObjType::gePermuteTo(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permuteLeft(const prm::pMat& P) const
{
	dMat ret;
	ThisObjType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permuteRight(const prm::pMat& Q) const
{
	dMat ret;
	ThisObjType::gePermuteToRight(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P) const
{
	dMat ret;
	ThisObjType::shPermuteTo(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void dMat::ipermute     (const prm::pMat& P, const prm::pMat& Q) { return ThisObjType::gePermuteIp     (P, Q); }
void dMat::ipermuteLeft (const prm::pMat& P                    ) { return ThisObjType::gePermuteIpLeft (P);    }
void dMat::ipermuteRight(const prm::pMat& Q                    ) { return ThisObjType::gePermuteIpRight(Q);    }
void dMat::ipermute     (const prm::pMat& P                    ) { return ThisObjType::shPermuteIp     (P);    }
/*-------------------------------------------------*/
dMat dMat::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	dMat ret;
	ThisObjType::getBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	dMat ret;
	ThisObjType::getBlockReference(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
dMMap dMat::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	dMMap ret;
	ThisMapType& trg = ret;
	trg = const_cast<dMat&>(*this).rblock(ibgn, jbgn, ni, nj);
	return ret;
}
/*-------------------------------------------------*/
void dMat::setBlock(uint_t ibgn, uint_t jbgn, const dMat& src)
{
	ThisObjType::setBlock(src, ibgn, jbgn);
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
dMat dMat::map(uint_t nrows, uint_t ncols, ThisDatType *values)
{
	return map(prop_t::GENERAL, nrows, ncols, values, nrows, false);
}
/*-------------------------------------------------*/
dMat dMat::map(prop_t ptype, uint_t nrows, uint_t ncols, ThisDatType *values, uint_t ld, bool bind)
{
	dMat ret;
	ret.mapCreator(propcheck(ptype), nrows, ncols, values, ld, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
dMMap dMat::map(uint_t nrows, uint_t ncols, const ThisDatType *values)
{
	return map(prop_t::GENERAL, nrows, ncols, values, nrows);
}
/*-------------------------------------------------*/
dMMap dMat::map(prop_t ptype, uint_t nrows, uint_t ncols, const ThisDatType *values, uint_t ld)
{
	dMMap ret;
	ThisMapType& trg = ret;
	trg = dMat::map(propcheck(ptype), nrows, ncols, const_cast<ThisDatType*>(values), ld, false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMMap::dMMap()
{
}
/*-------------------------------------------------*/
dMMap::~dMMap()
{
}
/*-------------------------------------------------*/
dMMap::dMMap(const dMMap& src)
	:ThisMapType(src)
{
}
/*-------------------------------------------------*/
dMMap& dMMap::operator=(const dMMap& src)
{
	ThisMapType::operator=(src);
	return *this;
}
/*-------------------------------------------------*/
const dMat& dMMap::mat() const
{ 
	return ThisMapType::obj(); 
}
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
