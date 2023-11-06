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
#include <string>
#include <cmath>
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
#define SIZEKB 1024LLU 
#define SIZEMB 1048576LLU
#define SIZEGB 1073741824LLU
#define SIZETB 1099511627776LLU
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
std::string bytes2human(bulk_t nbytes, uint_t nsd)
{
#define BUFFER_LEN 128

	sanitize_nsd(nsd);

	nint_t nd = static_cast<nint_t>(nsd);
	char ret[BUFFER_LEN];
	real_t rsize = static_cast<real_t>(nbytes);

	if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZETB);
		std::snprintf(ret, BUFFER_LEN, "%.*lf Tb", nd, b2r);
	} else if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEGB);
		std::snprintf(ret, BUFFER_LEN, "%.*lf Gb", nd, b2r);
	} else if(nbytes >= SIZEMB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEMB);
		std::snprintf(ret, BUFFER_LEN, "%.*lf Mb", nd, b2r);
	} else if(nbytes >= SIZEKB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEKB);
		std::snprintf(ret, BUFFER_LEN, "%.*lf Kb", nd, b2r);
	} else {
		real_t b2r = rsize;
		std::snprintf(ret, BUFFER_LEN, "%.*lf b", nd, b2r);
	} // nbytes

	return ret;

#undef BUFFER_LEN
}
/*-------------------------------------------------*/
std::string extract_filename(const std::string& path, const std::string& hint)
{
	// FIXME: portability

	size_t pos = std::string::npos;

	if(hint.size()) {
		pos = path.rfind(hint);
	} else {
		pos = path.rfind("/");
	} // hint

	std::string ret;

	if(pos != std::string::npos) {
		if(path[pos] == '/') ret = path.substr(pos+1);
		else                 ret = path.substr(pos);
	} // valid pos

	return ret;
}
/*-------------------------------------------------*/
void fill_info_margins(const std::string& msg, std::string& top, std::string& bottom)
{
	const bulk_t deflen = 44;
	const bulk_t msglen = msg.size();

	top.clear();
	bottom.clear();

	if(!msglen) {
		top.resize(deflen, '=');
	} else if(msglen > deflen - 2) {
		top = msg;
	} else {
		bulk_t lenmargin = (deflen - msglen - 2) / 2;
		top.append(lenmargin, '=');
		top.append(" ");
		top.append(msg);
		top.append(" ");
		top.append(lenmargin, '=');
	} // msglen

	bottom.resize(top.size(), '=');
}
/*-------------------------------------------------*/
std::string bool2yn(bool flg)
{
	return (flg ? "Yes" : "No");
}
/*-------------------------------------------------*/
template <typename T>
static real_t rand_tmpl(T low, T high)
{
	if(low > high) {
		throw err::Exception("Need low <= high");
	} // error

	real_t diff = static_cast<real_t>(high - low);
	real_t pct = static_cast<real_t>(std::rand() / static_cast<real_t>(RAND_MAX + 1U));
	real_t ret = static_cast<real_t>(low) + pct * diff;

	return ret;
}
/*-------------------------------------------------*/
int_t irand(int_t low, int_t high)
{
	real_t ret = rand_tmpl(low, high);
	return static_cast<int_t>(std::round(ret));
}
/*-------------------------------------------------*/
uint_t urand(uint_t low, uint_t high)
{
	real_t ret = rand_tmpl(low, high);
	return static_cast<uint_t>(std::round(ret));
}
/*-------------------------------------------------*/
real_t  drand(real_t  low, real_t  high) { return                      rand_tmpl(low, high) ; }
real4_t srand(real4_t low, real4_t high) { return static_cast<real4_t>(rand_tmpl(low, high)); }
/*-------------------------------------------------*/
complex_t  zrand(real_t  low, real_t  high){ return complex_t (drand(low,high), drand(low,high)); }
complex8_t crand(real4_t low, real4_t high){ return complex8_t(srand(low,high), srand(low,high)); }
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, int_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, "%*" _DFMT_ , static_cast<nint_t>(nsd), val);
	} else {
		std::snprintf(buff, bufflen, "%" _DFMT_ , val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, uint_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, "%*" _UFMT_ , static_cast<nint_t>(nsd), val);
	} else {
		std::snprintf(buff, bufflen, "%" _UFMT_ , val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, real_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, " % .*le", static_cast<nint_t>(nsd), val);
	} else {
		std::snprintf(buff, bufflen, " % .le", val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, real4_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, " % .*e", static_cast<nint_t>(nsd), val);
	} else {
		std::snprintf(buff, bufflen, " % .e", val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, complex_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, " (% .*le,% .*le)", 
			static_cast<nint_t>(nsd), val.real(), 
			static_cast<nint_t>(nsd), val.imag());
	} else {
		std::snprintf(buff, bufflen, " (% .le,% .le)", val.real(), val.imag());
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, bulk_t bufflen, uint_t nsd, complex8_t val)
{
	if(nsd) {
		std::snprintf(buff, bufflen, " (% .*e,% .*e)", 
			static_cast<nint_t>(nsd), val.real(), 
			static_cast<nint_t>(nsd), val.imag());
	} else {
		std::snprintf(buff, bufflen, " (% .e,% .e)", val.real(), val.imag());
	} // nsd
}
/*-------------------------------------------------*/
uplo_t auto_uplo(prop_t ptype)
{
	if(ptype == prop_t::General  ) return uplo_t::Full;
	if(ptype == prop_t::Symmetric) return uplo_t::Lower;
	if(ptype == prop_t::Hermitian) return uplo_t::Lower;

	throw err::Exception();
	return uplo_t::Full;
}
/*-------------------------------------------------*/
template <typename T>
static void fill_identity_perm_tmpl(uint_t n, T *P)
{
	for(uint_t i = 0; i < n; i++) {
		P[i] = static_cast<T>(i);
	} // i
}
/*-------------------------------------------------*/
void fill_identity_perm(uint_t n, uint_t *P){ fill_identity_perm_tmpl(n, P); }
void fill_identity_perm(uint_t n,  int_t *P){ fill_identity_perm_tmpl(n, P); }
/*-------------------------------------------------*/
template <typename T>
static void fill_random_perm_tmpl(uint_t n, T *P)
{
	if(!n) return;

	fill_identity_perm(n, P);

	uint_t ilen = n;
	for(uint_t i = 0; i < n - 1; i++) {
		uint_t k = urand(0, ilen-1);
		std::swap(P[k], P[ilen-1]);
		ilen--;
	} // i
}
/*-------------------------------------------------*/
void fill_random_perm(uint_t n, uint_t *P) { fill_random_perm_tmpl(n, P); }
void fill_random_perm(uint_t n,  int_t *P) { fill_random_perm_tmpl(n, P); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
