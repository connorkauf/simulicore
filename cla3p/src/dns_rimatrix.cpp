// this file inc
#include "dns_rimatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
using ThisDataType = cla3p::int_t;
using ThisRealType = cla3p::int_t;
using ThisObjectType = cla3p::dns::GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = cla3p::Guard<cla3p::dns::RiMatrix>;
/*-------------------------------------------------*/
#define XxMatrix RiMatrix
#define XxMGuard RiMGuard
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
static cla3p::prop_t propcheck(cla3p::prop_t ptype)
{
	return (ptype == cla3p::prop_t::HERMITIAN ? cla3p::prop_t::SYMMETRIC : ptype);
}
/*-------------------------------------------------*/
#include "dns_xxmatrix.hpp"
/*-------------------------------------------------*/
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
