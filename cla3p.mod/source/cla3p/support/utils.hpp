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

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

uint_t inumlen(int_t n);
void sanitize_nsd(uint_t& nsd);
std::string bytes2human(bulk_t nbytes, uint_t nsd = 3);
std::string extract_filename(const std::string& path, const std::string& hint = "");
void fill_info_margins(const std::string& msg, std::string& top, std::string& bottom);
std::string bool2yn(bool flg);

int_t irand(int_t low, int_t high);
uint_t urand(uint_t low, uint_t high);
real_t drand(real_t low, real_t high);
real4_t srand(real4_t low, real4_t high);
complex_t zrand(real_t low, real_t high);
complex8_t crand(real4_t low, real4_t high);

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

template <typename T>
std::vector<T> create_random_perm(uint_t n)
{
	std::vector<T> ret(n);
	fill_random_perm(n, ret.data());
	return ret;
}

typedef struct RowRange {
	uint_t ibgn;
	uint_t iend;
	uint_t ilen;
} RowRange;

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
