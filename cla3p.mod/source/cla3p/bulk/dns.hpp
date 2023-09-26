#ifndef CLA3P_BULK_DNS_HPP_
#define CLA3P_BULK_DNS_HPP_

#include "cla3p/types.hpp"
#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

//
// Set pointer (column-major)
//
template <typename T>
inline T* ptrmv(uint_t lda, T *a, uint_t i, uint_t j)
{
	return (a + i + j * lda);
}

//
// Get value (column-major)
//
template <typename T>
inline T& entry(uint_t lda, T *a, uint_t i, uint_t j)
{
	return *ptrmv(lda,a,i,j);
}

//
// Set all entries to val
//
#define fill_macro(typeout, typein) \
typeout fill(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein val)
fill_macro(void, int_t);
fill_macro(void, uint_t);
fill_macro(void, real_t);
fill_macro(void, real4_t);
fill_macro(void, complex_t);
fill_macro(void, complex8_t);
#undef fill_macro

//
// Set all entries to val (separate diagonal)
//
#define fill_macro(typeout, typein) \
typeout fill(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein val, typein dval)
fill_macro(void, int_t);
fill_macro(void, uint_t);
fill_macro(void, real_t);
fill_macro(void, real4_t);
fill_macro(void, complex_t);
fill_macro(void, complex8_t);
#undef fill_macro

//
// Set all entries to zero
//
template <typename T>
void zero(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda)
{
	fill(uplo, m, n, a, lda, 0);
}

//
// Allocate memory
//
template <typename T>
T* alloc(uint_t m, uint_t n, uint_t lda, bool wipe = false)
{
	T *ret = static_cast<T*>(i_malloc(lda * n, sizeof(T)));
	if(wipe) {
		zero(uplo_t::F, m, n, ret, lda);
	} // wipe
	return ret;
}

//
// Set random values
//
#define rand_macro(typeout, typein, rtypein, lval, hval) \
typeout rand(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, rtypein low = lval, rtypein high = hval)
rand_macro(void, int_t     , int_t  , 0, 100);
rand_macro(void, uint_t    , uint_t , 0, 100);
rand_macro(void, real_t    , real_t , 0,   1);
rand_macro(void, real4_t   , real4_t, 0,   1);
rand_macro(void, complex_t , real_t , 0,   1);
rand_macro(void, complex8_t, real4_t, 0,   1);
#undef rand_macro

//
// Copy
//
#define copy_macro(typeout, typein) \
typeout copy(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
copy_macro(void, int_t);
copy_macro(void, uint_t);
copy_macro(void, real_t);
copy_macro(void, real4_t);
copy_macro(void, complex_t);
copy_macro(void, complex8_t);
#undef copy_macro

//
// Get real part from complex
//
#define get_real_macro(typeout, typein, rtypein) \
typeout get_real(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, rtypein *b, uint_t ldb)
get_real_macro(void, int_t     , int_t  ); // exception
get_real_macro(void, uint_t    , uint_t ); // exception
get_real_macro(void, real_t    , real_t ); // exception
get_real_macro(void, real4_t   , real4_t); // exception
get_real_macro(void, complex_t , real_t );
get_real_macro(void, complex8_t, real4_t);
#undef get_real_macro

//
// Get imag part from complex
//
#define get_imag_macro(typeout, typein, rtypein) \
typeout get_imag(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, rtypein *b, uint_t ldb)
get_imag_macro(void, int_t     , int_t  ); // exception
get_imag_macro(void, uint_t    , uint_t ); // exception
get_imag_macro(void, real_t    , real_t ); // exception
get_imag_macro(void, real4_t   , real4_t); // exception
get_imag_macro(void, complex_t , real_t );
get_imag_macro(void, complex8_t, real4_t);
#undef get_imag_macro

//
// Set real part to complex
//
#define set_real_macro(typeout, typein, rtypein) \
typeout set_real(uplo_t uplo, uint_t m, uint_t n, const rtypein *a, uint_t lda, typein *b, uint_t ldb)
set_real_macro(void, int_t     , int_t  ); // exception
set_real_macro(void, uint_t    , uint_t ); // exception
set_real_macro(void, real_t    , real_t ); // exception
set_real_macro(void, real4_t   , real4_t); // exception
set_real_macro(void, complex_t , real_t );
set_real_macro(void, complex8_t, real4_t);
#undef set_real_macro

//
// Set imag part to complex
//
#define set_imag_macro(typeout, typein, rtypein) \
typeout set_imag(uplo_t uplo, uint_t m, uint_t n, const rtypein *a, uint_t lda, typein *b, uint_t ldb)
set_imag_macro(void, int_t     , int_t  ); // exception
set_imag_macro(void, uint_t    , uint_t ); // exception
set_imag_macro(void, real_t    , real_t ); // exception
set_imag_macro(void, real4_t   , real4_t); // exception
set_imag_macro(void, complex_t , real_t );
set_imag_macro(void, complex8_t, real4_t);
#undef set_imag_macro

//
// Scale
//
#define scale_macro(typeout, typein) \
typeout scale(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein coeff)
scale_macro(void, int_t);
scale_macro(void, uint_t);
scale_macro(void, real_t);
scale_macro(void, real4_t);
scale_macro(void, complex_t);
scale_macro(void, complex8_t);
#undef scale_macro

//
// Transpositions
//
#define transpose_macro(typeout, typein) \
typeout transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
transpose_macro(void, int_t);
transpose_macro(void, uint_t);
transpose_macro(void, real_t);
transpose_macro(void, real4_t);
transpose_macro(void, complex_t);
transpose_macro(void, complex8_t);
#undef transpose_macro

//
// Conjugate transpositions
//
#define conjugate_transpose_macro(typeout, typein) \
typeout conjugate_transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
conjugate_transpose_macro(void, int_t); // exception
conjugate_transpose_macro(void, uint_t); // exception
conjugate_transpose_macro(void, real_t); // exception
conjugate_transpose_macro(void, real4_t); // exception
conjugate_transpose_macro(void, complex_t);
conjugate_transpose_macro(void, complex8_t);
#undef conjugate_transpose_macro

//
// Conjugations
//
#define conjugate_macro(typeout, typein) \
typeout conjugate(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein coeff = 1)
conjugate_macro(void, int_t); // exception
conjugate_macro(void, uint_t); // exception
conjugate_macro(void, real_t); // exception
conjugate_macro(void, real4_t); // exception
conjugate_macro(void, complex_t);
conjugate_macro(void, complex8_t);
#undef conjugate_macro

//
// Symmetric to general
//
#define sy2ge_macro(typeout, typein) \
typeout sy2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
sy2ge_macro(void, int_t);
sy2ge_macro(void, uint_t);
sy2ge_macro(void, real_t);
sy2ge_macro(void, real4_t);
sy2ge_macro(void, complex_t);
sy2ge_macro(void, complex8_t);
#undef sy2ge_macro

//
// Hermitian to general
//
#define he2ge_macro(typeout, typein) \
typeout he2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
he2ge_macro(void, int_t); // exception
he2ge_macro(void, uint_t); // exception
he2ge_macro(void, real_t); // exception
he2ge_macro(void, real4_t); // exception
he2ge_macro(void, complex_t);
he2ge_macro(void, complex8_t);
#undef he2ge_macro

//
// Skew to general
//
#define sk2ge_macro(typeout, typein) \
typeout sk2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
sk2ge_macro(void, int_t);
sk2ge_macro(void, uint_t); // exception
sk2ge_macro(void, real_t);
sk2ge_macro(void, real4_t);
sk2ge_macro(void, complex_t);
sk2ge_macro(void, complex8_t);
#undef sk2ge_macro

//
// Triangular to general
//
#define tr2ge_macro(typeout, typein) \
typeout tr2ge(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda)
tr2ge_macro(void, int_t);
tr2ge_macro(void, uint_t);
tr2ge_macro(void, real_t);
tr2ge_macro(void, real4_t);
tr2ge_macro(void, complex_t);
tr2ge_macro(void, complex8_t);
#undef tr2ge_macro

//
// Norm 1
//
#define norm_one_macro(typeout, typein) \
typeout norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda)
norm_one_macro(int_t  , int_t); // exception
norm_one_macro(uint_t , uint_t); // exception
norm_one_macro(real_t , real_t);
norm_one_macro(real4_t, real4_t);
norm_one_macro(real_t , complex_t);
norm_one_macro(real4_t, complex8_t);
#undef norm_one_macro

