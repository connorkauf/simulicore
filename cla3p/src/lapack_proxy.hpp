#ifndef CLA3P_LAPACK_PROXY_HPP_
#define CLA3P_LAPACK_PROXY_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/

real_t lange(char norm, int_t m, int_t n, const real_t *a, int_t lda);
real_t lange(char norm, int_t m, int_t n, const complex_t *a, int_t lda);

real_t lansy(char norm, char uplo, int_t n, const real_t *a, int_t lda);
real_t lansy(char norm, char uplo, int_t n, const complex_t *a, int_t lda);

real_t lanhe(char norm, char uplo, int_t n, const real_t *a, int_t lda); // same as lansy
real_t lanhe(char norm, char uplo, int_t n, const complex_t *a, int_t lda);

/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_PROXY_HPP_
