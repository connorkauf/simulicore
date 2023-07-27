// this file inc
#include "utils.hpp"

// system
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>

// 3rd

// cla3p
#include "error.hpp"

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
	sanitize_nsd(nsd);

	nint_t nd = nsd;
	char ret[128];
	real_t rsize = static_cast<real_t>(nbytes);

	if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZETB);
		std::sprintf(ret, "%.*lf Tb", nd, b2r);
	} else if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEGB);
		std::sprintf(ret, "%.*lf Gb", nd, b2r);
	} else if(nbytes >= SIZEMB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEMB);
		std::sprintf(ret, "%.*lf Mb", nd, b2r);
	} else if(nbytes >= SIZEKB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEKB);
		std::sprintf(ret, "%.*lf Kb", nd, b2r);
	} else {
		real_t b2r = rsize;
		std::sprintf(ret, "%.*lf b", nd, b2r);
	} // nbytes
		//
	return ret;
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
		throw Exception("Need low <= high");
	} // error

	real_t diff = static_cast<real_t>(high - low);
	real_t pct = static_cast<real_t>(std::rand() / static_cast<real_t>(RAND_MAX + 1U));
	real_t ret = static_cast<real_t>(low) + pct * diff;

	return ret;
}
/*-------------------------------------------------*/
int_t irand(int_t low, int_t high)
{
	int_t ret = rand_tmpl(low, high);
	return std::round(ret);
}
/*-------------------------------------------------*/
uint_t urand(uint_t low, uint_t high)
{
	int_t ret = rand_tmpl(low, high);
	return std::round(ret);
}
/*-------------------------------------------------*/
real_t  drand(real_t  low, real_t  high) { return                      rand_tmpl(low, high) ; }
real4_t srand(real4_t low, real4_t high) { return static_cast<real4_t>(rand_tmpl(low, high)); }
/*-------------------------------------------------*/
complex_t  zrand(real_t  low, real_t  high){ return complex_t (drand(low,high), drand(low,high)); }
complex8_t crand(real4_t low, real4_t high){ return complex8_t(srand(low,high), srand(low,high)); }
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, int_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, "%*" _DFMT_ , nd, val);
	} else {
		std::sprintf(buff, "%" _DFMT_ , val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, uint_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, "%*" _UFMT_ , nd, val);
	} else {
		std::sprintf(buff, "%" _UFMT_ , val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, real_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, " % .*le", nd, val);
	} else {
		std::sprintf(buff, " % .le", val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, real4_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, " % .*e", nd, val);
	} else {
		std::sprintf(buff, " % .e", val);
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, complex_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, " (% .*le,% .*le)", nd, val.real(), nd, val.imag());
	} else {
		std::sprintf(buff, " (% .le,% .le)", val.real(), val.imag());
	} // nsd
}
/*-------------------------------------------------*/
void val2char(char *buff, uint_t nsd, complex8_t val)
{
	if(nsd) {
		nint_t nd = nsd;
		std::sprintf(buff, " (% .*e,% .*e)", nd, val.real(), nd, val.imag());
	} else {
		std::sprintf(buff, " (% .e,% .e)", val.real(), val.imag());
	} // nsd
}
/*-------------------------------------------------*/
uplo_t auto_uplo(prop_t ptype)
{
	if(ptype == prop_t::GENERAL  ) return uplo_t::F;
	if(ptype == prop_t::SYMMETRIC) return uplo_t::L;
	if(ptype == prop_t::HERMITIAN) return uplo_t::L;

	throw Exception();
	return uplo_t::F;
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
