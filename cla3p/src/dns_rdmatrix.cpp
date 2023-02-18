// this file inc
#include "dns_rdmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
using ThisDataType = cla3p::real_t;
using ThisRealType = cla3p::real_t;
using ThisObjectType = cla3p::dns::GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = cla3p::Guard<cla3p::dns::RdMatrix>;
/*-------------------------------------------------*/
#define XxMatrix RdMatrix
#define XxMGuard RdMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::DOUBLE)
/*-------------------------------------------------*/
static cla3p::prop_t propcheck(cla3p::prop_t ptype)
{
	return (ptype == cla3p::prop_t::HERMITIAN ? cla3p::prop_t::SYMMETRIC : ptype);
}
/*-------------------------------------------------*/
#include "dns_xxmatrix.hpp"
#include "dns_flmatrix.hpp"
/*-------------------------------------------------*/
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
