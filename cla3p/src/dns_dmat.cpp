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
static const Property _pproper = Property(prop_t::SYMMETRIC);
/*-------------------------------------------------*/
static const Property& propcheck(const Property& prop)
{
	return (prop.is_hermitian() ? _pproper : prop);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat::dMat()
{
}
/*-------------------------------------------------*/
dMat::dMat(uint_t nrows, uint_t ncols)
	:ThisObjType(Property(prop_t::GENERAL), nrows, ncols, nrows, false)
{
}
/*-------------------------------------------------*/
dMat::dMat(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
	:ThisObjType(propcheck(prop), nrows, ncols, ld, wipe)
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
	ThisObjType::copy_to(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::move()
{ 
	dMat ret;
	ThisObjType::move_to(ret);
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::clone()
{
	dMat ret;
	ThisObjType::clone_to(ret);
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
void dMat::print(uint_t nsd) const 
{
	ThisObjType::print(nsd); 
}
/*-------------------------------------------------*/
std::string dMat::print2str(uint_t nsd) const 
{
	return ThisObjType::print2str(nsd); 
}
/*-------------------------------------------------*/
real_t dMat::norm_one() const { return ThisObjType::norm_one(); }
real_t dMat::norm_inf() const { return ThisObjType::norm_inf(); }
real_t dMat::norm_max() const { return ThisObjType::norm_max(); }
real_t dMat::norm_fro() const { return ThisObjType::norm_fro(); }
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
	ThisObjType::transpose_to(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P, const prm::pMat& Q) const
{
	dMat ret;
	ThisObjType::ge_permute_to(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute_left(const prm::pMat& P) const
{
	dMat ret;
	ThisObjType::ge_permute_to_left(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute_right(const prm::pMat& Q) const
{
	dMat ret;
	ThisObjType::ge_permute_to_right(ret, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const prm::pMat& P) const
{
	dMat ret;
	ThisObjType::sh_permute_to(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void dMat::ipermute      (const prm::pMat& P, const prm::pMat& Q) { return ThisObjType::ge_permute_ip      (P, Q); }
void dMat::ipermute_left (const prm::pMat& P                    ) { return ThisObjType::ge_permute_ip_left (P);    }
void dMat::ipermute_right(const prm::pMat& Q                    ) { return ThisObjType::ge_permute_ip_right(Q);    }
void dMat::ipermute      (const prm::pMat& P                    ) { return ThisObjType::sh_permute_ip      (P);    }
/*-------------------------------------------------*/
dMat dMat::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	dMat ret;
	ThisObjType::get_block(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	dMat ret;
	ThisObjType::get_block_reference(ret, ibgn, jbgn, ni, nj);
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
void dMat::set_block(uint_t ibgn, uint_t jbgn, const dMat& src)
{
	ThisObjType::set_block(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat dMat::init(uint_t nrows, uint_t ncols) 
{ 
	return init(Property(prop_t::GENERAL), nrows, ncols, nrows);
}
/*-------------------------------------------------*/
dMat dMat::init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.blank_creator(propcheck(prop), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::zero(uint_t nrows, uint_t ncols) 
{ 
	return zero(Property(prop_t::GENERAL), nrows, ncols, nrows) ;
}
/*-------------------------------------------------*/
dMat dMat::zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.zero_creator(propcheck(prop), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::random(uint_t nrows, uint_t ncols) 
{ 
	return random(Property(prop_t::GENERAL), nrows, ncols, nrows);
}
/*-------------------------------------------------*/
dMat dMat::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	dMat ret;
	ret.random_creator(propcheck(prop), nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::map(uint_t nrows, uint_t ncols, ThisDatType *values)
{
	return map(Property(prop_t::GENERAL), nrows, ncols, values, nrows, false);
}
/*-------------------------------------------------*/
dMat dMat::map(const Property& prop, uint_t nrows, uint_t ncols, ThisDatType *values, uint_t ld, bool bind)
{
	dMat ret;
	ret.map_creator(propcheck(prop), nrows, ncols, values, ld, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
dMMap dMat::map(uint_t nrows, uint_t ncols, const ThisDatType *values)
{
	return map(Property(prop_t::GENERAL), nrows, ncols, values, nrows);
}
/*-------------------------------------------------*/
dMMap dMat::map(const Property& prop, uint_t nrows, uint_t ncols, const ThisDatType *values, uint_t ld)
{
	dMMap ret;
	ThisMapType& trg = ret;
	trg = dMat::map(propcheck(prop), nrows, ncols, const_cast<ThisDatType*>(values), ld, false);
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
	os << mat.print2str();
	return os;
}
/*-------------------------------------------------*/
