// this file inc
#include "dns_rfvector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = real4_t;
using ThisRealType = real4_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxVector RfVector
#define XxVGuard RfVGuard
#define XxMatrix RfMatrix
#define XxMGuard RfMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::REAL, PrecisionType::SINGLE)
/*-------------------------------------------------*/
#include "dns_xxvector_source.hpp"
#include "dns_flvector_source.hpp"
/*-------------------------------------------------*/
#undef XxVector
#undef XxVGuard
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
