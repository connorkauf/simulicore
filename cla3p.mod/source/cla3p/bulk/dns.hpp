/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
template <typename T_Scalar>
inline T_Scalar* ptrmv(uint_t lda, T_Scalar *a, uint_t i, uint_t j)
{
	return (a + i + j * lda);
}

//
// Get value (column-major)
//
template <typename T_Scalar>
inline T_Scalar& entry(uint_t lda, T_Scalar *a, uint_t i, uint_t j)
{
	return *ptrmv(lda,a,i,j);
}

//
// Set zeros on diagonal depending on property
//
#define set_diag_zeros_macro(typein) \
void set_diag_zeros(prop_t ptype, uint_t n, typein *a, uint_t lda)
set_diag_zeros_macro(int_t);
set_diag_zeros_macro(uint_t);
set_diag_zeros_macro(real_t);
set_diag_zeros_macro(real4_t);
set_diag_zeros_macro(complex_t);
set_diag_zeros_macro(complex8_t);
#undef set_diag_zeros

//
// Set all entries to val
//
#define fill_macro(typein) \
void fill(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein val)
fill_macro(int_t);
fill_macro(uint_t);
fill_macro(real_t);
fill_macro(real4_t);
fill_macro(complex_t);
fill_macro(complex8_t);
#undef fill_macro

//
// Set all entries to val (separate diagonal)
//
#define fill_macro(typein) \
void fill(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein val, typein dval)
fill_macro(int_t);
fill_macro(uint_t);
fill_macro(real_t);
fill_macro(real4_t);
fill_macro(complex_t);
fill_macro(complex8_t);
#undef fill_macro

//
// Set all entries to zero
//
template <typename T_Scalar>
void zero(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	fill(uplo, m, n, a, lda, 0);
}

//
// Allocate memory
//
template <typename T_Scalar>
T_Scalar* alloc(uint_t m, uint_t n, uint_t lda, bool wipe = false)
{
	T_Scalar *ret = static_cast<T_Scalar*>(i_malloc(lda * n, sizeof(T_Scalar)));
	if(wipe) {
		zero(uplo_t::Full, m, n, ret, lda);
	} // wipe
	return ret;
}

//
// Set random values
//
#define rand_macro(typein, lval, hval) \
void rand(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, \
		TypeTraits<typein>::real_type low = lval, \
		TypeTraits<typein>::real_type high = hval)
rand_macro(int_t     , 0, 100);
rand_macro(uint_t    , 0, 100);
rand_macro(real_t    , 0,   1);
rand_macro(real4_t   , 0,   1);
rand_macro(complex_t , 0,   1);
rand_macro(complex8_t, 0,   1);
#undef rand_macro

//
// Copy
//
#define copy_macro(typein) \
void copy(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, \
		typein *b, uint_t ldb, typein coeff = 1)
copy_macro(int_t);
copy_macro(uint_t);
copy_macro(real_t);
copy_macro(real4_t);
copy_macro(complex_t);
copy_macro(complex8_t);
#undef copy_macro

//
// Get real part from complex
//
#define get_real_macro(typein) \
void get_real(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, \
		TypeTraits<typein>::real_type *b, uint_t ldb)
get_real_macro(complex_t);
get_real_macro(complex8_t);
#undef get_real_macro

//
// Get imag part from complex
//
#define get_imag_macro(typein) \
void get_imag(uplo_t uplo, uint_t m, uint_t n, const typein *a, uint_t lda, \
		TypeTraits<typein>::real_type *b, uint_t ldb)
get_imag_macro(complex_t);
get_imag_macro(complex8_t);
#undef get_imag_macro

//
// Set real part to complex
//
#define set_real_macro(typein) \
void set_real(uplo_t uplo, uint_t m, uint_t n, const TypeTraits<typein>::real_type *a, uint_t lda, \
		typein *b, uint_t ldb)
set_real_macro(complex_t);
set_real_macro(complex8_t);
#undef set_real_macro

//
// Set imag part to complex
//
#define set_imag_macro(typein) \
void set_imag(uplo_t uplo, uint_t m, uint_t n, const TypeTraits<typein>::real_type *a, uint_t lda, \
		typein *b, uint_t ldb)
set_imag_macro(complex_t);
set_imag_macro(complex8_t);
#undef set_imag_macro

//
// Scale
//
#define scale_macro(typein) \
void scale(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein coeff)
scale_macro(real_t);
scale_macro(real4_t);
scale_macro(complex_t);
scale_macro(complex8_t);
#undef scale_macro

