// this file inc
#include "dns_xxobject.hpp"

// system

// 3rd

// cla3p
#include "../dense2.hpp"
#include "../bulk/dns.hpp"

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
XxObjectTmpl::~XxObject()
{
}
/*-------------------------------------------------*/
#if 0
XxObjectTlst
void XxObjectTmpl::scale(T_Scalar val)
{
	bulk::dns::scale(uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize(), val);
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normOne() const
{ 
	return bulk::dns::norm_one(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normMax() const
{ 
	return bulk::dns::norm_max(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxObjectTlst
T_RScalar XxObjectTmpl::normFro() const
{ 
	return bulk::dns::norm_fro(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
#endif
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
#undef XxObjectTlst
/*-------------------------------------------------*/
template class XxObject<real_t ,real_t , RdVector2>;
template class XxObject<real4_t,real4_t, RfVector2>;
//template class XxObject<real_t  ,real_t , RdMatrix>;
//template class XxObject<real4_t ,real4_t, RfMatrix>;
template class XxObject<complex_t ,real_t , CdVector2>;
template class XxObject<complex8_t,real4_t, CfVector2>;
//template class XxObject<complex_t ,real_t , CdMatrix>;
//template class XxObject<complex8_t,real4_t, CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
