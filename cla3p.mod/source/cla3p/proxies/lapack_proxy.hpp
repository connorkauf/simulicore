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

#ifndef CLA3P_LAPACK_PROXY_HPP_
#define CLA3P_LAPACK_PROXY_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/

int_t laenv(int_t ispec, const char *name, const char *opts, int_t n1, int_t n2, int_t n3, int_t n4);

#define larnv_macro(typein) \
int_t larnv(int_t idist, int_t* iseed, int_t n, typein* x)
larnv_macro(real_t);
larnv_macro(real4_t);
larnv_macro(complex_t);
larnv_macro(complex8_t);
#undef larnv_macro

#define laset_macro(typein) \
int_t laset(char uplo, int_t m, int_t n, typein alpha, typein beta, typein *a, int_t lda)
laset_macro(real_t);
laset_macro(real4_t);
laset_macro(complex_t);
laset_macro(complex8_t);
#undef laset_macro

#define lacpy_macro(typein) \
int_t lacpy(char uplo, int_t m, int_t n, const typein *a, int_t lda, typein *b, int_t ldb)
lacpy_macro(real_t);
lacpy_macro(real4_t);
lacpy_macro(complex_t);
lacpy_macro(complex8_t);
#undef lacpy_macro

#define lacp2_macro(typein) \
int_t lacp2(char uplo, int_t m, int_t n, const TypeTraits<typein>::real_type *a, int_t lda, typein *b, int_t ldb)
lacp2_macro(complex_t );
lacp2_macro(complex8_t);
#undef lacp2_macro

#define lange_macro(typein) \
TypeTraits<typein>::real_type lange(char norm, int_t m, int_t n, const typein *a, int_t lda)
lange_macro(real_t);
lange_macro(real4_t);
lange_macro(complex_t);
lange_macro(complex8_t);
#undef lange_macro

#define lansy_macro(typein) \
TypeTraits<typein>::real_type lansy(char norm, char uplo, int_t n, const typein *a, int_t lda)
lansy_macro(real_t);
lansy_macro(real4_t);
lansy_macro(complex_t);
lansy_macro(complex8_t);
#undef lansy_macro

#define lanhe_macro(typein) \
TypeTraits<typein>::real_type lanhe(char norm, char uplo, int_t n, const typein *a, int_t lda)
lanhe_macro(real_t); // same as lansy
lanhe_macro(real4_t); // same as lansy
lanhe_macro(complex_t);
lanhe_macro(complex8_t);
#undef lanhe_macro

#define lantr_macro(typein) \
TypeTraits<typein>::real_type lantr(char norm, char uplo, char diag, int_t m, int_t n, const typein* a, int_t lda)
lantr_macro(real_t);
lantr_macro(real4_t);
lantr_macro(complex_t);
lantr_macro(complex8_t);
#undef lantr_macro

#define laswp_macro(typein) \
int_t laswp(int_t n, typein *a, int_t lda, int_t k1, int_t k2, const int_t* ipiv, int_t incx)
laswp_macro(real_t);
laswp_macro(real4_t);
laswp_macro(complex_t);
laswp_macro(complex8_t);
#undef laswp_macro

#define laqp2_macro(typein) \
void laqp2(int_t m, int_t n, int_t offset, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, TypeTraits<typein>::real_type *vn1, TypeTraits<typein>::real_type *vn2, typein *work)
laqp2_macro(real_t);
laqp2_macro(real4_t);
laqp2_macro(complex_t);
laqp2_macro(complex8_t);
#undef laqp2_macro

#define laqps_macro(typein) \
void laqps(int_t m, int_t n, int_t offset, int_t nb, int_t *kb, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, TypeTraits<typein>::real_type *vn1, TypeTraits<typein>::real_type *vn2, \
		typein *auxv, typein *f, int_t ldf)
laqps_macro(real_t);
laqps_macro(real4_t);
laqps_macro(complex_t);
laqps_macro(complex8_t);
#undef laqps_macro

#define getrf_macro(typein) \
int_t getrf(int_t m, int_t n, typein *a, int_t lda, int_t *ipiv)
getrf_macro(real_t);
getrf_macro(real4_t);
getrf_macro(complex_t);
getrf_macro(complex8_t);
#undef getrf_macro

