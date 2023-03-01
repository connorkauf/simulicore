// this file inc
#include "dns_rimatrix.hpp"

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
using ThisGuardType = Guard<RiMatrix>;
/*-------------------------------------------------*/
static Property propcheck(const Property& prop)
{
	return (prop.isHermitian() ? Property(prop_t::SYMMETRIC,prop.uplo()) : prop);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxMatrix RiMatrix
#define XxMGuard RiMGuard
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::INT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
#include "dns_xxmatrix_source.hpp"
/*-------------------------------------------------*/
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor