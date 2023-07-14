// this file inc
#include "dns_cxvector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxVectorTmpl CxVector<T_Scalar,T_RScalar>
#define CxVectorTlst template <typename T_Scalar, typename T_RScalar>
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector()
{
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::~CxVector()
{
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxVectorTmpl
#undef CxVectorTlst
/*-------------------------------------------------*/
template class CxVector<complex_t,real_t>;
template class CxVector<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
