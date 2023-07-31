// this file inc
#include "dns_xxobject.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../bulk/dns.hpp"
#include "../bulk/dns_math.hpp"
#include "../checks/all_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject<T_Scalar,T_Object>
#define XxObjectTlst template <typename T_Scalar, typename T_Object>
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject()
{
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::XxObject(uint_t nr, uint_t nc, uint_t nl, const Property& pr)
	: Array2D<T_Scalar>(nr, nc, nl, pr)
{
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl::~XxObject()
{
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::operator+(const XxObjectTmpl& other)
{
	T_Object ret;
	ret.createFromScaledSum(1, *this, 1, other);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::operator-(const XxObjectTmpl& other)
{
	T_Object ret;
	ret.createFromScaledSum(1, *this, -1, other);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl& XxObjectTmpl::operator+=(const XxObjectTmpl& other)
{
	updateSelfWithScaledOther(1, other);
	return *this;
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl& XxObjectTmpl::operator-=(const XxObjectTmpl& other)
{
	updateSelfWithScaledOther(-1, other);
	return *this;
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl& XxObjectTmpl::operator*=(T_Scalar val)
{
	scale(val);
	return *this;
}
/*-------------------------------------------------*/
XxObjectTlst
XxObjectTmpl& XxObjectTmpl::operator/=(T_Scalar val)
{
	if(val == T_Scalar(0)) {
		throw InvalidOp(msg::division_by_zero());
	}

	T_Scalar one(1);
	T_Scalar coeff = one / val;
	scale(coeff);
	return *this;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::copy() const
{
	T_Object ret;
	this->copyTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::rcopy()
{
	T_Object ret;
	this->copyToShallow(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_Object> XxObjectTmpl::rcopy() const
{
	T_Object tmp;
	const_cast<XxObjectTmpl&>(*this).copyToShallow(tmp);
	Guard<T_Object> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::move()
{
	T_Object ret;
	this->moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::scale(T_Scalar val)
{
	if(this->property().isHermitian() && getIm(val)) {
		throw InvalidOp(msg::hermitian_inconsistency());
	}

	bulk::dns::scale(
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize(), val);
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normOne() const
{ 
	return bulk::dns::norm_one(
			this->property().type(),
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
typename XxObjectTmpl::T_RScalar XxObjectTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(
			this->property().type(),
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Guard<T_Object> tmp = getBlockReference(ibgn, jbgn, ni, nj);
	return tmp.get().copy();
}
/*-------------------------------------------------*/
XxObjectTlst
T_Object XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	block_op_consistency_check(
			this->property(),
			this->rsize(),
			this->csize(),
			ibgn, jbgn, ni, nj);
	
	T_Scalar *p_vij = bulk::dns::ptrmv(
			this->lsize(),
			this->values(),
			ibgn, jbgn);
	
	T_Object ret;
	ret.wrapper(ni, nj, this->lsize(), p_vij, false, this->property());
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_Object> XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	T_Object tmp = const_cast<XxObjectTmpl&>(*this).getBlockReference(ibgn, jbgn, ni, nj);
	Guard<T_Object> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setBlockCopy(const XxObjectTmpl& src, uint_t ibgn, uint_t jbgn)
{
	T_Object tmp = getBlockReference(ibgn, jbgn, src.rsize(), src.csize());
	src.copyToAllocated(tmp);
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::updateSelfWithScaledOther(T_Scalar alpha, const XxObjectTmpl& other)
{
	op_similarity_check(
			this->property(), 
			this->rsize(), 
			this->csize(), 
			other.property(), 
			other.rsize(), 
			other.csize());

	bulk::dns::update(
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			alpha, other.values(), other.lsize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::createFromScaledSum(
		T_Scalar alpha, const XxObjectTmpl& otherA,
		T_Scalar beta, const XxObjectTmpl& otherB)
{
	op_similarity_check(
			otherA.property(), otherA.rsize(), otherA.csize(), 
			otherB.property(), otherB.rsize(), otherB.csize());

	*this = XxObject(otherA.rsize(), otherA.csize(), otherA.rsize(), otherA.property());

  bulk::dns::add(
			this->property().uplo(), 
			this->rsize(), 
			this->csize(), 
			alpha, otherA.values(), otherA.lsize(), 
			beta, otherB.values(), otherB.lsize(), 
			this->values(), 
			this->lsize());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
template class XxObject<real_t,RdVector>;
template class XxObject<real4_t,RfVector>;
template class XxObject<complex_t,CdVector>;
template class XxObject<complex8_t,CfVector>;
template class XxObject<real_t,RdMatrix>;
template class XxObject<real4_t,RfMatrix>;
template class XxObject<complex_t,CdMatrix>;
template class XxObject<complex8_t,CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
