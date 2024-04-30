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

// this file inc
#include "cla3p/checks/coo_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/utils.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/checks/basic_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void coo_consistency_check(const Property& prop, uint_t m, uint_t n)
{
	if(!m || !n) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}

	property_compatibility_check(prop, m, n);
}
/*-------------------------------------------------*/
template <typename T_Int>
void coo_check_coord(uint_t m, uint_t n, const Property& prop, const T_Int& i, const T_Int& j)
{
	if(
			i <  static_cast<T_Int>(0) ||
			i >= static_cast<T_Int>(m) || 
			j <  static_cast<T_Int>(0) ||
			j >= static_cast<T_Int>(n)
		)
	{
		throw err::OutOfBounds(msg::IndexOutOfBounds(m,n,i,j));
	}

	if(prop.isLower() && i < j) {
		throw err::InvalidOp("Invalid insertion of " + coord2str(i,j) + " in upper part");
	}

	if(prop.isUpper() && i > j) {
		throw err::InvalidOp("Invalid insertion of " + coord2str(i,j) + " in lower part");
	}

	if(prop.isSkew() && i == j) {
		throw err::InvalidOp(msg::SkewInconsistency() + " (value on diagonal)");
	}
}
/*-------------------------------------------------*/
template void coo_check_coord(uint_t, uint_t, const Property&, const int_t&, const int_t&);
template void coo_check_coord(uint_t, uint_t, const Property&, const uint_t&, const uint_t&);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void coo_check_triplet(uint_t m, uint_t n, const Property& prop, const T_Int& i, const T_Int& j, const T_Scalar& v)
{
	coo_check_coord(m, n, prop, i, j);

	if(prop.isHermitian() && i == j && arith::getIm(v)) {
		throw err::InvalidOp(msg::HermitianInconsistency() + " (imaginary value on diagonal)");
	}
}
/*-------------------------------------------------*/
template void coo_check_triplet(uint_t, uint_t, const Property&, const int_t&, const int_t&, const real_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const int_t&, const int_t&, const real4_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const int_t&, const int_t&, const complex_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const int_t&, const int_t&, const complex8_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const uint_t&, const uint_t&, const real_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const uint_t&, const uint_t&, const real4_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const uint_t&, const uint_t&, const complex_t&);
template void coo_check_triplet(uint_t, uint_t, const Property&, const uint_t&, const uint_t&, const complex8_t&);
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
