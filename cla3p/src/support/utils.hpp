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

uplo_t auto_uplo(prop_t ptype);

void fill_identity_perm(uint_t n, uint_t *P);
void fill_random_perm(uint_t n, uint_t *P);
std::vector<uint_t> create_random_perm(uint_t n);

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

	if(uplo == uplo_t::U) {
		ret.ibgn = 0;
		ret.iend = std::min(j+1,m);
	} else if(uplo == uplo_t::L) {
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

	if(uplo == uplo_t::U) {
		ret.ibgn = std::min(j+1,m);
		ret.iend = m;
	} else if(uplo == uplo_t::L) {
		ret.ibgn = 0;
		ret.iend = std::min(j,m);
	} // uplo

	ret.ilen = ret.iend - ret.ibgn;

	return ret;
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UTILS_HPP_
