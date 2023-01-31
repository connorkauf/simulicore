// this file inc
#include "dns_dmat.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using GenericObj = GenericObject<real_t>;
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
{
	*this = static_cast<GenericObj&&>(src);
}
/*-------------------------------------------------*/
dMat& dMat::operator=(dMat&& src)
{
	*this = static_cast<GenericObj&&>(src);
	return *this;
}
/*-------------------------------------------------*/
dMat::dMat(GenericObj&& src)
{
	GenericObj& dest = *this;
	dest = src.move();
}
/*-------------------------------------------------*/
dMat& dMat::operator=(GenericObj&& src)
{
	GenericObj& dest = *this;
	dest = src.move();
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
bool dMat::isready() const
{
	return GenericObj::isready();
}
/*-------------------------------------------------*/
void dMat::clear()
{
	return GenericObj::clear();
}
/*-------------------------------------------------*/
void dMat::unbind()
{
	return GenericObj::unbind();
}
/*-------------------------------------------------*/
dMat dMat::copy() const 
{ 
	return GenericObj::copy();  
}
/*-------------------------------------------------*/
dMat dMat::clone()
{
	return GenericObj::clone();
}
/*-------------------------------------------------*/
#if 0
dMMap dMat::clone() const
{
}
#endif
/*-------------------------------------------------*/
dMat dMat::move()
{ 
	return GenericObj::move();  
}
/*-------------------------------------------------*/
void dMat::info(const std::string& msg) const
{ 
	GenericObj::info(msg, objtype(), datatype(), prectype()); 
}
/*-------------------------------------------------*/
void dMat::print() const 
{
	GenericObj::print(); 
}
/*-------------------------------------------------*/
dMat dMat::init  (const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	return GenericObj::init  (prop, nrows, ncols, ld); 
}
/*-------------------------------------------------*/
dMat dMat::zero  (const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	return GenericObj::zero  (prop, nrows, ncols, ld); 
}
/*-------------------------------------------------*/
dMat dMat::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) 
{ 
	if(!ld) ld = nrows;
	return GenericObj::random(prop, nrows, ncols, ld); 
}
/*-------------------------------------------------*/
dMat dMat::map(const Property& prop, uint_t nrows, uint_t ncols, real_t *values, uint_t ld)
{
	if(!ld) ld = nrows;
	return GenericObj::map(prop, nrows, ncols, values, ld); 
}
/*-------------------------------------------------*/
real_t& dMat::operator()(uint_t i, uint_t j)
{
	return GenericObj::operator()(i,j);
}
/*-------------------------------------------------*/
const real_t& dMat::operator()(uint_t i, uint_t j) const
{
	return GenericObj::operator()(i,j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
