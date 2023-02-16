#ifndef CLA3P_BULK_DNS_HPP_
#define CLA3P_BULK_DNS_HPP_

#include "../types.hpp"
#include "../support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
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

#define fill_macro(typeout, typein) \
typeout fill(prop_t ptype, uint_t m, uint_t n, typein *a, uint_t lda, typein val)
fill_macro(void, int_t);
fill_macro(void, uint_t);
fill_macro(void, real_t);
fill_macro(void, real4_t);
fill_macro(void, complex_t);
fill_macro(void, complex8_t);
#undef fill_macro

template <typename T>
void zero(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda)
{
	fill(ptype, m, n, a, lda, 0);
}

template <typename T>
T* alloc(uint_t m, uint_t n, uint_t lda, bool wipe = false)
{
	T *ret = static_cast<T*>(i_malloc(lda * n, sizeof(T)));
	if(wipe) {
		zero(prop_t::GENERAL, m, n, ret, lda);
	} // wipe
	return ret;
}

#define rand_macro(typeout, typein, rtypein, lowval, highval) \
typeout rand(prop_t ptype, uint_t m, uint_t n, typein *a, uint_t lda, rtypein low = lowval, rtypein high = highval)
rand_macro(void, int_t     , int_t  , 0, 100);
rand_macro(void, uint_t    , uint_t , 0, 100);
rand_macro(void, real_t    , real_t , 0,   1);
rand_macro(void, real4_t   , real4_t, 0,   1);
rand_macro(void, complex_t , real_t , 0,   1);
rand_macro(void, complex8_t, real4_t, 0,   1);
#undef rand_macro

#define copy_macro(typeout, typein) \
typeout copy(prop_t ptype, uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
copy_macro(void, int_t);
copy_macro(void, uint_t);
copy_macro(void, real_t);
copy_macro(void, real4_t);
copy_macro(void, complex_t);
copy_macro(void, complex8_t);
#undef copy_macro

#define scale_macro(typeout, typein) \
typeout scale(prop_t ptype, uint_t m, uint_t n, typein *a, uint_t lda, typein coeff)
scale_macro(void, int_t);
scale_macro(void, uint_t);
scale_macro(void, real_t);
scale_macro(void, real4_t);
scale_macro(void, complex_t);
scale_macro(void, complex8_t);
#undef scale_macro

#define transpose_macro(typeout, typein) \
typeout transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
transpose_macro(void, int_t);
transpose_macro(void, uint_t);
transpose_macro(void, real_t);
transpose_macro(void, real4_t);
transpose_macro(void, complex_t);
transpose_macro(void, complex8_t);
#undef transpose_macro

#define conjugate_transpose_macro(typeout, typein) \
typeout conjugate_transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
conjugate_transpose_macro(void, int_t); // same as transpose
conjugate_transpose_macro(void, uint_t); // same as transpose
conjugate_transpose_macro(void, real_t); // same as transpose
conjugate_transpose_macro(void, real4_t); // same as transpose
conjugate_transpose_macro(void, complex_t);
conjugate_transpose_macro(void, complex8_t);
#undef transpose_macro

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

// dummy functions, throw exception
int_t norm_one(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda);
int_t norm_inf(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda);
int_t norm_max(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda);
int_t norm_fro(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda);

// dummy functions, throw exception
uint_t norm_one(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda);
uint_t norm_inf(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda);
uint_t norm_max(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda);
uint_t norm_fro(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda);

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

// prop: GENERAL             B = P*A*Q     if P,Q is nullptr, the identity perm is used
// prop: SYMMETRIC/HERMITIAN B = P*A*P^{T} Q is not referenced
#define permute_macro(typeout, typein) \
typeout permute(prop_t ptype, uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, const uint_t *P, const uint_t *Q)
permute_macro(void, int_t);
permute_macro(void, uint_t);
permute_macro(void, real_t);
permute_macro(void, real4_t);
permute_macro(void, complex_t);
permute_macro(void, complex8_t);
#undef permute_macro

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_HPP_