#define getrs_macro(typein) \
int_t getrs(char trans, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
getrs_macro(real_t);
getrs_macro(real4_t);
getrs_macro(complex_t);
getrs_macro(complex8_t);
#undef getrs_macro

#define getc2_macro(typein) \
int_t getc2(int_t n, typein *a, int_t lda, int_t *ipiv, int_t *jpiv)
getc2_macro(real_t);
getc2_macro(real4_t);
getc2_macro(complex_t);
getc2_macro(complex8_t);
#undef getc2_macro

#define gesc2_macro(typein) \
int_t gesc2(int_t n,const typein *a, int_t lda, typein *rhs, const int_t *ipiv, const int_t *jpiv, TypeTraits<typein>::real_type *scale)
gesc2_macro(real_t);
gesc2_macro(real4_t);
gesc2_macro(complex_t);
gesc2_macro(complex8_t);
#undef gesc2_macro

#define sytrf_macro(typein) \
int_t sytrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv)
sytrf_macro(real_t);
sytrf_macro(real4_t);
sytrf_macro(complex_t);
sytrf_macro(complex8_t);
#undef sytrf_macro

#define sytrs_macro(typein) \
int_t sytrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
sytrs_macro(real_t);
sytrs_macro(real4_t);
sytrs_macro(complex_t);
sytrs_macro(complex8_t);
#undef sytrs_macro

#define hetrf_macro(typein) \
int_t hetrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv)
hetrf_macro(real_t); // same as sytrf
hetrf_macro(real4_t); // same as sytrf
hetrf_macro(complex_t);
hetrf_macro(complex8_t);
#undef hetrf_macro

#define hetrs_macro(typein) \
int_t hetrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb)
hetrs_macro(real_t); // same as sytrs
hetrs_macro(real4_t); // same as sytrs
hetrs_macro(complex_t);
hetrs_macro(complex8_t);
#undef hetrs_macro

#define potrf_macro(typein) \
int_t potrf(char uplo, int_t n, typein *a, int_t lda)
potrf_macro(real_t);
potrf_macro(real4_t);
potrf_macro(complex_t);
potrf_macro(complex8_t);
#undef potrf_macro

#define potrs_macro(typein) \
int_t potrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb)
potrs_macro(real_t);
potrs_macro(real4_t);
potrs_macro(complex_t);
potrs_macro(complex8_t);
#undef potrs_macro

#define trtrs_macro(typein) \
int_t trtrs(char uplo, char trans, char diag, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb)
trtrs_macro(real_t);
trtrs_macro(real4_t);
trtrs_macro(complex_t);
trtrs_macro(complex8_t);
#undef trtrs_macro

#define gesvd_macro(typein) \
int_t gesvd(char jobu, char jobvt, int_t m, int_t n, typein *a, int_t lda, \
		TypeTraits<typein>::real_type *s, typein *u, int_t ldu, typein *vt, int_t ldvt, \
		TypeTraits<typein>::real_type *superb)
gesvd_macro(real_t);
gesvd_macro(real4_t);
gesvd_macro(complex_t);
gesvd_macro(complex8_t);
#undef gesvd_macro

#define geqrf_macro(typein) \
int_t geqrf(int_t m, int_t n, typein *a, int_t lda, typein *tau)
geqrf_macro(real_t);
geqrf_macro(real4_t);
geqrf_macro(complex_t);
geqrf_macro(complex8_t);
#undef geqrf_macro

#define xxmqr_macro(typein) \
int_t xxmqr(char side, char trans, int_t m, int_t n, int_t k, \
		const typein *a, int_t lda, const typein *tau, typein *c, int_t ldc)
xxmqr_macro(real_t);
xxmqr_macro(real4_t);
xxmqr_macro(complex_t);
xxmqr_macro(complex8_t);
#undef xxmqr_macro

#define xxgqr_macro(typein) \
int_t xxgqr(int_t m, int_t n, int_t k, typein *a, int_t lda, const typein *tau)
xxgqr_macro(real_t);
xxgqr_macro(real4_t);
xxgqr_macro(complex_t);
xxgqr_macro(complex8_t);
#undef xxgqr_macro

/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_PROXY_HPP_
