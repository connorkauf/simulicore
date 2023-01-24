#ifndef CLA3P_DNS_IO_HPP_
#define CLA3P_DNS_IO_HPP_

#include <string>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/

std::string print2str(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print2str(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print2str(uint_t m, uint_t n, const complex_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print2str(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);

void print(uint_t m, uint_t n, const real_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uint_t m, uint_t n, const real4_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uint_t m, uint_t n, const complex_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uint_t m, uint_t n, const complex8_t *a, uint_t lda, bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_IO_HPP_
