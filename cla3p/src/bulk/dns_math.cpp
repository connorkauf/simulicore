// this file inc
#include "dns_math.hpp"

// system

// 3rd

// cla3p
#include "../checks/all_checks.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../proxies/blas_proxy.hpp"
#include "../proxies/mkl_proxy.hpp"
#include "dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
template <typename T>
static void naive_update_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, T *c, uint_t ldc)
{
	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(ldc,c,i,j) += alpha * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void update_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, T *c, uint_t ldc)
{
	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		blas::axpy(ir.ilen, alpha, ptrmv(lda,a,ir.ibgn,j), 1, ptrmv(ldc,c,ir.ibgn,j), 1);
	} // j
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, int_t *c, uint_t ldc) 
{
	naive_update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, uint_t *c, uint_t ldc)
{
	naive_update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, real_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, real4_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, complex_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, complex8_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_add_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, T beta, const T *b, uint_t ldb, T *c, uint_t ldc)
{
	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(ldc,c,i,j) = alpha * entry(lda,a,i,j) + beta * entry(ldb,b,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void add_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, T beta, const T *b, uint_t ldb, T *c, uint_t ldc)
{
	if(uplo == uplo_t::F) {
		mkl::omatadd('C', 'N', 'N', m, n, alpha, a, lda, beta, b, ldb, c, ldc);
	} else {
		zero(uplo, m, n, c, ldc);
		update(uplo, m, n, alpha, a, lda, c, ldc);
		update(uplo, m, n, beta , b, ldb, c, ldc);
	} // uplo
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, int_t beta, const int_t *b, uint_t ldb, int_t *c, uint_t ldc) 
{
	naive_add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, uint_t beta, const uint_t *b, uint_t ldb, uint_t *c, uint_t ldc) 
{
	naive_add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, real_t beta, const real_t *b, uint_t ldb, real_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, real4_t beta, const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, complex_t beta, const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, complex8_t beta, const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_gem_x_vec_tmpl(op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	uint_t dimy = (opA == op_t::N ? m : n);
	scale(uplo_t::F, dimy, 1, y, dimy, beta);

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			T aij = entry(lda,a,i,j);
			if(opA == op_t::N) y[i] += alpha *      aij  * x[j];
			if(opA == op_t::T) y[j] += alpha *      aij  * x[i];
			if(opA == op_t::C) y[j] += alpha * conj(aij) * x[i];
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void gem_x_vec_tmpl(op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	blas::gemv(static_cast<char>(opA), m, n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *x, int_t beta, int_t *y)
{
	naive_gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *x, uint_t beta, uint_t *y)
{
	naive_gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *x, real_t beta, real_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *x, real4_t beta, real4_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *x, complex_t beta, complex_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *x, complex8_t beta, complex8_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_sym_x_vec_tmpl(uplo_t uplo, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	scale(uplo_t::F, n, 1, y, n, beta);

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			T aij = entry(lda,a,i,j);
			y[i] += alpha * aij * x[j];
			if(i != j) y[j] += alpha * aij * x[i];
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void sym_x_vec_tmpl(uplo_t uplo, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	blas::symv(static_cast<char>(uplo), n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *x, int_t beta, int_t *y)
{
	naive_sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *x, uint_t beta, uint_t *y)
{
	naive_sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *x, real_t beta, real_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *x, real4_t beta, real4_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *x, complex_t beta, complex_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *x, complex8_t beta, complex8_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#if 0
template <typename T>
static void naive_hem_x_vec_tmpl(uplo_t uplo, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	scale(uplo_t::F, n, 1, y, n, beta);

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			T aij = entry(lda,a,i,j);
			y[i] += alpha * aij * x[j];
			if(i != j) y[j] += alpha * conj(aij) * x[i];
		} // i
	} // j
}
#endif
/*-------------------------------------------------*/
template <typename T>
static void hem_x_vec_tmpl(uplo_t uplo, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	blas::hemv(static_cast<char>(uplo), n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void hem_x_vec(uplo_t, uint_t, int_t  , const int_t*  , uint_t, const int_t*  , int_t  , int_t*  ) { throw Exception(msg::op_not_allowed()); }
void hem_x_vec(uplo_t, uint_t, uint_t , const uint_t* , uint_t, const uint_t* , uint_t , uint_t* ) { throw Exception(msg::op_not_allowed()); }
void hem_x_vec(uplo_t, uint_t, real_t , const real_t* , uint_t, const real_t* , real_t , real_t* ) { throw Exception(msg::op_not_allowed()); }
void hem_x_vec(uplo_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, real4_t, real4_t*) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void hem_x_vec(uplo_t uplo, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *x, complex_t beta, complex_t *y)
{
	hem_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void hem_x_vec(uplo_t uplo, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *x, complex8_t beta, complex8_t *y)
{
	hem_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_trm_x_vec_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T *y)
{
	uint_t dimy = (opA == op_t::N ? m : n);
	zero(uplo_t::F, dimy, 1, y, dimy);

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			T aij = entry(lda,a,i,j);
			if(opA == op_t::N) y[i] += alpha *      aij  * x[j];
			if(opA == op_t::T) y[j] += alpha *      aij  * x[i];
			if(opA == op_t::C) y[j] += alpha * conj(aij) * x[i];
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void trm_x_vec_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T *y)
{
	uint_t mindim = std::min(m,n);

	if(opA == op_t::N) {

		copy(uplo_t::F, mindim, 1, x, mindim, y, mindim, alpha);
		if(m > n) zero(uplo_t::F, m-n, 1, y + n, m-n);
		blas::trmv(static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, a, lda, y, 1);

		if(m > n && uplo == uplo_t::L) gem_x_vec(opA, m-n, n, alpha, ptrmv(lda,a,n,0), lda, x, 1, y + n);
		if(m < n && uplo == uplo_t::U) gem_x_vec(opA, m, n-m, alpha, ptrmv(lda,a,0,m), lda, x + m, 1, y);

	} else {

		copy(uplo_t::F, mindim, 1, x, mindim, y, mindim, alpha);
		if(n > m) zero(uplo_t::F, n-m, 1, y + m, n-m);
		blas::trmv(static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, a, lda, y, 1);

		if(m > n && uplo == uplo_t::L) gem_x_vec(opA, m-n, n, alpha, ptrmv(lda,a,n,0), lda, x + n, 1, y);
		if(m < n && uplo == uplo_t::U) gem_x_vec(opA, m, n-m, alpha, ptrmv(lda,a,0,m), lda, x, 1, y + m);

	} // opA
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *x, int_t *y)
{
	naive_trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *x, uint_t *y)
{
	naive_trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *x, real_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *x, real4_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *x, complex_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *x, complex8_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_gem_x_gem_tmpl(uint_t m, uint_t n, uint_t k, T alpha, op_t opA, const T *a, uint_t lda, op_t opB, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	scale(uplo_t::F, m, n, c, ldc, beta);

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			for(uint_t l = 0; l < k; l++) {
				T a_elem = 0;
				T b_elem = 0;
				/**/ if(opA == op_t::N) a_elem =      entry(lda,a,i,l) ;
				else if(opA == op_t::T) a_elem =      entry(lda,a,l,i) ;
				else if(opA == op_t::C) a_elem = conj(entry(lda,a,l,i));
				/**/ if(opB == op_t::N) b_elem =      entry(ldb,b,l,j) ;
				else if(opB == op_t::T) b_elem =      entry(ldb,b,j,l) ;
				else if(opB == op_t::C) b_elem = conj(entry(ldb,b,j,l));
				entry(ldc,c,i,j) += alpha * a_elem * b_elem;
			} // l
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void gem_x_gem_tmpl(uint_t m, uint_t n, uint_t k, T alpha, op_t opA, const T *a, uint_t lda, op_t opB, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::gemm(static_cast<char>(opA), static_cast<char>(opB), m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, int_t alpha, op_t opA, const int_t *a, uint_t lda, op_t opB, const int_t *b, uint_t ldb, int_t beta, int_t *c, uint_t ldc)
{
	naive_gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, uint_t alpha, op_t opA, const uint_t *a, uint_t lda, op_t opB, const uint_t *b, uint_t ldb, uint_t beta, uint_t *c, uint_t ldc)
{
	naive_gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, real_t alpha, op_t opA, const real_t *a, uint_t lda, op_t opB, const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, real4_t alpha, op_t opA, const real4_t *a, uint_t lda, op_t opB, const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, complex_t alpha, op_t opA, const complex_t *a, uint_t lda, op_t opB, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, complex8_t alpha, op_t opA, const complex8_t *a, uint_t lda, op_t opB, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_sym_x_gem_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	for(uint_t j = 0; j < n; j++) {
		sym_x_vec(uplo, m, alpha, a, lda, ptrmv(ldb,b,0,j), beta, ptrmv(ldc,c,0,j));
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void sym_x_gem_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::symm('L', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *b, uint_t ldb, int_t beta, int_t *c, uint_t ldc)
{
	naive_sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *b, uint_t ldb, uint_t beta, uint_t *c, uint_t ldc)
{
	naive_sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_gem_x_sym_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	scale(uplo_t::F, m, n, c, ldc, beta);

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			for(uint_t k = 0; k < m; k++) {
				T aij = entry(lda,a,i,j);
				T bki = entry(ldb,b,k,i);
				T bkj = entry(ldb,b,k,j);
				entry(ldc,c,k,i) += alpha * aij * bkj;
				if(i != j) entry(ldc,c,k,j) += alpha * aij * bki;
			} // k
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void gem_x_sym_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::symm('R', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *b, uint_t ldb, int_t beta, int_t *c, uint_t ldc)
{
	naive_gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *b, uint_t ldb, uint_t beta, uint_t *c, uint_t ldc)
{
	naive_gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void hem_x_gem_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::hemm('L', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void hem_x_gem(uplo_t, uint_t, uint_t, int_t  , const int_t*  , uint_t, const int_t*  , uint_t, int_t  , int_t*  , uint_t) { throw Exception(msg::op_not_allowed()); }
void hem_x_gem(uplo_t, uint_t, uint_t, uint_t , const uint_t* , uint_t, const uint_t* , uint_t, uint_t , uint_t* , uint_t) { throw Exception(msg::op_not_allowed()); }
void hem_x_gem(uplo_t, uint_t, uint_t, real_t , const real_t* , uint_t, const real_t* , uint_t, real_t , real_t* , uint_t) { throw Exception(msg::op_not_allowed()); }
void hem_x_gem(uplo_t, uint_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, uint_t, real4_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	hem_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	hem_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void gem_x_hem_tmpl(uplo_t uplo, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::hemm('R', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_hem(uplo_t, uint_t, uint_t, int_t  , const int_t*  , uint_t, const int_t*  , uint_t, int_t  , int_t*  , uint_t) { throw Exception(msg::op_not_allowed()); }
void gem_x_hem(uplo_t, uint_t, uint_t, uint_t , const uint_t* , uint_t, const uint_t* , uint_t, uint_t , uint_t* , uint_t) { throw Exception(msg::op_not_allowed()); }
void gem_x_hem(uplo_t, uint_t, uint_t, real_t , const real_t* , uint_t, const real_t* , uint_t, real_t , real_t* , uint_t) { throw Exception(msg::op_not_allowed()); }
void gem_x_hem(uplo_t, uint_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, uint_t, real4_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void gem_x_hem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_hem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_hem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_hem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
void naive_trm_x_gem_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T *c, uint_t ldc)
{
	uint_t nrA = (opA == op_t::N ? m : k);
	uint_t ncA = (opA == op_t::N ? k : m);

	for(uint_t l = 0; l < n; l++) {
		naive_trm_x_vec_tmpl(uplo, opA, nrA, ncA, alpha, a, lda, ptrmv(ldb,b,0,l), ptrmv(ldc,c,0,l));
	} // l
}
/*-------------------------------------------------*/
template <typename T>
void trm_x_gem_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T *c, uint_t ldc)
{
	uint_t mindim = std::min(m,k);

		copy(uplo_t::F, mindim, n, b, ldb, c, ldc, alpha);
		if(m > k) zero(uplo_t::F, m-k, n, ptrmv(ldc,c,k,0), ldc);
		blas::trmm('L', static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, n, 1, a, lda, c, ldc);

	if(opA == op_t::N) {
		if(m > k && uplo == uplo_t::L) gem_x_gem(m-k, n, k, alpha, opA, ptrmv(lda,a,k,0), lda, op_t::N,           b     , ldb, 1, ptrmv(ldc,c,k,0), ldc);
		if(m < k && uplo == uplo_t::U) gem_x_gem(m, n, k-m, alpha, opA, ptrmv(lda,a,0,m), lda, op_t::N, ptrmv(ldb,b,m,0), ldb, 1,           c     , ldc);
	} else {
		if(m > k && uplo == uplo_t::U) gem_x_gem(m-k, n, k, alpha, opA, ptrmv(lda,a,0,k), lda, op_t::N,           b     , ldb, 1, ptrmv(ldc,c,k,0), ldc);
		if(m < k && uplo == uplo_t::L) gem_x_gem(m, n, k-m, alpha, opA, ptrmv(lda,a,m,0), lda, op_t::N, ptrmv(ldb,b,m,0), ldb, 1,           c     , ldc);
	} // opA
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, int_t alpha, const int_t *a, uint_t lda, const int_t *b, uint_t ldb, int_t *c, uint_t ldc)
{
	naive_trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *b, uint_t ldb, uint_t *c, uint_t ldc)
{
	naive_trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real_t alpha, const real_t *a, uint_t lda, const real_t *b, uint_t ldb, real_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
//void naive_gem_x_trm_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T *c, uint_t ldc)
void naive_gem_x_trm_tmpl(uplo_t, op_t, uint_t, uint_t, uint_t, T, const T*, uint_t, const T*, uint_t, T*, uint_t)
{
}
/*-------------------------------------------------*/
template <typename T>
void gem_x_trm_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T alpha, const T *a, uint_t lda, const T *b, uint_t ldb, T *c, uint_t ldc)
{
	uint_t mindim = std::min(n,k);

	copy(uplo_t::F, m, mindim, b, ldb, c, ldc, alpha);
	if(n > k) zero(uplo_t::F, m, n-k, ptrmv(ldc,c,0,k), ldc);
	blas::trmm('R', static_cast<char>(uplo), static_cast<char>(opA), 'N', m, mindim, 1, a, lda, c, ldc);

	if(opA == op_t::N) {
		if(n > k && uplo == uplo_t::U) gem_x_gem(m, n-k, k, alpha, op_t::N,           b     , ldb, opA, ptrmv(lda,a,0,k), lda, 1, ptrmv(ldc,c,0,k), ldc);
		if(n < k && uplo == uplo_t::L) gem_x_gem(m, n, k-n, alpha, op_t::N, ptrmv(ldb,b,0,n), ldb, opA, ptrmv(lda,a,n,0), lda, 1,           c     , ldc);
	} else {
		if(n > k && uplo == uplo_t::L) gem_x_gem(m, n-k, k, alpha, op_t::N,           b     , ldb, opA, ptrmv(lda,a,k,0), lda, 1, ptrmv(ldc,c,0,k), ldc);
		if(n < k && uplo == uplo_t::U) gem_x_gem(m, n, k-n, alpha, op_t::N, ptrmv(ldb,b,0,n), ldb, opA, ptrmv(lda,a,0,n), lda, 1,           c     , ldc);
	} // opA
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, int_t alpha, const int_t *a, uint_t lda, const int_t *b, uint_t ldb, int_t *c, uint_t ldc)
{
	naive_gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *b, uint_t ldb, uint_t *c, uint_t ldc)
{
	naive_gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real_t alpha, const real_t *a, uint_t lda, const real_t *b, uint_t ldb, real_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/