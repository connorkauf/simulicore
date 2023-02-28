#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_
/*-------------------------------------------------*/
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../perms/perm_matrix.hpp"
/*-------------------------------------------------*/
//
//
// Common functionality for floating point & integer dense vectors
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
XxVector::XxVector()
	: 
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
XxVector::XxVector(uint_t n)
	:
		UniversalConstructor(),
		ThisObjectType(Property(prop_t::GENERAL,uplo_t::F), n, 1, n, false)
{
}
/*-------------------------------------------------*/
XxVector::~XxVector()
{
}
/*-------------------------------------------------*/
XxVector::XxVector(XxVector&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
XxVector& XxVector::operator=(XxVector&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t XxVector::size() const { return rsize(); }
/*-------------------------------------------------*/
void XxVector::scale(ThisDataType coeff)
{
	ThisObjectType::scaleWith(coeff);
}
/*-------------------------------------------------*/
XxVector XxVector::copy() const 
{ 
	XxVector ret;
	ThisObjectType::copyTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxVector XxVector::move()
{ 
	XxVector ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxVector XxVector::clone()
{
	XxVector ret;
	ThisObjectType::cloneTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
XxVGuard XxVector::clone() const
{
	XxVGuard ret;
	ThisGuardType& trg = ret;
	trg = *this;
	return ret;
}
/*-------------------------------------------------*/
std::string XxVector::info(const std::string& msg) const
{ 
	return ThisObjectType::info(false, msg, objTypeName(), dataTypeName(), precTypeName()); 
}
/*-------------------------------------------------*/
ThisDataType& XxVector::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return ThisObjectType::operator()(i,0);
}
/*-------------------------------------------------*/
const ThisDataType& XxVector::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return ThisObjectType::operator()(i,0);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVector XxVector::permuteLeft(const PermMatrix& P) const
{
	XxVector ret;
	ThisObjectType::gePermuteToLeft(ret, P);
	return ret.move();
}
/*-------------------------------------------------*/
void XxVector::ipermuteLeft(const PermMatrix& P) 
{ 
	return ThisObjectType::gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
XxVector XxVector::block(uint_t ibgn, uint_t ni) const
{
	XxVector ret;
	ThisObjectType::getBlock(ret, ibgn, 0, ni, 1);
	return ret.move();
}
/*-------------------------------------------------*/
XxVector XxVector::rblock(uint_t ibgn, uint_t ni)
{
	XxVector ret;
	ThisObjectType::getBlockReference(ret, ibgn, 0, ni, 1);
	return ret.move();
}
/*-------------------------------------------------*/
XxVGuard XxVector::rblock(uint_t ibgn, uint_t ni) const
{
	XxVGuard ret;
	ThisGuardType& trg = ret;
	trg = const_cast<XxVector&>(*this).rblock(ibgn, ni);
	return ret;
}
/*-------------------------------------------------*/
void XxVector::setBlock(uint_t ibgn, const XxVector& src)
{
	ThisObjectType::setBlock(src, ibgn, 0);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVector XxVector::init(uint_t n) 
{ 
	XxVector ret;
	Property pr(prop_t::GENERAL,uplo_t::F);
	ret.blankCreator(pr, n, 1, n); 
	return ret.move();
}
/*-------------------------------------------------*/
XxVector XxVector::zero(uint_t n) 
{ 
	XxVector ret;
	Property pr(prop_t::GENERAL,uplo_t::F);
	ret.zeroCreator(pr, n, 1, n); 
	return ret.move();
}
/*-------------------------------------------------*/
XxVector XxVector::random(uint_t n) 
{ 
	XxVector ret;
	Property pr(prop_t::GENERAL,uplo_t::F);
	ret.randomCreator(pr, n, 1, n); 
	return ret.move();
}
/*-------------------------------------------------*/
XxVector XxVector::wrap(uint_t n, ThisDataType *vals, bool bind)
{
	XxVector ret;
	Property pr(prop_t::GENERAL,uplo_t::F);
	ret.wrapCreator(pr, n, 1, vals, n, bind); 
	return ret.move();
}
/*-------------------------------------------------*/
XxVGuard XxVector::wrap(uint_t n, const ThisDataType *vals)
{
	XxVGuard ret;
	ThisGuardType& trg = ret;
	trg = XxVector::wrap(n, const_cast<ThisDataType*>(vals), false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVGuard::XxVGuard()
{
}
/*-------------------------------------------------*/
XxVGuard::~XxVGuard()
{
}
/*-------------------------------------------------*/
XxVGuard::XxVGuard(const XxVGuard& other)
	:ThisGuardType(other)
{
}
/*-------------------------------------------------*/
XxVGuard& XxVGuard::operator=(const XxVGuard& other)
{
	ThisGuardType::operator=(other);
	return *this;
}
/*-------------------------------------------------*/
const XxVector& XxVGuard::vec() const
{ 
	return ThisGuardType::obj(); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxVector& vec)
{
	os << vec.printToString();
	return os;
}
/*-------------------------------------------------*/
#endif // CLA3P_DNS_XXVECTOR_HPP_
