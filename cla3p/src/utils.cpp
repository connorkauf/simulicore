// this file inc
#include "utils.hpp"

// system
#include <cstdio>
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
template <class T>
static real_t rand_tmpl(T low, T high)
{
	if(low > high) {
		throw NoConsistency("Need low <= high");
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
} // namespace cla3p
/*-------------------------------------------------*/
