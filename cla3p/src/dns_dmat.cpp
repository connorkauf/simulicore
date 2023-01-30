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
void dMat::info(const std::string& msg) const
{ 
	GenericObj::info(msg, "Matrix", "Real", "Double"); 
}
/*-------------------------------------------------*/
dMat dMat::copy()  const { return GenericObj::copy();  }
dMat dMat::move()        { return GenericObj::move();  }
void dMat::print() const {        GenericObj::print(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
dMat dMat::init  (const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) { return GenericObj::init  (prop, nrows, ncols, ld); }
dMat dMat::zero  (const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) { return GenericObj::zero  (prop, nrows, ncols, ld); }
dMat dMat::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld) { return GenericObj::random(prop, nrows, ncols, ld); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
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
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
