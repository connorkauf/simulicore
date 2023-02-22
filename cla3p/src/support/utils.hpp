#ifndef CLA3P_UTILS_HPP_
#define CLA3P_UTILS_HPP_

#include <string>
#include <vector>

#include "../types.hpp"

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

void fill_random_perm(uint_t n, uint_t *P);
std::vector<uint_t> create_random_perm(uint_t n);

typedef struct RowRange {
	int_t ibgn;
	int_t iend;
	int_t ilen;
} RowRange;

inline RowRange irange(uplo_t uplo, int_t m, int_t n, int_t j)
{
	RowRange ret;
	ret.ibgn = 0;
	ret.iend = m;
	ret.ilen = m;

	if(uplo == uplo_t::U) {
		ret.ibgn = 0;
		ret.iend = j+1;
		ret.ilen = j+1;
	} else if(uplo == uplo_t::L) {
		ret.ibgn = j;
		ret.iend = m;
		ret.ilen = m-j;
	} // uplo

	return ret;
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UTILS_HPP_
