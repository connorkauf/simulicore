/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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

#ifndef CLA3P_LAPACK_PROXY_HPP_
#define CLA3P_LAPACK_PROXY_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/

int_t laenv(int_t ispec, const char *name, const char *opts, int_t n1, int_t n2, int_t n3, int_t n4);

#define larnv_macro(typeout, typein) \
typeout larnv(int_t idist, int_t* iseed, int_t n, typein* x)
larnv_macro(int_t, real_t);
larnv_macro(int_t, real4_t);
larnv_macro(int_t, complex_t);
larnv_macro(int_t, complex8_t);
#undef larnv_macro

#define laset_macro(typeout, typein) \
typeout laset(char uplo, int_t m, int_t n, typein alpha, typein beta, typein *a, int_t lda)
laset_macro(int_t, real_t);
laset_macro(int_t, real4_t);
laset_macro(int_t, complex_t);
laset_macro(int_t, complex8_t);
#undef laset_macro

#define lacpy_macro(typeout, typein) \
typeout lacpy(char uplo, int_t m, int_t n, const typein *a, int_t lda, typein *b, int_t ldb)
lacpy_macro(int_t, real_t);
lacpy_macro(int_t, real4_t);
lacpy_macro(int_t, complex_t);
lacpy_macro(int_t, complex8_t);
#undef lacpy_macro

#define lacp2_macro(typeout, rtypein, ctypein) \
typeout lacp2(char uplo, int_t m, int_t n, const rtypein *a, int_t lda, ctypein *b, int_t ldb)
lacp2_macro(int_t, real_t , complex_t );
lacp2_macro(int_t, real4_t, complex8_t);
#undef lacp2_macro

#define lange_macro(typeout, typein) \
typeout lange(char norm, int_t m, int_t n, const typein *a, int_t lda)
lange_macro(real_t , real_t);
lange_macro(real4_t, real4_t);
lange_macro(real_t , complex_t);
lange_macro(real4_t, complex8_t);
#undef lange_macro

#define lansy_macro(typeout, typein) \
typeout lansy(char norm, char uplo, int_t n, const typein *a, int_t lda)
lansy_macro(real_t , real_t);
lansy_macro(real4_t, real4_t);
lansy_macro(real_t , complex_t);
lansy_macro(real4_t, complex8_t);
#undef lansy_macro

#define lanhe_macro(typeout, typein) \
typeout lanhe(char norm, char uplo, int_t n, const typein *a, int_t lda)
lanhe_macro(real_t , real_t); // exception
lanhe_macro(real4_t, real4_t); // exception
lanhe_macro(real_t , complex_t);
lanhe_macro(real4_t, complex8_t);
#undef lanhe_macro

#define lantr_macro(typeout, typein) \
typeout lantr(char norm, char uplo, char diag, int_t m, int_t n, const typein* a, int_t lda)
lantr_macro(real_t , real_t);
lantr_macro(real4_t, real4_t);
lantr_macro(real_t , complex_t);
lantr_macro(real4_t, complex8_t);
#undef lantr_macro

#define laswp_macro(typeout, typein) \
typeout laswp(int_t n, typein *a, int_t lda, int_t k1, int_t k2, const int_t* ipiv, int_t incx)
laswp_macro(int_t, real_t);
laswp_macro(int_t, real4_t);
laswp_macro(int_t, complex_t);
laswp_macro(int_t, complex8_t);
#undef laswp_macro

#define laqp2_macro(typeout, rtypein, typein) \
typeout laqp2(int_t m, int_t n, int_t offset, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, rtypein *vn1, rtypein *vn2, typein *work)
laqp2_macro(void, real_t, real_t);
laqp2_macro(void, real4_t, real4_t);
laqp2_macro(void, real_t, complex_t);
laqp2_macro(void, real4_t, complex8_t);
#undef laqp2_macro

#define laqps_macro(typeout, rtypein, typein) \
typeout laqps(int_t m, int_t n, int_t offset, int_t nb, int_t *kb, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, rtypein *vn1, rtypein *vn2, typein *auxv, typein *f, int_t ldf)
laqps_macro(void, real_t, real_t);
laqps_macro(void, real4_t, real4_t);
laqps_macro(void, real_t, complex_t);
laqps_macro(void, real4_t, complex8_t);
#undef laqps_macro

