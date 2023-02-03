#ifndef CLA3P_UTILS_HPP_
#define CLA3P_UTILS_HPP_

#include <string>
#include <vector>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

uint_t inumlen(int_t n);
void sanitize_nsd(uint_t& nsd);
std::string bytes2human(bulk_t nbytes, uint_t nsd = 3);

std::string extract_filename(const std::string& path, const std::string& hint = "");

void fill_info_margins(const std::string& msg, std::string& top, std::string& bottom);

std::string out_of_bounds_message(uint_t m, uint_t n, uint_t i, uint_t j);
std::string out_of_bounds_message(uint_t n, uint_t i);
std::string bool2yn(bool flg);

int_t irand(int_t low, int_t high);
uint_t urand(uint_t low, uint_t high);
real_t drand(real_t low, real_t high);
real4_t srand(real4_t low, real4_t high);
complex_t zrand(real_t low, real_t high);
complex8_t crand(real4_t low, real4_t high);

void fill_random_perm(uint_t n, uint_t *P);
std::vector<uint_t> create_random_perm(uint_t n);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UTILS_HPP_
