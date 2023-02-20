// this file inc
#include "dns_rivector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = int_t;
using ThisRealType = int_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RiVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxVector RiVector
#define XxVGuard RiVGuard
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::INT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::INT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
#include "dns_xxvector_source.hpp"
/*-------------------------------------------------*/
#undef XxVector
#undef XxVGuard
#undef UniversalConstructor
