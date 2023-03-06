// this file inc
#include "dns_math.hpp"

// system

// 3rd

// cla3p
#include "../checks/all_checks.hpp"
#include "../support/error.hpp"
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
static void naive_matvec_tmpl(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	T bzero = 0;

	uint_t dimy = (opA == op_t::N ? m : n);

	// 
	// scale y
	//
	if(beta == bzero) {
		zero(uplo_t::F, dimy, 1, y, dimy);
	} else {
		scale(uplo_t::F, dimy, 1, y, dimy, beta);
	} // beta

	// 
	// do the math
	//
	if(prop.isGeneral()) {
		for(uint_t j = 0; j < n; j++) {
			for(uint_t i = 0; i < m; i++) {
				T aij = entry(lda,a,i,j);
				if(opA == op_t::N) y[i] += alpha *      aij  * x[j];
				if(opA == op_t::T) y[j] += alpha *      aij  * x[i];
				if(opA == op_t::C) y[j] += alpha * conj(aij) * x[i];
			} // i
		} // j
	} else if(prop.isSymmetric()) {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			for(uint_t i = ir.ibgn; i < ir.iend; i++) {
				T aij = entry(lda,a,i,j);
				y[i] += alpha * aij * x[j];
				if(i != j) y[j] += alpha * aij * x[i];
			} // i
		} // j
	} else if(prop.isHermitian()) {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			for(uint_t i = ir.ibgn; i < ir.iend; i++) {
				T aij = entry(lda,a,i,j);
				if(i != j) y[j] += alpha * conj(aij) * x[i];
			} // i
		} // j
	} else {
		throw Exception("Invalid property: " + prop.name());
	}
}
/*-------------------------------------------------*/
template <typename T>
static void matvec_tmpl(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, T alpha, const T *a, uint_t lda, const T *x, T beta, T *y)
{
	Property prop(ptype, uplo);
	Operation op(opA);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	/**/ if(prop.isGeneral()  ) return blas::gemv(op.ctype(), m, n, alpha, a, lda, x, 1, beta, y, 1);
	else if(prop.isSymmetric()) return blas::symv(prop.cuplo(), n, alpha, a, lda, x, 1, beta, y, 1);
	else if(prop.isHermitian()) return blas::hemv(prop.cuplo(), n, alpha, a, lda, x, 1, beta, y, 1);
	
	throw Exception("Invalid property: " + prop.name());
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, int_t alpha, const int_t *a, uint_t lda, const int_t *x, int_t beta, int_t *y)
{
	naive_matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t alpha, const uint_t *a, uint_t lda, const uint_t *x, uint_t beta, uint_t *y)
{
	naive_matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, const real_t *x, real_t beta, real_t *y)
{
	matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, const real4_t *x, real4_t beta, real4_t *y)
{
	matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, const complex_t *x, complex_t beta, complex_t *y)
{
	matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *x, complex8_t beta, complex8_t *y)
{
	matvec_tmpl(ptype, uplo, opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void naive_gematmat_tmpl(uint_t m, uint_t n, uint_t k, T alpha, op_t opA, const T *a, uint_t lda, op_t opB, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	T bzero = 0;

	// 
	// scale y
	//
	if(beta == bzero) {
		zero(uplo_t::F, m, n, c, ldc);
	} else {
		scale(uplo_t::F, m, n, c, ldc, beta);
	} // beta

	// 
	// do the math
	//
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
static void gematmat_tmpl(uint_t m, uint_t n, uint_t k, T alpha, op_t opA, const T *a, uint_t lda, op_t opB, const T *b, uint_t ldb, T beta, T *c, uint_t ldc)
{
	blas::gemm(static_cast<char>(opA), static_cast<char>(opB), m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, int_t alpha, op_t opA, const int_t *a, uint_t lda, op_t opB, const int_t *b, uint_t ldb, int_t beta, int_t *c, uint_t ldc)
{
	naive_gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, uint_t alpha, op_t opA, const uint_t *a, uint_t lda, op_t opB, const uint_t *b, uint_t ldb, uint_t beta, uint_t *c, uint_t ldc)
{
	naive_gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, real_t alpha, op_t opA, const real_t *a, uint_t lda, op_t opB, const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, real4_t alpha, op_t opA, const real4_t *a, uint_t lda, op_t opB, const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, complex_t alpha, op_t opA, const complex_t *a, uint_t lda, op_t opB, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gematmat(uint_t m, uint_t n, uint_t k, complex8_t alpha, op_t opA, const complex8_t *a, uint_t lda, op_t opB, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gematmat_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
