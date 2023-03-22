// this file inc
#include "dns_cdvector.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = complex_t;
using ThisRealType = real_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<CdVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define RxVector RdVector
#define XxVector CdVector
#define XxVGuard CdVGuard
#define XxMatrix CdMatrix
#define XxMGuard CdMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::COMPLEX, PrecisionType::DOUBLE)
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
