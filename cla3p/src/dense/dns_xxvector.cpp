// this file inc
#include "dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "../dense2.hpp"
#include "../bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XxVector<T_Scalar,T_RScalar,T_ReturnType>
#define XxVectorTlst template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::values());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
template class XxVector<real_t,real_t,RdVector>;
template class XxVector<real4_t,real4_t,RfVector>;
template class XxVector<complex_t,real_t,CdVector>;
template class XxVector<complex8_t,real4_t,CfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
