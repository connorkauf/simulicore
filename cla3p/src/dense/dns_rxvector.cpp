// this file inc
#include "dns_rxvector.hpp"

// system

// 3rd

// cla3p
//#include "../bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define RxVectorTmpl RxVector<T_Scalar>
#define RxVectorTlst template <typename T_Scalar>
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector()
{
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::~RxVector()
{
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxVectorTmpl
#undef RxVectorTlst
/*-------------------------------------------------*/
template class RxVector<real_t>;
template class RxVector<real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
