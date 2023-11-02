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

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/

/*------------------ Level 1 ----------------------*/

#define iamax_macro(typeout, typein) \
typeout iamax(int_t n, const typein *x, int_t incx)
iamax_macro(int_t, real_t);
iamax_macro(int_t, real4_t);
iamax_macro(int_t, complex_t);
iamax_macro(int_t, complex8_t);
#undef iamax_macro

#define iamin_macro(typeout, typein) \
typeout iamin(int_t n, const typein *x, int_t incx)
iamin_macro(int_t, real_t);
iamin_macro(int_t, real4_t);
iamin_macro(int_t, complex_t);
iamin_macro(int_t, complex8_t);
#undef iamin_macro

#define asum_macro(typeout, typein) \
typeout asum(int_t n, const typein *x, int_t incx)
asum_macro(real_t, real_t);
asum_macro(real4_t, real4_t);
asum_macro(real_t, complex_t);
asum_macro(real4_t, complex8_t);
#undef asum_macro

#define copy_macro(typeout, typein) \
typeout copy(int_t n, const typein *x, int_t incx, typein *y, int_t incy)
copy_macro(void, real_t);
copy_macro(void, real4_t);
copy_macro(void, complex_t);
copy_macro(void, complex8_t);
#undef copy_macro

#define swap_macro(typeout, typein) \
typeout swap(int_t n, typein *x, int_t incx, typein *y, int_t incy)
swap_macro(void, real_t);
swap_macro(void, real4_t);
swap_macro(void, complex_t);
swap_macro(void, complex8_t);
#undef swap_macro

#define scal_macro(typeout, atypein, typein) \
typeout scal(int_t n, atypein alpha, typein *x, int_t incx)
scal_macro(void, real_t, real_t);
scal_macro(void, real4_t, real4_t);
scal_macro(void, real_t, complex_t);
scal_macro(void, real4_t, complex8_t);
scal_macro(void, complex_t, complex_t);
scal_macro(void, complex8_t, complex8_t);
#undef scal_macro

#define nrm2_macro(typeout, typein) \
typeout nrm2(int_t n, const typein *x, int_t incx)
nrm2_macro(real_t , real_t);
nrm2_macro(real4_t, real4_t);
nrm2_macro(real_t , complex_t);
nrm2_macro(real4_t, complex8_t);
#undef nrm2_macro

#define dot_macro(typeio) \
typeio dot(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy)
dot_macro(real_t);
dot_macro(real4_t);
#undef dot_macro

#define dotu_macro(typeio) \
typeio dotu(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy)
dotu_macro(complex_t);
dotu_macro(complex8_t);
#undef dotu_macro

#define dotc_macro(typeio) \
typeio dotc(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy)
dotc_macro(complex_t);
dotc_macro(complex8_t);
#undef dotc_macro

#define axpy_macro(typeout, typein) \
typeout axpy(int_t n, typein alpha, const typein *x, int_t incx, typein *y, int_t incy)
axpy_macro(void, real_t);
axpy_macro(void, real4_t);
axpy_macro(void, complex_t);
axpy_macro(void, complex8_t);
#undef axpy_macro

/*------------------ Level 2 ----------------------*/

#define gemv_macro(typeout, typein) \
typeout gemv(char trans, int_t m, int_t n, typein alpha, \
           const typein *a, int_t lda, const typein *x, int_t incx, \
           typein beta, typein *y, int_t incy)
gemv_macro(void, real_t);
gemv_macro(void, real4_t);
gemv_macro(void, complex_t);
gemv_macro(void, complex8_t);
#undef gemv_macro

#define symv_macro(typeout, typein) \
typeout symv(char uplo, int_t n, typein alpha, const typein *a, int_t lda, \
           const typein *x, int_t incx, typein beta, typein *y, int_t incy)
symv_macro(void, real_t);
symv_macro(void, real4_t);
symv_macro(void, complex_t);
symv_macro(void, complex8_t);
#undef symv_macro

#define hemv_macro(typeout, typein) \
typeout hemv(char uplo, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy)
hemv_macro(void, complex_t);
hemv_macro(void, complex8_t);
#undef hemv_macro

#define trmv_macro(typeout, typein) \
typeout trmv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx)
trmv_macro(void, real_t);
trmv_macro(void, real4_t);
trmv_macro(void, complex_t);
trmv_macro(void, complex8_t);
#undef trmv_macro

#define trsv_macro(typeout, typein) \
typeout trsv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx)
trsv_macro(void, real_t);
trsv_macro(void, real4_t);
trsv_macro(void, complex_t);
trsv_macro(void, complex8_t);
#undef trsv_macro

#define ger_macro(typeout, typein) \
typeout ger(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda)
ger_macro(void, real_t);
ger_macro(void, real4_t);
#undef ger_macro

#define geru_macro(typeout, typein) \
typeout geru(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda)
geru_macro(void, complex_t);
geru_macro(void, complex8_t);
#undef geru_macro

#define gerc_macro(typeout, typein) \
typeout gerc(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda)
gerc_macro(void, complex_t);
gerc_macro(void, complex8_t);
#undef gerc_macro

/*------------------ Level 3 ----------------------*/

#define gemm_macro(typeout, typein) \
typeout gemm(char transa, char transb, int_t m, int_t n, int_t k, \
           typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
           typein beta, typein *c, int_t ldc)
gemm_macro(void, real_t);
gemm_macro(void, real4_t);
gemm_macro(void, complex_t);
gemm_macro(void, complex8_t);
#undef gemm_macro

#define gemmt_macro(typeout, typein) \
typeout gemmt(char uplo, char transa, char transb, int_t n, int_t k, \
           typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
           typein beta, typein *c, int_t ldc)
gemmt_macro(void, real_t);
gemmt_macro(void, real4_t);
gemmt_macro(void, complex_t);
gemmt_macro(void, complex8_t);
#undef gemmt_macro

#define symm_macro(typeout, typein) \
typeout symm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc)
symm_macro(void, real_t);
symm_macro(void, real4_t);
symm_macro(void, complex_t);
symm_macro(void, complex8_t);
#undef symm_macro

#define hemm_macro(typeout, typein) \
typeout hemm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc)
hemm_macro(void, complex_t);
hemm_macro(void, complex8_t);
#undef hemm_macro

#define trmm_macro(typeout, typein) \
typeout trmm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb)
trmm_macro(void, real_t);
trmm_macro(void, real4_t);
trmm_macro(void, complex_t);
trmm_macro(void, complex8_t);
#undef trmm_macro

#define trsm_macro(typeout, typein) \
typeout trsm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb)
trsm_macro(void, real_t);
trsm_macro(void, real4_t);
trsm_macro(void, complex_t);
trsm_macro(void, complex8_t);
#undef trsm_macro

/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BLAS_PROXY_HPP_
