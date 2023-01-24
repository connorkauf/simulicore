#ifndef CLA3P_MKL_PROXY_HPP_
#define CLA3P_MKL_PROXY_HPP_

#include <stddef.h>
#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

std::string version();

void omatcopy(char ordering, char trans, size_t rows, size_t cols, real_t alpha, const real_t *a, size_t lda, real_t *b, size_t ldb);
void omatcopy(char ordering, char trans, size_t rows, size_t cols, real4_t alpha, const real4_t *a, size_t lda, real4_t *b, size_t ldb);
void omatcopy(char ordering, char trans, size_t rows, size_t cols, complex_t alpha, const complex_t *a, size_t lda, complex_t *b, size_t ldb);
void omatcopy(char ordering, char trans, size_t rows, size_t cols, complex8_t alpha, const complex8_t *a, size_t lda, complex8_t *b, size_t ldb);

void imatcopy(char ordering, char trans, size_t rows, size_t cols, real_t alpha, real_t *a, size_t lda, size_t ldb);
void imatcopy(char ordering, char trans, size_t rows, size_t cols, real4_t alpha, real4_t *a, size_t lda, size_t ldb);
void imatcopy(char ordering, char trans, size_t rows, size_t cols, complex_t alpha, complex_t *a, size_t lda, size_t ldb);
void imatcopy(char ordering, char trans, size_t rows, size_t cols, complex8_t alpha, complex8_t *a, size_t lda, size_t ldb);

/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_PROXY_HPP_
