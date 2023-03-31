#ifndef CLA3P_BULK_DNS_DECOMP_HPP_
#define CLA3P_BULK_DNS_DECOMP_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

//
// (P*L)*B = B
// (P*U)*B = B
//
void itrsm_lln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
void itrsm_lun(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// D*B = B
//
int_t itrsm_lld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
int_t itrsm_lud(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// (P*L)'*B = B
// (P*U)'*B = B
//
void itrsm_llt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
void itrsm_lut(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*(P*L) = B or (P*L)'*B' = B'
// B*(P*U) = B or (P*U)'*B' = B'
//
void itrsm_rln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
void itrsm_run(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*D = B or D*B' = B'
//
int_t itrsm_rld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
int_t itrsm_rud(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*(P*L)' = B or (P*L)*B' = B'
// B*(P*U)' = B or (P*U)*B' = B'
//
void itrsm_rlt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);
void itrsm_rut(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// tr: Apply ipiv to a and zero 2x2 off diag
// ge: Apply ipiv to a left side
//
void itrperm(char uplo, int_t n, real_t *a, int_t lda, const int_t *ipiv1);
void igeperm(char order, char trans, int_t m, int_t n, real_t *a, int_t lda, const int_t *ipiv1);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_DECOMP_HPP_
