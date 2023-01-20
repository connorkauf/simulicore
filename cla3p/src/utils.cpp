// this file inc
#include "utils.hpp"

// system
#include <cstdio>
#include <algorithm>

// 3rd

// cla3p

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
std::string bytes2human(bulk_t nbytes, nint_t nsd)
{
	nsd = std::max( 1, nsd);
	nsd = std::min(16, nsd);

	char ret[128];
	real_t rsize = static_cast<real_t>(nbytes);

	if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZETB);
		std::sprintf(ret, "%.*lf Tb", nsd, b2r);
	} else if(nbytes >= SIZEGB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEGB);
		std::sprintf(ret, "%.*lf Gb", nsd, b2r);
	} else if(nbytes >= SIZEMB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEMB);
		std::sprintf(ret, "%.*lf Mb", nsd, b2r);
	} else if(nbytes >= SIZEKB) {
		real_t b2r = rsize / static_cast<real_t>(SIZEKB);
		std::sprintf(ret, "%.*lf Kb", nsd, b2r);
	} else {
		real_t b2r = rsize;
		std::sprintf(ret, "%.*lf b", nsd, b2r);
	} // nbytes
		//
	return ret;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
