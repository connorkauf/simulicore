// this file inc
#include "dns_cfvector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = complex8_t;
using ThisRealType = real4_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<CfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define RxVector RfVector
#define XxVector CfVector
#define XxVGuard CfVGuard
#define XxMatrix CfMatrix
#define XxMGuard CfMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::COMPLEX, PrecisionType::SINGLE)
/*-------------------------------------------------*/
#include "dns_xxvector_source.hpp"
#include "dns_cxvector_source.hpp"
#include "dns_flvector_source.hpp"
/*-------------------------------------------------*/
#undef RxVector
#undef XxVector
#undef XxVGuard
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
