#ifndef CLA3P_UTILS_HPP_
#define CLA3P_UTILS_HPP_

#include <string>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

uint_t inumlen(int_t n);
void sanitize_nsd(uint_t& nsd);
std::string bytes2human(bulk_t nbytes, uint_t nsd = 3);

int_t irand(int_t low, int_t high);
uint_t urand(uint_t low, uint_t high);
real_t drand(real_t low, real_t high);
complex_t zrand(real_t low, real_t high);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_UTILS_HPP_