//
// Transpositions
//
#define transpose_macro(typein) \
void transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
transpose_macro(real_t);
transpose_macro(real4_t);
transpose_macro(complex_t);
transpose_macro(complex8_t);
#undef transpose_macro

//
// Conjugate transpositions
//
#define conjugate_transpose_macro(typein) \
void conjugate_transpose(uint_t m, uint_t n, const typein *a, uint_t lda, typein *b, uint_t ldb, typein coeff = 1)
conjugate_transpose_macro(real_t); // transpose
conjugate_transpose_macro(real4_t); // transpose
conjugate_transpose_macro(complex_t);
conjugate_transpose_macro(complex8_t);
#undef conjugate_transpose_macro

//
// Conjugations
//
#define conjugate_macro(typein) \
void conjugate(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda, typein coeff = 1)
conjugate_macro(real_t); // does nothing
conjugate_macro(real4_t); // does nothing
conjugate_macro(complex_t);
conjugate_macro(complex8_t);
#undef conjugate_macro

//
// Symmetric to general
//
#define sy2ge_macro(typein) \
void sy2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
sy2ge_macro(real_t);
sy2ge_macro(real4_t);
sy2ge_macro(complex_t);
sy2ge_macro(complex8_t);
#undef sy2ge_macro

//
// Hermitian to general
//
#define he2ge_macro(typein) \
void he2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
he2ge_macro(real_t); // exception
he2ge_macro(real4_t); // exception
he2ge_macro(complex_t);
he2ge_macro(complex8_t);
#undef he2ge_macro

//
// Skew to general
//
#define sk2ge_macro(typein) \
void sk2ge(uplo_t uplo, uint_t n, typein *a, uint_t lda)
sk2ge_macro(real_t);
sk2ge_macro(real4_t);
sk2ge_macro(complex_t);
sk2ge_macro(complex8_t);
#undef sk2ge_macro

//
// Triangular to general
//
#define tr2ge_macro(typein) \
void tr2ge(uplo_t uplo, uint_t m, uint_t n, typein *a, uint_t lda)
tr2ge_macro(real_t);
tr2ge_macro(real4_t);
tr2ge_macro(complex_t);
tr2ge_macro(complex8_t);
#undef tr2ge_macro

//
// Norm 1
//
#define norm_one_macro(typein) \
TypeTraits<typein>::real_type norm_one(prop_t ptype, uplo_t uplo, \
		uint_t m, uint_t n, const typein *a, uint_t lda)
norm_one_macro(real_t);
norm_one_macro(real4_t);
norm_one_macro(complex_t);
norm_one_macro(complex8_t);
#undef norm_one_macro

//
// Norm Inf
//
#define norm_inf_macro(typein) \
TypeTraits<typein>::real_type norm_inf(prop_t ptype, uplo_t uplo, \
		uint_t m, uint_t n, const typein *a, uint_t lda)
norm_inf_macro(real_t);
norm_inf_macro(real4_t);
norm_inf_macro(complex_t);
norm_inf_macro(complex8_t);
#undef norm_inf_macro

//
// Norm Max
//
#define norm_max_macro(typein) \
TypeTraits<typein>::real_type norm_max(prop_t ptype, uplo_t uplo, \
		uint_t m, uint_t n, const typein *a, uint_t lda)
norm_max_macro(real_t);
norm_max_macro(real4_t);
norm_max_macro(complex_t);
norm_max_macro(complex8_t);
#undef norm_max_macro

//
// Norm Frobenius
//
#define norm_fro_macro(typein) \
TypeTraits<typein>::real_type norm_fro(prop_t ptype, uplo_t uplo, \
		uint_t m, uint_t n, const typein *a, uint_t lda)
norm_fro_macro(real_t);
norm_fro_macro(real4_t);
norm_fro_macro(complex_t);
norm_fro_macro(complex8_t);
#undef norm_fro_macro

//
// Norm Euclidean
//
#define norm_euc_macro(typein) \
TypeTraits<typein>::real_type norm_euc(uint_t n, const typein *a)
norm_euc_macro(real_t);
norm_euc_macro(real4_t);
norm_euc_macro(complex_t);
norm_euc_macro(complex8_t);
#undef norm_euc_macro

//
// Permutations
//
// prop: General                  B = P*A*Q     if P,Q is nullptr, the identity perm is used
// prop: Symmetric/Hermitian/Skew B = P*A*P^{T} Q is not referenced
//
template <typename T_Scalar>
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, 
		T_Scalar *b, uint_t ldb, const int_t *P, const int_t *Q);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_HPP_
