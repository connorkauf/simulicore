// this file inc
#include "dns_xxobject.hpp"

// system

// 3rd

// cla3p
#include "../dense2.hpp"
#include "../bulk/dns.hpp"
#include "../checks/all_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject<T_Scalar,T_RScalar,T_ReturnType>
#define XxObjectTlst template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
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
T_ReturnType XxObjectTmpl::copy() const
{
	T_ReturnType ret;
	Array2D<T_Scalar>::copyTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_ReturnType XxObjectTmpl::rcopy()
{
	T_ReturnType ret;
	Array2D<T_Scalar>::copyToShallow(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_ReturnType> XxObjectTmpl::rcopy() const
{
	T_ReturnType tmp;
	const_cast<XxObjectTmpl&>(*this).copyToShallow(tmp);
	Guard<T_ReturnType> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
T_ReturnType XxObjectTmpl::move()
{
	T_ReturnType ret;
	Array2D<T_Scalar>::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::scale(T_Scalar val)
{
	bulk::dns::scale(
			Array2D<T_Scalar>::property().uplo(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize(), val);
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normOne() const
{ 
	return bulk::dns::norm_one(
			Array2D<T_Scalar>::property().type(),
			Array2D<T_Scalar>::property().uplo(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(
			Array2D<T_Scalar>::property().type(),
			Array2D<T_Scalar>::property().uplo(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_ReturnType XxObjectTmpl::getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Guard<T_ReturnType> tmp = getBlockReference(ibgn, jbgn, ni, nj);
	return tmp.get().copy();
}
/*-------------------------------------------------*/
XxObjectTlst
T_ReturnType XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	block_op_consistency_check(
			Array2D<T_Scalar>::property(),
			Array2D<T_Scalar>::rsize(),
			Array2D<T_Scalar>::csize(),
			ibgn, jbgn, ni, nj);
	
	T_Scalar *p_vij = bulk::dns::ptrmv(
			Array2D<T_Scalar>::lsize(),
			Array2D<T_Scalar>::values(),
			ibgn, jbgn);
	
	T_ReturnType ret;
	ret.wrapper(ni, nj, Array2D<T_Scalar>::lsize(), p_vij, false, Array2D<T_Scalar>::property());
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
Guard<T_ReturnType> XxObjectTmpl::getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	T_ReturnType tmp = const_cast<XxObjectTmpl&>(*this).getBlockReference(ibgn, jbgn, ni, nj);
	Guard<T_ReturnType> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
XxObjectTlst
void XxObjectTmpl::setBlockCopy(const XxObjectTmpl& src, uint_t ibgn, uint_t jbgn)
{
	T_ReturnType tmp = getBlockReference(ibgn, jbgn, src.rsize(), src.csize());
	src.copyToAllocated(tmp);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
template class XxObject<real_t,real_t,RdVector2>;
template class XxObject<real4_t,real4_t,RfVector2>;
template class XxObject<complex_t,real_t,CdVector2>;
template class XxObject<complex8_t,real4_t,CfVector2>;
template class XxObject<real_t,real_t,RdMatrix2>;
template class XxObject<real4_t,real4_t,RfMatrix2>;
template class XxObject<complex_t,real_t,CdMatrix2>;
template class XxObject<complex8_t,real4_t,CfMatrix2>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
