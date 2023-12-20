/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

// TODO: delete this file & use sanitizeProperty when 
//       property is removed from the Array2D class

template< typename T_Scalar>
inline Property checkProperty(const Property& pr);

template<> inline Property checkProperty<int_t>     (const Property& pr) { return (pr.isHermitian() ? Property(prop_t::Symmetric, pr.uplo()) : pr); }
template<> inline Property checkProperty<uint_t>    (const Property& pr) { return (pr.isHermitian() ? Property(prop_t::Symmetric, pr.uplo()) : pr); }
template<> inline Property checkProperty<real_t>    (const Property& pr) { return (pr.isHermitian() ? Property(prop_t::Symmetric, pr.uplo()) : pr); }
template<> inline Property checkProperty<real4_t>   (const Property& pr) { return (pr.isHermitian() ? Property(prop_t::Symmetric, pr.uplo()) : pr); }
template<> inline Property checkProperty<complex_t> (const Property& pr) { return pr; }
template<> inline Property checkProperty<complex8_t>(const Property& pr) { return pr; }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PROPERTY_INTERNAL_HPP_
