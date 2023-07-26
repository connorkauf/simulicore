// this file inc
#include "dns_rdmatrix.hpp"

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
using ThisGuardType = Guard<RdMatrix>;
/*-------------------------------------------------*/
static Property propcheck(const Property& prop)
{
	return (prop.isHermitian() ? Property(prop_t::SYMMETRIC,prop.uplo()) : prop);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxMatrix RdMatrix
#define XxMGuard RdMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::DOUBLE)
/*-------------------------------------------------*/
#include "dns_xxmatrix_source.hpp"
#include "dns_flmatrix_source.hpp"
/*-------------------------------------------------*/
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor
