// this file inc
#include "dns_rdvector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = real_t;
using ThisRealType = real_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RdVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxVector RdVector
#define XxVGuard RdVGuard
#define XxMatrix RdMatrix
#define XxMGuard RdMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::REAL, PrecisionType::DOUBLE)
/*-------------------------------------------------*/
#include "dns_xxvector_source.hpp"
#include "dns_flvector_source.hpp"
/*-------------------------------------------------*/
#undef XxVector
#undef XxVGuard
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
