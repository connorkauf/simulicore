// this file inc
#include "dns_dmat.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"
#include "utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDatType = real_t;
using ThisObjType = GenericObject<ThisDatType>;
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
dMat::dMat()
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
dMat dMat::init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	dMat ret;
	ret.create_empty(prop, nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	dMat ret;
	ret.create_zero(prop, nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	dMat ret;
	ret.create_random(prop, nrows, ncols, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMat dMat::map(const Property& prop, uint_t nrows, uint_t ncols, ThisDatType *values, uint_t ld)
{
	if(!ld) ld = nrows;
	dMat ret;
	ret.create_mapped(prop, nrows, ncols, values, ld); 
	return ret.move();
}
/*-------------------------------------------------*/
dMMap dMat::map(const Property& prop, uint_t nrows, uint_t ncols, const ThisDatType *values, uint_t ld)
{
	dMat mat = dMat::map(prop, nrows, ncols, const_cast<ThisDatType*>(values), ld);
	dMMap ret;
	ThisMapType& dest = ret;
	dest = mat;
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
