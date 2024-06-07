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

#ifndef CLA3P_BLAS_PROXY_HPP_
#define CLA3P_BLAS_PROXY_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/

/*------------------ Level 1 ----------------------*/

#define iamax_macro(typein) \
int_t iamax(int_t n, const typein *x, int_t incx)
iamax_macro(real_t);
iamax_macro(real4_t);
iamax_macro(complex_t);
iamax_macro(complex8_t);
#undef iamax_macro

#define asum_macro(typein) \
TypeTraits<typein>::real_type asum(int_t n, const typein *x, int_t incx)
asum_macro(real_t);
asum_macro(real4_t);
asum_macro(complex_t);
asum_macro(complex8_t);
#undef asum_macro

#define copy_macro(typein) \
void copy(int_t n, const typein *x, int_t incx, typein *y, int_t incy)
copy_macro(real_t);
copy_macro(real4_t);
copy_macro(complex_t);
copy_macro(complex8_t);
#undef copy_macro

#define swap_macro(typein) \
void swap(int_t n, typein *x, int_t incx, typein *y, int_t incy)
swap_macro(real_t);
swap_macro(real4_t);
swap_macro(complex_t);
swap_macro(complex8_t);
#undef swap_macro

#define scal_macro(typein) \
void scal(int_t n, typein alpha, typein *x, int_t incx)
scal_macro(real_t);
scal_macro(real4_t);
scal_macro(complex_t);
scal_macro(complex8_t);
#undef scal_macro

#define scal_macro(typein) \
void scal(int_t n, TypeTraits<typein>::real_type alpha, typein *x, int_t incx)
scal_macro(complex_t);
scal_macro(complex8_t);
#undef scal_macro

#define nrm2_macro(typein) \
TypeTraits<typein>::real_type nrm2(int_t n, const typein *x, int_t incx)
nrm2_macro(real_t);
nrm2_macro(real4_t);
nrm2_macro(complex_t);
nrm2_macro(complex8_t);
#undef nrm2_macro

#define dot_macro(typeio) \
typeio dot(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy)
dot_macro(real_t);
dot_macro(real4_t);
dot_macro(complex_t);
dot_macro(complex8_t);
#undef dot_macro

#define dotc_macro(typeio) \
typeio dotc(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy)
dotc_macro(real_t); // same as dot
dotc_macro(real4_t); // same as dot
dotc_macro(complex_t);
dotc_macro(complex8_t);
#undef dotc_macro

#define axpy_macro(typein) \
void axpy(int_t n, typein alpha, const typein *x, int_t incx, typein *y, int_t incy)
axpy_macro(real_t);
axpy_macro(real4_t);
axpy_macro(complex_t);
axpy_macro(complex8_t);
#undef axpy_macro

/*------------------ Level 2 ----------------------*/

#define ger_macro(typein) \
void ger(int_t m, int_t n, typein alpha, \
		const typein *x, int_t incx, \
		const typein *y, int_t incy, \
		typein *a, int_t lda)
ger_macro(real_t);
ger_macro(real4_t);
ger_macro(complex_t);
ger_macro(complex8_t);
#undef ger_macro

#define gerc_macro(typein) \
void gerc(int_t m, int_t n, typein alpha, \
		const typein *x, int_t incx, \
		const typein *y, int_t incy, \
		typein *a, int_t lda)
gerc_macro(real_t); // same as ger
gerc_macro(real4_t); // same as ger
gerc_macro(complex_t);
gerc_macro(complex8_t);
#undef gerc_macro

#define syr_macro(typein) \
void syr(char uplo, int_t n, typein alpha, \
		const typein *x, int_t incx, \
		typein *a, int_t lda)
syr_macro(real_t);
syr_macro(real4_t);
syr_macro(complex_t);
syr_macro(complex8_t);
#undef syr_macro

#define her_macro(typein) \
void her(char uplo, int_t n, TypeTraits<typein>::real_type alpha, \
		const typein *x, int_t incx, \
		typein *a, int_t lda)
her_macro(real_t); // same as syr
her_macro(real4_t); // same as syr
her_macro(complex_t);
her_macro(complex8_t);
#undef her_macro

#define gemv_macro(typein) \
void gemv(char trans, int_t m, int_t n, typein alpha, \
           const typein *a, int_t lda, const typein *x, int_t incx, \
           typein beta, typein *y, int_t incy)
gemv_macro(real_t);
gemv_macro(real4_t);
gemv_macro(complex_t);
gemv_macro(complex8_t);
#undef gemv_macro

#define symv_macro(typein) \
void symv(char uplo, int_t n, typein alpha, const typein *a, int_t lda, \
           const typein *x, int_t incx, typein beta, typein *y, int_t incy)
symv_macro(real_t);
symv_macro(real4_t);
symv_macro(complex_t);
symv_macro(complex8_t);
#undef symv_macro

#define hemv_macro(typein) \
void hemv(char uplo, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy)
hemv_macro(complex_t);
hemv_macro(complex8_t);
#undef hemv_macro

#define trmv_macro(typein) \
void trmv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx)
trmv_macro(real_t);
trmv_macro(real4_t);
trmv_macro(complex_t);
trmv_macro(complex8_t);
#undef trmv_macro

#define trsv_macro(typein) \
void trsv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx)
trsv_macro(real_t);
trsv_macro(real4_t);
trsv_macro(complex_t);
trsv_macro(complex8_t);
#undef trsv_macro

/*------------------ Level 3 ----------------------*/

#define gemm_macro(typein) \
void gemm(char transa, char transb, int_t m, int_t n, int_t k, \
           typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
           typein beta, typein *c, int_t ldc)
gemm_macro(real_t);
gemm_macro(real4_t);
gemm_macro(complex_t);
gemm_macro(complex8_t);
#undef gemm_macro

#define gemmt_macro(typein) \
void gemmt(char uplo, char transa, char transb, int_t n, int_t k, \
           typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
           typein beta, typein *c, int_t ldc)
gemmt_macro(real_t);
gemmt_macro(real4_t);
gemmt_macro(complex_t);
gemmt_macro(complex8_t);
#undef gemmt_macro

#define symm_macro(typein) \
void symm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc)
symm_macro(real_t);
symm_macro(real4_t);
symm_macro(complex_t);
symm_macro(complex8_t);
#undef symm_macro

#define hemm_macro(typein) \
void hemm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc)
hemm_macro(complex_t);
hemm_macro(complex8_t);
#undef hemm_macro

#define trmm_macro(typein) \
void trmm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb)
trmm_macro(real_t);
trmm_macro(real4_t);
trmm_macro(complex_t);
trmm_macro(complex8_t);
#undef trmm_macro

#define trsm_macro(typein) \
void trsm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb)
trsm_macro(real_t);
trsm_macro(real4_t);
trsm_macro(complex_t);
trsm_macro(complex8_t);
#undef trsm_macro

/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BLAS_PROXY_HPP_
