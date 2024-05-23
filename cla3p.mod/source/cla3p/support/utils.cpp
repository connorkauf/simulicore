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
#include "cla3p/support/utils.hpp"

// system
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
uint_t inumlen(int_t n)
{
	uint_t len = 1;

	while(n /= 10)
		len++;

	return len;
}
/*-------------------------------------------------*/
void sanitize_nsd(uint_t& nsd)
{
	const uint_t nsd_min =  1;
	const uint_t nsd_max = 16;

	nsd = std::max(nsd, nsd_min);
	nsd = std::min(nsd, nsd_max);
}
/*-------------------------------------------------*/
static constexpr std::size_t SIZEKB = 1024LLU;
static constexpr std::size_t SIZEMB = 1048576LLU;
static constexpr std::size_t SIZEGB = 1073741824LLU;
static constexpr std::size_t SIZETB = 1099511627776LLU;
/*-------------------------------------------------*/
static std::string bytesToString(std::size_t nbytes, uint_t nsd, std::size_t base, const char *suffix)
{
	constexpr std::size_t BUFFER_LEN = 128;
	char ret[BUFFER_LEN];

	sanitize_nsd(nsd);
	nint_t nd = static_cast<nint_t>(nsd);

	real_t scaledBytes = static_cast<real_t>(nbytes) / static_cast<real_t>(base);

	std::snprintf(ret, BUFFER_LEN, "%.*lf %s", nd, scaledBytes, suffix);

	return ret;
}
/*-------------------------------------------------*/
std::string bytesToString(std::size_t nbytes, uint_t nsd)
{
	if(nbytes >= SIZETB)
		return bytesToString(nbytes, nsd, SIZETB, "Tb");

	else if(nbytes >= SIZEGB)
		return bytesToString(nbytes, nsd, SIZEGB, "Gb");

	else if(nbytes >= SIZEMB)
		return bytesToString(nbytes, nsd, SIZEMB, "Mb");

	else if(nbytes >= SIZEKB)
		return bytesToString(nbytes, nsd, SIZEKB, "Kb");

	else
		return bytesToString(nbytes, nsd, 1, "b");
}
/*-------------------------------------------------*/
std::string kbytesToString(std::size_t nkbytes, uint_t nsd)
{
	return bytesToString(nkbytes * SIZEKB, nsd);
}
/*-------------------------------------------------*/
std::string mbytesToString(std::size_t nmbytes, uint_t nsd)
{
	return bytesToString(nmbytes * SIZEMB, nsd);
}
/*-------------------------------------------------*/
void fill_info_margins(const std::string& header, std::string& top, std::string& bottom)
{
	const bulk_t deflen = 44;
	const bulk_t msglen = header.size();

	top.clear();
	bottom.clear();

	if(!msglen) {
		top.resize(deflen, '=');
	} else if(msglen > deflen - 2) {
		top = header;
	} else {
		bulk_t lenmargin = (deflen - msglen - 2) / 2;
		top.append(lenmargin, '=');
		top.append(" ");
		top.append(header);
		top.append(" ");
		top.append(lenmargin, '=');
	} // msglen

	bottom.resize(top.size(), '=');
}
/*-------------------------------------------------*/
std::string boolToYesNo(bool flg)
{
	return (flg ? "Yes" : "No");
}
/*-------------------------------------------------*/
std::string boolToOnOff(bool flg)
{
	return (flg ? "On" : "Off");
}
/*-------------------------------------------------*/
uint_t opposite_element(const uint_t& x, const prop_t&)
{
  throw err::Exception("Invalid Datatype");
  return x;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar opposite_element(const T_Scalar& x, const prop_t& ptype)
{
  if(ptype == prop_t::Symmetric)
		return x;

  if(ptype == prop_t::Hermitian)
		return arith::conj(x);

  if(ptype == prop_t::Skew)
		return (-x);

  throw err::Exception("Invalid Property");
  return x;
}
/*-------------------------------------------------*/
template int_t      opposite_element(const int_t     &, const prop_t&);
template real_t     opposite_element(const real_t    &, const prop_t&);
template real4_t    opposite_element(const real4_t   &, const prop_t&);
template complex_t  opposite_element(const complex_t &, const prop_t&);
template complex8_t opposite_element(const complex8_t&, const prop_t&);
/*-------------------------------------------------*/
template <typename T_Int>
std::string coordToString(T_Int i, T_Int j)
{
  std::string ret = "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
  return ret;
}
/*-------------------------------------------------*/
template std::string coordToString(int_t , int_t );
template std::string coordToString(uint_t, uint_t);
/*-------------------------------------------------*/
template <typename T_Int>
static T_Int randomCaseInt(T_Int lo, T_Int hi)
{
	T_Int diff = hi - lo;
	T_Int stdRandVal = std::rand();
	T_Int inc = stdRandVal % diff;
	return (lo + inc);
}
/*-------------------------------------------------*/
template int_t  randomCaseInt(int_t , int_t );
template uint_t randomCaseInt(uint_t, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCaseReal(T_Scalar lo, T_Scalar hi)
{
  T_Scalar diff = hi - lo;
	T_Scalar stdRandVal = static_cast<T_Scalar>(std::rand());
  T_Scalar inc = diff * (stdRandVal / static_cast<T_Scalar>(RAND_MAX + 1U));
	return (lo + inc);
}
/*-------------------------------------------------*/
template real_t  randomCaseReal(real_t , real_t );
template real4_t randomCaseReal(real4_t, real4_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCaseComplex(
		typename TypeTraits<T_Scalar>::real_type lo, 
		typename TypeTraits<T_Scalar>::real_type hi)
{
	return T_Scalar(randomCaseReal(lo,hi), randomCaseReal(lo,hi));
}
/*-------------------------------------------------*/
template complex_t  randomCaseComplex(real_t , real_t );
template complex8_t randomCaseComplex(real4_t, real4_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCase(
		typename TypeTraits<T_Scalar>::real_type lo,
		typename TypeTraits<T_Scalar>::real_type hi);
/*-------------------------------------------------*/
template<> int_t  randomCase<int_t >(int_t  lo, int_t  hi) { return randomCaseInt<int_t >(lo,hi); }
template<> uint_t randomCase<uint_t>(uint_t lo, uint_t hi) { return randomCaseInt<uint_t>(lo,hi); }
/*-------------------------------------------------*/
template<> real_t  randomCase<real_t >(real_t  lo, real_t  hi) { return randomCaseReal<real_t >(lo,hi); }
template<> real4_t randomCase<real4_t>(real4_t lo, real4_t hi) { return randomCaseReal<real4_t>(lo,hi); }
/*-------------------------------------------------*/
template<> complex_t  randomCase<complex_t >(real_t  lo, real_t  hi) { return randomCaseComplex<complex_t >(lo,hi); }
template<> complex8_t randomCase<complex8_t>(real4_t lo, real4_t hi) { return randomCaseComplex<complex8_t>(lo,hi); }
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar rand(
		typename TypeTraits<T_Scalar>::real_type lo,
		typename TypeTraits<T_Scalar>::real_type hi)
{
	if(lo > hi)
		throw err::Exception("Need lo <= hi");

	return randomCase<T_Scalar>(lo,hi);
}
/*-------------------------------------------------*/
template int_t      rand(int_t  , int_t  );
template uint_t     rand(uint_t , uint_t );
template real_t     rand(real_t , real_t );
template real4_t    rand(real4_t, real4_t);
template complex_t  rand(real_t , real_t );
template complex8_t rand(real4_t, real4_t);
/*-------------------------------------------------*/
static std::string valToStringSpec(int_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "%*" _DFMT_ , static_cast<nint_t>(nsd), val);
	else
		std::snprintf(ret, BUFFER_LEN, "%" _DFMT_ , val);

	return ret;
}
/*-------------------------------------------------*/
static std::string valToStringSpec(uint_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "%*" _UFMT_ , static_cast<nint_t>(nsd), val);
	else
		std::snprintf(ret, BUFFER_LEN, "%" _UFMT_ , val);

	return ret;
}
/*-------------------------------------------------*/
static std::string valToStringSpec(real_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "% .*le" , static_cast<nint_t>(nsd), val);
	else
		std::snprintf(ret, BUFFER_LEN, "% le" , val);

	return ret;
}
/*-------------------------------------------------*/
static std::string valToStringSpec(real4_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "% .*e" , static_cast<nint_t>(nsd), val);
	else
		std::snprintf(ret, BUFFER_LEN, "% e" , val);

	return ret;
}
/*-------------------------------------------------*/
static std::string valToStringSpec(complex_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "(% .*le,% .*le)", 
				static_cast<nint_t>(nsd), val.real(), 
				static_cast<nint_t>(nsd), val.imag());
	else
		std::snprintf(ret, BUFFER_LEN, "(% le,% le)", val.real(), val.imag());

	return ret;
}
/*-------------------------------------------------*/
static std::string valToStringSpec(complex8_t val, uint_t nsd)
{
	constexpr std::size_t BUFFER_LEN = 64;
	char ret[BUFFER_LEN];

	if(nsd)
		std::snprintf(ret, BUFFER_LEN, "(% .*e,% .*e)", 
			static_cast<nint_t>(nsd), val.real(), 
			static_cast<nint_t>(nsd), val.imag());
	else
		std::snprintf(ret, BUFFER_LEN, "(% e,% e)", val.real(), val.imag());
	
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string valToString(T_Scalar val, uint_t nsd)
{
	return valToStringSpec(val, nsd);
}
/*-------------------------------------------------*/
template std::string valToString(int_t     , uint_t);
template std::string valToString(uint_t    , uint_t);
template std::string valToString(real_t    , uint_t);
template std::string valToString(real4_t   , uint_t);
template std::string valToString(complex_t , uint_t);
template std::string valToString(complex8_t, uint_t);
/*-------------------------------------------------*/
ListPrinter::ListPrinter(uint_t nsd, uint_t maxRows, uint_t maxCols, uint_t maxNnz)
{
	m_ndCount = std::max(5, static_cast<nint_t>(inumlen(maxNnz )));
	m_ndRows  = std::max(5, static_cast<nint_t>(inumlen(maxRows)));
	m_ndCols  = std::max(8, static_cast<nint_t>(inumlen(maxCols)));
	m_ndVals  = static_cast<nint_t>(nsd);
}
/*-------------------------------------------------*/
std::string ListPrinter::header() const
{
	char cbuff[512];
	std::snprintf(cbuff, 512, "%*s | %*s %*s %s", m_ndCount, "#nz", m_ndRows, "row", m_ndCols, "column", "  value");

	std::string ret;
	ret.append(cbuff);
	ret.append("\n");
	ret.append(std::strlen(cbuff), '-');
	ret.append("\n");

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
void fill_identity_perm(uint_t n, T_Int *P)
{
	for(uint_t i = 0; i < n; i++) {
		P[i] = static_cast<T_Int>(i);
	} // i
}
/*-------------------------------------------------*/
template void fill_identity_perm(uint_t, uint_t*);
template void fill_identity_perm(uint_t, int_t*);
/*-------------------------------------------------*/
template <typename T_Int>
void fill_random_perm(uint_t n, T_Int *P)
{
	if(!n) return;

	fill_identity_perm(n, P);

	uint_t ilen = n;
	for(uint_t i = 0; i < n - 1; i++) {
		uint_t k = rand<T_Int>(0, ilen-1);
		std::swap(P[k], P[ilen-1]);
		ilen--;
	} // i
}
/*-------------------------------------------------*/
template void fill_random_perm(uint_t, uint_t*);
template void fill_random_perm(uint_t, int_t*);
/*-------------------------------------------------*/
decomp_t determineDecompType(decomp_t dtype, const Property& pr)
{
	decomp_t ret = dtype;

	if(ret == decomp_t::Auto) {

		if(pr.isSymmetric() || pr.isHermitian())
			ret = decomp_t::LDLT;

		else if(pr.isGeneral())
			ret = decomp_t::LU;

	} // auto

	return ret;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