#define getrf_macro(typeout, typein) \
typeout getrf(int_t m, int_t n, typein *a, int_t lda, int_t *ipiv)
getrf_macro(int_t, real_t);
getrf_macro(int_t, real4_t);
getrf_macro(int_t, complex_t);
getrf_macro(int_t, complex8_t);
#undef getrf_macro

#define getrs_macro(typeout, typein) \
typeout getrs(char trans, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
getrs_macro(int_t, real_t);
getrs_macro(int_t, real4_t);
getrs_macro(int_t, complex_t);
getrs_macro(int_t, complex8_t);
#undef getrs_macro

#define getc2_macro(typeout, typein) \
typeout getc2(int_t n, typein *a, int_t lda, int_t *ipiv, int_t *jpiv)
getc2_macro(int_t, real_t);
getc2_macro(int_t, real4_t);
getc2_macro(int_t, complex_t);
getc2_macro(int_t, complex8_t);
#undef getc2_macro

#define gesc2_macro(typeout, rtypein, typein) \
typeout gesc2(int_t n, const typein *a, int_t lda, typein *rhs, const int_t *ipiv, const int_t *jpiv, rtypein *scale)
gesc2_macro(int_t, real_t, real_t);
gesc2_macro(int_t, real4_t, real4_t);
gesc2_macro(int_t, real_t, complex_t);
gesc2_macro(int_t, real4_t, complex8_t);
#undef gesc2_macro

#define sytrf_macro(typeout, typein) \
typeout sytrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv)
sytrf_macro(int_t, real_t);
sytrf_macro(int_t, real4_t);
sytrf_macro(int_t, complex_t);
sytrf_macro(int_t, complex8_t);
#undef sytrf_macro

#define sytrs_macro(typeout, typein) \
typeout sytrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
sytrs_macro(int_t, real_t);
sytrs_macro(int_t, real4_t);
sytrs_macro(int_t, complex_t);
sytrs_macro(int_t, complex8_t);
#undef sytrs_macro

#define hetrf_macro(typeout, typein) \
typeout hetrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv)
hetrf_macro(int_t, real_t); // exception
hetrf_macro(int_t, real4_t); // exception
hetrf_macro(int_t, complex_t);
hetrf_macro(int_t, complex8_t);
#undef hetrf_macro

#define hetrs_macro(typeout, typein) \
typeout hetrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
hetrs_macro(int_t, real_t); // exception
hetrs_macro(int_t, real4_t); // exception
hetrs_macro(int_t, complex_t);
hetrs_macro(int_t, complex8_t);
#undef hetrs_macro

#define potrf_macro(typeout, typein) \
typeout potrf(char uplo, int_t n, typein *a, int_t lda)
potrf_macro(int_t, real_t);
potrf_macro(int_t, real4_t);
potrf_macro(int_t, complex_t);
potrf_macro(int_t, complex8_t);
#undef potrf_macro

#define potrs_macro(typeout, typein) \
typeout potrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb)
potrs_macro(int_t, real_t);
potrs_macro(int_t, real4_t);
potrs_macro(int_t, complex_t);
potrs_macro(int_t, complex8_t);
#undef potrs_macro

#define trtrs_macro(typeout, typein) \
typeout trtrs(char uplo, char trans, char diag, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb)
trtrs_macro(int_t, real_t);
trtrs_macro(int_t, real4_t);
trtrs_macro(int_t, complex_t);
trtrs_macro(int_t, complex8_t);
#undef trtrs_macro

#define gesvd_macro(typeout, rtypein, typein) \
typeout gesvd(char jobu, char jobvt, int_t m, int_t n, typein *a, int_t lda, \
		rtypein *s, typein *u, int_t ldu, typein *vt, int_t ldvt, rtypein *superb)
gesvd_macro(int_t, real_t, real_t);
gesvd_macro(int_t, real4_t, real4_t);
gesvd_macro(int_t, real_t, complex_t);
gesvd_macro(int_t, real4_t, complex8_t);
#undef gesvd_macro

/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_PROXY_HPP_
