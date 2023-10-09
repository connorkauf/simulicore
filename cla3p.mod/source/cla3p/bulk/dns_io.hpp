#ifndef CLA3P_BULK_DNS_IO_HPP_
#define CLA3P_BULK_DNS_IO_HPP_

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);

void print(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_IO_HPP_