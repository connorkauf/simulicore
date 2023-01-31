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
using ThisObjType = GenericObject<real_t>;
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
	ThisObjType& dest = ret;
	ThisObjType::copy_to(dest);
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::move()
{ 
	dMat ret;
	ThisObjType& dest = ret;
	ThisObjType::move_to(dest);
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::clone()
{
	dMat ret;
	ThisObjType& dest = ret;
	ThisObjType::clone_to(dest);
	return ret;
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
	ThisObjType& dest = ret;
	dest.create_empty(prop, nrows, ncols, ld); 
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	dMat ret;
	ThisObjType& dest = ret;
	dest.create_zero(prop, nrows, ncols, ld); 
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	dMat ret;
	ThisObjType& dest = ret;
	dest.create_random(prop, nrows, ncols, ld); 
	return ret;
}
/*-------------------------------------------------*/
dMat dMat::map(const Property& prop, uint_t nrows, uint_t ncols, real_t *values, uint_t ld)
{
	if(!ld) ld = nrows;
	dMat ret;
	ThisObjType& dest = ret;
	dest.create_mapped(prop, nrows, ncols, values, ld); 
	return ret;
}
/*-------------------------------------------------*/
real_t& dMat::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(out_of_bounds_message(nrows(),ncols(),i,j));
	} // out-of-bounds

	return ThisObjType::operator()(i,j);
}
/*-------------------------------------------------*/
const real_t& dMat::operator()(uint_t i, uint_t j) const
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
	:ThisMapType()
{
	ThisMapType& dest = *this;
	const ThisMapType& msrc = src;
	dest = msrc;
}
/*-------------------------------------------------*/
dMMap& dMMap::operator=(const dMMap& src)
{
	ThisMapType& dest = *this;
	const ThisMapType& msrc = src;
	dest = msrc;
	return *this;
}
/*-------------------------------------------------*/
const dMat& dMMap::mat() const
{ 
	return obj(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
