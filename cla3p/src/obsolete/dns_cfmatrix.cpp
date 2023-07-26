// this file inc
#include "dns_cfmatrix.hpp"

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
using ThisGuardType = Guard<CfMatrix>;
/*-------------------------------------------------*/
static Property propcheck(const Property& prop)
{
	return prop;
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define RxMatrix RfMatrix
#define XxMatrix CfMatrix
#define XxMGuard CfMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::COMPLEX, PrecisionType::SINGLE)
/*-------------------------------------------------*/
#include "dns_xxmatrix_source.hpp"
#include "dns_cxmatrix_source.hpp"
#include "dns_flmatrix_source.hpp"
/*-------------------------------------------------*/
#undef RxMatrix
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
