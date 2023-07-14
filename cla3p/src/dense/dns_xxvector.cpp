// this file inc
#include "dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "../bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XxVector<T_Scalar,T_RScalar>
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
XxVectorTmpl::XxVector()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::values());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
/*-------------------------------------------------*/
template class XxVector<real_t    ,real_t >;
template class XxVector<real4_t   ,real4_t>;
template class XxVector<complex_t ,real_t >;
template class XxVector<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
