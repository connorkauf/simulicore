// this file inc
#include "dns_rfmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
using ThisDataType = cla3p::real4_t;
using ThisRealType = cla3p::real4_t;
using ThisObjectType = cla3p::dns::GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = cla3p::Guard<cla3p::dns::RfMatrix>;
/*-------------------------------------------------*/
#define XxMatrix RfMatrix
#define XxMGuard RfMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::SINGLE)
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
