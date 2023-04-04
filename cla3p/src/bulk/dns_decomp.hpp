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
void igeperm(int_t off, char order, char trans, int_t m, int_t n, real_t *a, int_t lda, const int_t *ipiv1);

//
// example for using itrperm() & igeperm()
// work(n x n)
//
void itrsm_left_blas3(char uplo, int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1, real_t *work);

//
// Y = X * D
// D(k x k)
// X(n x k)
// Y(n x k)
//
void iscal(char uplo, int_t n, int_t k, const real_t *d, int_t ldd, const real_t *x, int_t ldx, real_t *y, int_t ldy, const int_t *ipiv1);

//
// C += alpha * X * D * X'
// C(n x n)
// D(k x k)
// X(n x k)
// work(n x k)
//
void isyrk(char uplo, int_t n, int_t k, real_t alpha, 
		const real_t *d, int_t ldd, 
		const real_t *x, int_t ldx, const int_t *ipiv1, 
		real_t *c, int ldc, real_t *work);

//
// C += alpha * X * D * Y'
// C(m x n)
// D(k x k)
// X(m x k)
// Y(n x k)
// work(min(m,n) x k)
//
void igerk(char uplo, int_t m, int_t n, int_t k, real_t alpha, 
		const real_t *d, int_t ldd, 
		const real_t *x, int_t ldx, 
		const real_t *y, int_t ldy, const int_t *ipiv1, 
		real_t *c, int ldc, real_t *work);

//
// offset : on entry, the starting column, on exit the number of columns factored
// a      : input matrix (m x n) m >=n
// nb     : block size (get by calling qr_blocksize())
// pvt    : pivoting vector 0-based (n)
// tau    : coeff vector (n)
// work   : workspace (2*n + (n+1)*nb)
// return : number of columns to keep such that abs(Rii) >= tol * abs(R00)
//          < 0 on error
//
int_t qr_partial(int_t *offset, int_t m, int_t n, real_t *a, int_t lda, int_t *pvt, real_t *tau, real_t tol, int_t nb, real_t *work);
int_t qr_blocksize(int_t m, int_t n);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_DECOMP_HPP_
