#ifndef CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
#define CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_

#include "cla3p/src/types.hpp"
#include "cla3p/src/bulk/dns.hpp"

#include "cla3p/src/types/integer_internal.hpp"
#include "cla3p/src/types/scalar_internal.hpp"

/*-------------------------------------------------*/
using namespace cla3p;
/*-------------------------------------------------*/
uint_t  ddabs1(uint_t     x);
int_t   ddabs1(int_t      x);
real_t  ddabs1(real_t     x);
real4_t ddabs1(real4_t    x);
real_t  ddabs1(complex_t  x);
real4_t ddabs1(complex8_t x);
/*-------------------------------------------------*/
template <class T, class Tr>
Tr ddabs(T x)
{
	return ddabs1(x);
}
/*-------------------------------------------------*/
template <class T>
static T GetElem(uint_t lda, const T *a, uint_t i, uint_t j, op_t op)
{
	T ret = 0.;

	/**/ if(op == op_t::N) ret =      bulk::dns::entry(lda,a,i,j) ;
	else if(op == op_t::T) ret =      bulk::dns::entry(lda,a,j,i) ;
	else if(op == op_t::C) ret = conj(bulk::dns::entry(lda,a,j,i));

	return ret;
}
/*-------------------------------------------------*/
template <class T>
void naive_gemm(uint_t m, uint_t n, uint_t k, T alpha,
		op_t opA, const T *a, uint_t lda,
		op_t opB, const T *b, uint_t ldb,
		T beta, T *c, uint_t ldc)
{
	for(uint_t i = 0; i < m; i++) {
		for(uint_t j = 0; j < n; j++) {
			T sum = 0;
			for(uint_t l = 0; l < k; l++) {
				T aa = GetElem(lda,a,i,l,opA);
				T bb = GetElem(ldb,b,l,j,opB);
				sum += alpha * aa * bb;
			} // l
			bulk::dns::entry(ldc,c,i,j) = (beta == T(0) ? 0 : bulk::dns::entry(ldc,c,i,j) * beta);
			bulk::dns::entry(ldc,c,i,j) += sum;
		} // j
	} // i
}
/*-------------------------------------------------*/
template <class T, class Tr>
Tr naive_norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda)
{
	Tr ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(uplo, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(uplo,n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(uplo,n,b,m);
	for(uint_t j = 0; j < n; j++) {
		Tr jsum = 0.;
		for(uint_t i = 0; i < m; i++) {
			Tr bij = ddabs<T,Tr>(bulk::dns::entry(m,b,i,j));
			jsum += bij;
		} // i
		ret = std::max(ret,jsum);
	} // j
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T, class Tr>
Tr naive_norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda)
{
	Tr ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(uplo, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(uplo, n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(uplo, n,b,m);
	for(uint_t i = 0; i < m; i++) {
		Tr isum = 0.;
		for(uint_t j = 0; j < n; j++) {
			Tr bij = ddabs<T,Tr>(bulk::dns::entry(m,b,i,j));
			isum += bij;
		} // j
		ret = std::max(ret,isum);
	} // i
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T, class Tr>
Tr naive_norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda)
{
	Tr ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(uplo, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(uplo, n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(uplo, n,b,m);
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			Tr bij = ddabs<T,Tr>(bulk::dns::entry(m,b,i,j));
			ret = (ret > bij ? ret : bij);
		} // j
	} // i
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T, class Tr>
Tr naive_norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda)
{
	Tr ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(uplo, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(uplo,n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(uplo,n,b,m);
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			Tr bij = ddabs<T,Tr>(bulk::dns::entry(m,b,i,j));
			ret += bij * bij;
		} // i
	} // j
	i_free(b);
	return std::sqrt(ret);
}
/*-------------------------------------------------*/
template <class T>
void naive_permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	T *af = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(uplo, m, n, a, lda, af, m);
	if(ptype == prop_t::SYMMETRIC){ bulk::dns::sy2ge(uplo,n,af,m); Q = P; }
	if(ptype == prop_t::HERMITIAN){ bulk::dns::he2ge(uplo,n,af,m); Q = P; }
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			uint_t Pi = P ? P[i] : i;
			uint_t Qj = Q ? Q[j] : j;
			bulk::dns::entry(ldb,b,Pi,Qj) = bulk::dns::entry(m,af,i,j);
		} // i
	} // j
	i_free(af);
}
/*-------------------------------------------------*/
template <class T>
void naive_update(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			bulk::dns::entry(ldb,b,i,j) += coeff * bulk::dns::entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <class T>
void naive_matvec(op_t op, uint_t m, uint_t n, const T* a, uint_t lda, T alpha, const T *x, T beta, T *y)
{
	uint_t dimx = (op == op_t::N ? n : m);
	uint_t dimy = (op == op_t::N ? m : n);
	naive_gemm(dimy, 1, dimx, alpha, op, a, lda, op_t::N, x, dimx, beta, y, dimy);
}
/*-------------------------------------------------*/

#endif // CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
