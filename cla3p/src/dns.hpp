#ifndef CLA3P_DNS_HPP_
#define CLA3P_DNS_HPP_

#include "types.hpp"
#include "imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/

void check(uint_t m, uint_t n, const void *a, uint_t lda, ptype_t ptype);

template <class T>
inline T* ptrmv(uint_t lda, T *a, uint_t i, uint_t j)
{
	return (a + i + j * lda);
}

template <class T>
inline T& entry(uint_t lda, T *a, uint_t i, uint_t j)
{
	return *ptrmv(lda,a,i,j);
}

void zero(uint_t m, uint_t n, real_t *a, uint_t lda);
void zero(uint_t m, uint_t n, real4_t *a, uint_t lda);
void zero(uint_t m, uint_t n, complex_t *a, uint_t lda);
void zero(uint_t m, uint_t n, complex8_t *a, uint_t lda);

template <class T>
T* alloc(uint_t m, uint_t n, uint_t lda, bool clear = false)
{
	T *ret = static_cast<T*>(i_malloc(lda * n, sizeof(T)));
	if(clear) {
		zero(m, n, ret, lda);
	} // clear
	return ret;
}

void fill(uint_t m, uint_t n, real_t *a, uint_t lda, real_t val);
void fill(uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t val);
void fill(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t val);
void fill(uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val);

void rand(uint_t m, uint_t n, real_t *a, uint_t lda, real_t low = 0., real_t high = 1.);
void rand(uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t low = 0., real4_t high = 1.);
void rand(uint_t m, uint_t n, complex_t *a, uint_t lda, real_t low = 0., real_t high = 1.);
void rand(uint_t m, uint_t n, complex8_t *a, uint_t lda, real4_t low = 0., real4_t high = 1.);

void copy(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t scale = 1.);
void copy(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t scale = 1.);
void copy(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale = 1.);
void copy(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t scale = 1.);

void transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t scale = 1.);
void transpose(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t scale = 1.);
void transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale = 1.);
void transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t scale = 1.);

void conjugate_transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale = 1.);
void conjugate_transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t scale = 1.);

void conjugate(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale = 1.);
void conjugate(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t scale = 1.);

void conjugate(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t scale = 1.);
void conjugate(uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t scale = 1.);

void sy2ge(uint_t n, real_t *a, uint_t lda);
void sy2ge(uint_t n, real4_t *a, uint_t lda);
void sy2ge(uint_t n, complex_t *a, uint_t lda);
void sy2ge(uint_t n, complex8_t *a, uint_t lda);
void he2ge(uint_t n, complex_t *a, uint_t lda);
void he2ge(uint_t n, complex8_t *a, uint_t lda);

real_t norm_one(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype);
real_t norm_inf(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype);
real_t norm_max(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype);
real_t norm_fro(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype);

real4_t norm_one(uint_t m, uint_t n, const real4_t *a, uint_t lda, ptype_t ptype);
real4_t norm_inf(uint_t m, uint_t n, const real4_t *a, uint_t lda, ptype_t ptype);
real4_t norm_max(uint_t m, uint_t n, const real4_t *a, uint_t lda, ptype_t ptype);
real4_t norm_fro(uint_t m, uint_t n, const real4_t *a, uint_t lda, ptype_t ptype);

real_t norm_one(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype);
real_t norm_inf(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype);
real_t norm_max(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype);
real_t norm_fro(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype);

real4_t norm_one(uint_t m, uint_t n, const complex8_t *a, uint_t lda, ptype_t ptype);
real4_t norm_inf(uint_t m, uint_t n, const complex8_t *a, uint_t lda, ptype_t ptype);
real4_t norm_max(uint_t m, uint_t n, const complex8_t *a, uint_t lda, ptype_t ptype);
real4_t norm_fro(uint_t m, uint_t n, const complex8_t *a, uint_t lda, ptype_t ptype);

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_HPP_
