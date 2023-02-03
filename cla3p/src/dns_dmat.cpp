// this file inc
#include "dns_dmat.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"
#include "error_internal.hpp"
#include "utils.hpp"
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
static const Property _pproper = prop_t::SYMMETRIC;
/*-------------------------------------------------*/
static const Property& propcheck(const Property& prop)
{
	return (prop.is_hermitian() ? _pproper : prop);
}
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
uint_t             dMat::nrows () const { return ThisObjType::nrows (); }
uint_t             dMat::ncols () const { return ThisObjType::ncols (); }
uint_t             dMat::ld    () const { return ThisObjType::ld    (); }
ThisDatType*       dMat::values()       { return ThisObjType::values(); }
const ThisDatType* dMat::values() const { return ThisObjType::values(); }
const Property&    dMat::prop  () const { return ThisObjType::prop  (); }
bool               dMat::owner () const { return ThisObjType::owner (); }
/*-------------------------------------------------*/
bool dMat::empty() const
{
	return ThisObjType::empty();
}
/*-------------------------------------------------*/
void dMat::clear()
{
	return ThisObjType::clear();
}
/*-------------------------------------------------*/
void dMat::unbind()
{
	return ThisObjType::unbind();
}
/*-------------------------------------------------*/
void dMat::scale(real_t coeff)
{
	return ThisObjType::scale(coeff);
}
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
	ThisMapType& dest = ret;
	dest = *this;
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::transpose() const
{
	dMat ret;
	ThisObjType::transpose_to(ret);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const cla3p::prm::pMat& P, const cla3p::prm::pMat& Q) const
{
	if(P.empty() || Q.empty()) {
		throw NoConsistency(msg_empty_object() + " on permute operation");
	}

	if(!prop().is_general()) {
		throw InvalidOp("Double sided permutations are applied on general matrices");
	}

	dMat ret;
	ThisObjType::permute_to(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::lpermute(const cla3p::prm::pMat& P) const
{
	if(P.empty()) {
		throw NoConsistency(msg_empty_object() + " on permute operation (left)");
	}

	if(!prop().is_general()) {
		throw InvalidOp("Left sided permutations are applied on general matrices");
	}

	cla3p::prm::pMat Q; // dummy Q
	dMat ret;
	ThisObjType::permute_to(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::rpermute(const cla3p::prm::pMat& Q) const
{
	if(Q.empty()) {
		throw NoConsistency(msg_empty_object() + " on permute operation (right)");
	}

	if(!prop().is_general()) {
		throw InvalidOp("Right sided permutations are applied on general matrices");
	}

	cla3p::prm::pMat P; // dummy P
	dMat ret;
	ThisObjType::permute_to(ret, P, Q);
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::permute(const cla3p::prm::pMat& P) const
{
	if(P.empty()) {
		throw NoConsistency(msg_empty_object() + " on permute operation (symmetric)");
	}

	if(!prop().is_symmetric()) {
		throw InvalidOp("Symmetric permutations are applied on symmetric matrices");
	}

	cla3p::prm::pMat Q; // dummy Q
	dMat ret;
	ThisObjType::permute_to(ret, P, Q);
	return ret.move();
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
real_t dMat::norm_one() const { return ThisObjType::norm_one(); }
real_t dMat::norm_inf() const { return ThisObjType::norm_inf(); }
real_t dMat::norm_max() const { return ThisObjType::norm_max(); }
real_t dMat::norm_fro() const { return ThisObjType::norm_fro(); }
/*-------------------------------------------------*/
dMat dMat::init(uint_t nrows, uint_t ncols) 
{ 
	return init(prop_t::GENERAL, nrows, ncols, nrows);
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
	return zero(prop_t::GENERAL, nrows, ncols, nrows) ;
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
	return random(prop_t::GENERAL, nrows, ncols, nrows);
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
	return map(prop_t::GENERAL, nrows, ncols, values, nrows, false);
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
	return map(prop_t::GENERAL, nrows, ncols, values, nrows);
}
/*-------------------------------------------------*/
dMMap dMat::map(const Property& prop, uint_t nrows, uint_t ncols, const ThisDatType *values, uint_t ld)
{
	dMMap ret;
	ThisMapType& dest = ret;
	dest = dMat::map(propcheck(prop), nrows, ncols, const_cast<ThisDatType*>(values), ld, false);
	return ret;
}
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
