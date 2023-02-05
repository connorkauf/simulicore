#ifndef CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
#define CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_

#include "cla3p/src/types.hpp"
#include "cla3p/src/bulk/dns.hpp"

/*-------------------------------------------------*/
using namespace cla3p;
/*-------------------------------------------------*/
void naive_gemm(uint_t m, uint_t n, uint_t k, real_t alpha,
		TransOp opA, const real_t *a, uint_t lda,
		TransOp opB, const real_t *b, uint_t ldb,
		real_t beta, real_t *c, uint_t ldc);
/*-------------------------------------------------*/
template <class T>
real_t naive_norm_one(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda)
{
	real_t ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(ptype, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(n,b,m);
	for(uint_t j = 0; j < n; j++) {
		real_t jsum = 0.;
		for(uint_t i = 0; i < m; i++) {
			real_t bij = std::abs(bulk::dns::entry(m,b,i,j));
			jsum += bij;
		} // i
		ret = std::max(ret,jsum);
	} // j
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T>
real_t naive_norm_inf(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda)
{
	real_t ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(ptype, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(n,b,m);
	for(uint_t i = 0; i < m; i++) {
		real_t isum = 0.;
		for(uint_t j = 0; j < n; j++) {
			real_t bij = std::abs(bulk::dns::entry(m,b,i,j));
			isum += bij;
		} // j
		ret = std::max(ret,isum);
	} // i
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T>
real_t naive_norm_max(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda)
{
	real_t ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(ptype, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(n,b,m);
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			real_t bij = std::abs(bulk::dns::entry(m,b,i,j));
			ret = std::max(ret,bij);
		} // j
	} // i
	i_free(b);
	return ret;
}
/*-------------------------------------------------*/
template <class T>
real_t naive_norm_fro(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda)
{
	real_t ret = 0.;
	T *b = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(ptype, m, n, a, lda, b, m);
	if(ptype == prop_t::SYMMETRIC) bulk::dns::sy2ge(n,b,m);
	if(ptype == prop_t::HERMITIAN) bulk::dns::he2ge(n,b,m);
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			real_t bij = std::abs(bulk::dns::entry(m,b,i,j));
			ret += bij * bij;
		} // i
	} // j
	i_free(b);
	return std::sqrt(ret);
}
/*-------------------------------------------------*/
template <class T>
void naive_permute(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	T *af = bulk::dns::alloc<T>(m,n,m);
	bulk::dns::copy(ptype, m, n, a, lda, af, m);
	if(ptype == prop_t::SYMMETRIC){ bulk::dns::sy2ge(n,af,m); Q = P; }
	if(ptype == prop_t::HERMITIAN){ bulk::dns::he2ge(n,af,m); Q = P; }
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

#endif // CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
