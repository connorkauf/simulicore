// this file inc
#include "lapack_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/
real_t  lange(char norm, int_t m, int_t n, const real_t     *a, int_t lda) { return LAPACKE_dlange(LAPACK_COL_MAJOR, norm, m, n, a, lda); }
real4_t lange(char norm, int_t m, int_t n, const real4_t    *a, int_t lda) { return LAPACKE_slange(LAPACK_COL_MAJOR, norm, m, n, a, lda); }
real_t  lange(char norm, int_t m, int_t n, const complex_t  *a, int_t lda) { return LAPACKE_zlange(LAPACK_COL_MAJOR, norm, m, n, a, lda); }
real4_t lange(char norm, int_t m, int_t n, const complex8_t *a, int_t lda) { return LAPACKE_clange(LAPACK_COL_MAJOR, norm, m, n, a, lda); }
/*-------------------------------------------------*/
real_t  lansy(char norm, char uplo, int_t n, const real_t     *a, int_t lda) { return LAPACKE_dlansy(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
real4_t lansy(char norm, char uplo, int_t n, const real4_t    *a, int_t lda) { return LAPACKE_slansy(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
real_t  lansy(char norm, char uplo, int_t n, const complex_t  *a, int_t lda) { return LAPACKE_zlansy(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
real4_t lansy(char norm, char uplo, int_t n, const complex8_t *a, int_t lda) { return LAPACKE_clansy(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
/*-------------------------------------------------*/
real_t  lanhe(char norm, char uplo, int_t n, const real_t  *a, int_t lda) { return lansy(norm, uplo, n, a, lda); }
real4_t lanhe(char norm, char uplo, int_t n, const real4_t *a, int_t lda) { return lansy(norm, uplo, n, a, lda); }
/*-------------------------------------------------*/
real_t  lanhe(char norm, char uplo, int_t n, const complex_t  *a, int_t lda) { return LAPACKE_zlanhe(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
real4_t lanhe(char norm, char uplo, int_t n, const complex8_t *a, int_t lda) { return LAPACKE_clanhe(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); }
/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/
