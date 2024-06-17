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

/** 
 * @file
 */

#include <string>
#include <vector>

#include "cla3p/types.hpp"
#include "cla3p/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/*
 * Returns the number of digits of n
 * Sign not included
 */
uint_t inumlen(int_t n);

/*
 * Bounds nsd in [1,16]
 */
void sanitize_nsd(uint_t& nsd);

/*
 * Bytes to human readable string
 * KBytes to human readable string
 * MBytes to human readable string
 */
std::string bytesToString(std::size_t nbytes, uint_t nsd = 3);
std::string kbytesToString(std::size_t nkbytes, uint_t nsd = 3);
std::string mbytesToString(std::size_t nmbytes, uint_t nsd = 3);

/*
 * Fills object info top & bottom margin strings
 */
void fill_info_margins(const std::string& header, std::string& top, std::string& bottom);

/*
 * Boolean to yes/no
 * Boolean to on/off
 */
std::string boolToYesNo(bool flg);
std::string boolToOnOff(bool flg);

/*
 * Given Aij returns Aji depending on property
 */
uint_t opposite_element(const uint_t&, const prop_t&);
template <typename T_Scalar>
T_Scalar opposite_element(const T_Scalar&, const prop_t&);

/*
 * Coordinate to string (i,j)
 */
template <typename T_Int>
std::string coordToString(T_Int i, T_Int j);

/*
 * Value to string
 *
 * if nsd > 0
 *   for integers, nsd: number of spaces for val
 *   for scalars , nsd: number of significant digits
 * if nsd = 0
 *   default spacing
 *
 * Does not sanitize nsd
 */
template <typename T_Scalar>
std::string valToString(T_Scalar val, uint_t nsd);

/*
 * Unified code for Matrix element print in list form
 */
class ListPrinter {
	public:
		ListPrinter(uint_t nsd, uint_t maxRows, uint_t maxCols, uint_t maxNnz);
		~ListPrinter() = default;

		std::string header() const;

		template <typename T_Int, typename T_Scalar>
		std::string tuple(uint_t k, T_Int i, T_Int j, T_Scalar v) const
		{
			std::string ret;
			ret.append(valToString(k, m_ndCount)); ret.append(" | ");
			ret.append(valToString(i, m_ndRows )); ret.append(" ");
			ret.append(valToString(j, m_ndCols )); ret.append("   ");
			ret.append(valToString(v, m_ndVals )); ret.append("\n");
			return ret;
		}

	private:
		nint_t m_ndCount;
		nint_t m_ndRows ;
		nint_t m_ndCols ;
		nint_t m_ndVals ;
};

/*
 * Checks for auto & returns appropriate type
 */
decomp_t determineDecompType(decomp_t, const Property&);

/*-------------------------------------------------*/
typedef struct RowRange {
	uint_t ibgn;
	uint_t iend;
	uint_t ilen;
} RowRange;
/*-------------------------------------------------*/
inline RowRange irange(uplo_t uplo, uint_t m, uint_t j)
{
	RowRange ret = {0, m, m};
	//ret.ibgn = 0;
	//ret.iend = m;
	//ret.ilen = m;

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
	RowRange ret = {0, 0, 0};
	//ret.ibgn = 0;
	//ret.iend = 0;
	//ret.ilen = 0;

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
