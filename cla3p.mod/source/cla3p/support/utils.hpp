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

#ifndef CLA3P_UTILS_HPP_
#define CLA3P_UTILS_HPP_

#include <string>
#include <vector>

#include "cla3p/types.hpp"
#include "cla3p/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

uint_t inumlen(int_t n);
void sanitize_nsd(uint_t& nsd);
std::string bytes2human(bulk_t nbytes, uint_t nsd = 3);
void fill_info_margins(const std::string& msg, std::string& top, std::string& bottom);
std::string bool2yn(bool flg);

/*-------------------------------------------------*/
template <typename T_Scalar>
inline T_Scalar opposite_element(const T_Scalar& x, const prop_t& ptype)
{
	if(ptype == prop_t::Symmetric) return x;
	if(ptype == prop_t::Hermitian) return arith::conj(x);
	if(ptype == prop_t::Skew     ) return (-x);

	throw err::Exception("Invalid Property");
	return x;
}
/*-------------------------------------------------*/
template <typename T_Int>
std::string coord2str(T_Int i, T_Int j)
{
	std::string ret = "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar rand(
		typename TypeTraits<T_Scalar>::real_type low, 
		typename TypeTraits<T_Scalar>::real_type high)
{
  if(low > high) {
    throw err::Exception("Need low <= high");
  } // error

	cla3p::real_t rval = static_cast<cla3p::real_t>(std::rand());
	cla3p::real_t diff = static_cast<cla3p::real_t>(high - low);
  cla3p::real_t inc = (rval * diff) / static_cast<cla3p::real_t>(RAND_MAX + 1U);

  return (low + static_cast<T_Scalar>(inc));
}
/*-------------------------------------------------*/
template <>
complex_t rand<complex_t>(real_t low, real_t high); 
template <>
complex8_t rand<complex8_t>(real4_t low, real4_t high);
/*-------------------------------------------------*/

void val2char(char *buff, bulk_t bufflen, uint_t nsd, int_t val);
void val2char(char *buff, bulk_t bufflen, uint_t nsd, uint_t val);
void val2char(char *buff, bulk_t bufflen, uint_t nsd, real_t val);
void val2char(char *buff, bulk_t bufflen, uint_t nsd, real4_t val);
void val2char(char *buff, bulk_t bufflen, uint_t nsd, complex_t val);
void val2char(char *buff, bulk_t bufflen, uint_t nsd, complex8_t val);

uplo_t auto_uplo(prop_t ptype);

void fill_identity_perm(uint_t n, uint_t *P);
void fill_identity_perm(uint_t n, int_t *P);
void fill_random_perm(uint_t n, uint_t *P);
void fill_random_perm(uint_t n, int_t *P);

/*-------------------------------------------------*/
template <typename T_Int>
std::vector<T_Int> create_random_perm(uint_t n)
{
	std::vector<T_Int> ret(n);
	fill_random_perm(n, ret.data());
	return ret;
}
/*-------------------------------------------------*/
typedef struct RowRange {
	uint_t ibgn;
	uint_t iend;
	uint_t ilen;
} RowRange;
/*-------------------------------------------------*/
inline RowRange irange(uplo_t uplo, uint_t m, uint_t j)
{
	RowRange ret;
	ret.ibgn = 0;
	ret.iend = m;
	ret.ilen = m;

	if(!m) return ret;

	if(uplo == uplo_t::Upper) {
		ret.ibgn = 0;
		ret.iend = std::min(j+1,m);
	} else if(uplo == uplo_t::Lower) {
		ret.ibgn = std::min(j,m);
		ret.iend = m;
	} // uplo

	ret.ilen = ret.iend - ret.ibgn;

	return ret;
}
/*-------------------------------------------------*/
inline RowRange irange_strict(uplo_t uplo, uint_t m, uint_t j)
{
	RowRange ret = irange(uplo, m, j);

	if(!m) return ret;

	if(uplo == uplo_t::Upper) {
		ret.iend--;
	} else if(uplo == uplo_t::Lower) {
		ret.ibgn++;
	} // uplo

	ret.ilen = ret.iend - ret.ibgn;

	return ret;
}
/*-------------------------------------------------*/
inline RowRange irange_complement(uplo_t uplo, uint_t m, uint_t j)
{
	RowRange ret;
	ret.ibgn = 0;
	ret.iend = 0;
	ret.ilen = 0;

	if(!m) return ret;

	if(uplo == uplo_t::Upper) {
		ret.ibgn = std::min(j+1,m);
		ret.iend = m;
	} else if(uplo == uplo_t::Lower) {
		ret.ibgn = 0;
		ret.iend = std::min(j,m);
	} // uplo

	ret.ilen = ret.iend - ret.ibgn;

	return ret;
}
/*-------------------------------------------------*/
inline bool coord_in_range(uplo_t uplo, uint_t i, uint_t j)
{
	/**/ if(uplo == uplo_t::Upper && i > j) return false;
	else if(uplo == uplo_t::Lower && i < j) return false;

	return true;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UTILS_HPP_
