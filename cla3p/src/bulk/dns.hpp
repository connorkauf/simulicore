#ifndef CLA3P_DNS_HPP_
#define CLA3P_DNS_HPP_

#include "../types.hpp"
#include "../support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
namespace bulk {
/*-------------------------------------------------*/

template <typename T>
inline T* ptrmv(uint_t lda, T *a, uint_t i, uint_t j)
{
	return (a + i + j * lda);
}

template <typename T>
inline T& entry(uint_t lda, T *a, uint_t i, uint_t j)
{
	return *ptrmv(lda,a,i,j);
}

void zero(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda);
void zero(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda);
void zero(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda);
void zero(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda);

template <typename T>
T* alloc(uint_t m, uint_t n, uint_t lda, bool wipe = false)
{
	T *ret = static_cast<T*>(i_malloc(lda * n, sizeof(T)));
	if(wipe) {
		zero(prop_t::GENERAL, m, n, ret, lda);
	} // wipe
	return ret;
}

void fill(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda, real_t val);
void fill(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t val);
void fill(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t val);
void fill(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val);

void rand(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda, real_t low = 0., real_t high = 1.);
void rand(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t low = 0., real4_t high = 1.);
void rand(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda, real_t low = 0., real_t high = 1.);
void rand(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, real4_t low = 0., real4_t high = 1.);

void copy(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff = 1.);
void copy(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff = 1.);
void copy(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff = 1.);
void copy(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff = 1.);

void scale(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda, real_t coeff);
void scale(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t coeff);
void scale(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t coeff);
void scale(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff);

void transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff = 1.);
void transpose(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff = 1.);
void transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff = 1.);
void transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff = 1.);

void conjugate_transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff = 1.); // same as transpose
void conjugate_transpose(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff = 1.); // same as transpose
void conjugate_transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff = 1.);
void conjugate_transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff = 1.);

#if 0
void conjugate(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff = 1.); // scale only
void conjugate(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff = 1.); // scale only
void conjugate(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff = 1.);
void conjugate(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff = 1.);
#endif

void conjugate(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda, real_t coeff = 1.); // scale only
void conjugate(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t coeff = 1.); // scale only
void conjugate(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t coeff = 1.);
void conjugate(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff = 1.);

void sy2ge(uint_t n, real_t *a, uint_t lda);
void sy2ge(uint_t n, real4_t *a, uint_t lda);
void sy2ge(uint_t n, complex_t *a, uint_t lda);
void sy2ge(uint_t n, complex8_t *a, uint_t lda);

void he2ge(uint_t n, real_t *a, uint_t lda); // same as sy2ge
void he2ge(uint_t n, real4_t *a, uint_t lda); // same as sy2ge
void he2ge(uint_t n, complex_t *a, uint_t lda);
void he2ge(uint_t n, complex8_t *a, uint_t lda);

real_t norm_one(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda);
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda);
real_t norm_max(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda);
real_t norm_fro(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda);

real4_t norm_one(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda);
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda);
real4_t norm_max(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda);
real4_t norm_fro(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda);

real_t norm_one(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda);
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda);
real_t norm_max(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda);
real_t norm_fro(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda);

real4_t norm_one(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda);
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda);
real4_t norm_max(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda);
real4_t norm_fro(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda);

// prop: GENERAL   B = P*A*Q     if P,Q is nullptr, the identity perm is used
// prop: SYMMETRIC B = P*A*P^{T} Q is not referenced
// prop: HERMITIAN B = P*A*P^{H} Q is not referenced
void permute(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, const uint_t *P, const uint_t *Q);
void permute(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, const uint_t *P, const uint_t *Q);
void permute(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, const uint_t *P, const uint_t *Q);
void permute(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, const uint_t *P, const uint_t *Q);

/*-------------------------------------------------*/
} // namespace bulk
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_HPP_
