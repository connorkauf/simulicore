#ifndef CLA3P_PROPERTY_INTERNAL_HPP_
#define CLA3P_PROPERTY_INTERNAL_HPP_

/** 
 * @file
 * Property configuration
 */

#include "cla3p/types/integer.hpp"
#include "cla3p/types/scalar.hpp"
#include "cla3p/types/property.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template< typename T_Scalar>
inline Property checkProperty(const Property& pr);

template<> inline Property checkProperty<int_t>(const Property& pr) { return (pr.isHermitian() ? Property(prop_t::SYMMETRIC, pr.uplo()) : pr); }
template<> inline Property checkProperty<uint_t>(const Property& pr) { return (pr.isHermitian() ? Property(prop_t::SYMMETRIC, pr.uplo()) : pr); }
template<> inline Property checkProperty<real_t>(const Property& pr) { return (pr.isHermitian() ? Property(prop_t::SYMMETRIC, pr.uplo()) : pr); }
template<> inline Property checkProperty<real4_t>(const Property& pr) { return (pr.isHermitian() ? Property(prop_t::SYMMETRIC, pr.uplo()) : pr); }
template<> inline Property checkProperty<complex_t>(const Property& pr) { return pr; }
template<> inline Property checkProperty<complex8_t>(const Property& pr) { return pr; }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PROPERTY_INTERNAL_HPP_