//
// Norm Inf
//
#define norm_inf_macro(typeout, typein) \
typeout norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda)
norm_inf_macro(int_t  , int_t); // exception
norm_inf_macro(uint_t , uint_t); // exception
norm_inf_macro(real_t , real_t);
norm_inf_macro(real4_t, real4_t);
norm_inf_macro(real_t , complex_t);
norm_inf_macro(real4_t, complex8_t);
#undef norm_inf_macro

//
// Norm Max
//
#define norm_max_macro(typeout, typein) \
typeout norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda)
norm_max_macro(int_t  , int_t); // exception
norm_max_macro(uint_t , uint_t); // exception
norm_max_macro(real_t , real_t);
norm_max_macro(real4_t, real4_t);
norm_max_macro(real_t , complex_t);
norm_max_macro(real4_t, complex8_t);
#undef norm_max_macro

//
// Norm Frobenius
//
#define norm_fro_macro(typeout, typein) \
typeout norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda)
norm_fro_macro(int_t  , int_t); // exception
norm_fro_macro(uint_t , uint_t); // exception
norm_fro_macro(real_t , real_t);
norm_fro_macro(real4_t, real4_t);
norm_fro_macro(real_t , complex_t);
norm_fro_macro(real4_t, complex8_t);
#undef norm_fro_macro

//
// Norm Euclidian
//
#define norm_euc_macro(typeout, typein) \
typeout norm_euc(uint_t n, const typein *a)
norm_euc_macro(int_t  , int_t); // exception
norm_euc_macro(uint_t , uint_t); // exception
norm_euc_macro(real_t , real_t);
norm_euc_macro(real4_t, real4_t);
norm_euc_macro(real_t , complex_t);
norm_euc_macro(real4_t, complex8_t);
#undef norm_euc_macro

//
// Permutations
//
// prop: GENERAL                  B = P*A*Q     if P,Q is nullptr, the identity perm is used
// prop: SYMMETRIC/HERMITIAN/SKEW B = P*A*P^{T} Q is not referenced
//
#define permute_macro(typeout, typein, itypein) \
typeout permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, const itypein *P, const itypein *Q)
permute_macro(void, int_t     , uint_t);
permute_macro(void, uint_t    , uint_t);
permute_macro(void, real_t    , uint_t);
permute_macro(void, real4_t   , uint_t);
permute_macro(void, complex_t , uint_t);
permute_macro(void, complex8_t, uint_t);
permute_macro(void, int_t     ,  int_t);
permute_macro(void, uint_t    ,  int_t);
permute_macro(void, real_t    ,  int_t);
permute_macro(void, real4_t   ,  int_t);
permute_macro(void, complex_t ,  int_t);
permute_macro(void, complex8_t,  int_t);
#undef permute_macro

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_HPP_
