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

// this file inc
#include "cla3p/proxies/lapack_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/
int_t laenv(int_t ispec, const char *name, const char *opts, int_t n1, int_t n2, int_t n3, int_t n4)
{
	return ilaenv(&ispec, name, opts, &n1, &n2, &n3, &n4);
}
/*-------------------------------------------------*/
#define larnv_macro(typeout, typein, prefix) \
typeout larnv(int_t idist, int_t* iseed, int_t n, typein* x) \
{ \
	return LAPACKE_##prefix##larnv(idist, iseed, n, x); \
}
larnv_macro(int_t, real_t    , d)
larnv_macro(int_t, real4_t   , s)
larnv_macro(int_t, complex_t , z)
larnv_macro(int_t, complex8_t, c)
#undef larnv_macro
/*-------------------------------------------------*/
#define laset_macro(typeout, typein, prefix) \
typeout laset(char uplo, int_t m, int_t n, typein alpha, typein beta, typein *a, int_t lda) \
{ \
	return LAPACKE_##prefix##laset(LAPACK_COL_MAJOR, uplo, m, n, alpha, beta, a, lda); \
}
laset_macro(int_t, real_t    , d)
laset_macro(int_t, real4_t   , s)
laset_macro(int_t, complex_t , z)
laset_macro(int_t, complex8_t, c)
#undef laset_macro
/*-------------------------------------------------*/
#define lacpy_macro(typeout, typein, prefix) \
typeout lacpy(char uplo, int_t m, int_t n, const typein *a, int_t lda, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##lacpy(LAPACK_COL_MAJOR, uplo, m, n, a, lda, b, ldb); \
}
lacpy_macro(int_t, real_t    , d)
lacpy_macro(int_t, real4_t   , s)
lacpy_macro(int_t, complex_t , z)
lacpy_macro(int_t, complex8_t, c)
#undef lacpy_macro
/*-------------------------------------------------*/
#define lacp2_macro(typeout, rtypein, typein, prefix) \
typeout lacp2(char uplo, int_t m, int_t n, const rtypein *a, int_t lda, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##lacp2(LAPACK_COL_MAJOR, uplo, m, n, a, lda, b, ldb); \
}
lacp2_macro(int_t, real_t , complex_t , z)
lacp2_macro(int_t, real4_t, complex8_t, c)
#undef lacp2_macro
/*-------------------------------------------------*/
#define lange_macro(typeout, typein, prefix) \
typeout lange(char norm, int_t m, int_t n, const typein *a, int_t lda) \
{ \
	return LAPACKE_##prefix##lange(LAPACK_COL_MAJOR, norm, m, n, a, lda); \
}
lange_macro(real_t , real_t    , d)
lange_macro(real4_t, real4_t   , s)
lange_macro(real_t , complex_t , z)
lange_macro(real4_t, complex8_t, c)
#undef lange_macro
/*-------------------------------------------------*/
#define lansy_macro(typeout, typein, prefix) \
typeout lansy(char norm, char uplo, int_t n, const typein *a, int_t lda) \
{ \
	return LAPACKE_##prefix##lansy(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); \
}
lansy_macro(real_t , real_t    , d)
lansy_macro(real4_t, real4_t   , s)
lansy_macro(real_t , complex_t , z)
lansy_macro(real4_t, complex8_t, c)
#undef lansy_macro
/*-------------------------------------------------*/
real_t  lanhe(char, char, int_t, const real_t *, int_t) { throw err::Exception(msg::OpNotAllowed()); return 0; }
real4_t lanhe(char, char, int_t, const real4_t*, int_t) { throw err::Exception(msg::OpNotAllowed()); return 0; }
/*-------------------------------------------------*/
#define lanhe_macro(typeout, typein, prefix) \
typeout lanhe(char norm, char uplo, int_t n, const typein *a, int_t lda) \
{ \
	return LAPACKE_##prefix##lanhe(LAPACK_COL_MAJOR, norm, uplo, n, a, lda); \
}
lanhe_macro(real_t , complex_t , z)
lanhe_macro(real4_t, complex8_t, c)
#undef lanhe_macro
/*-------------------------------------------------*/
#define lantr_macro(typeout, typein, prefix) \
typeout lantr(char norm, char uplo, char diag, int_t m, int_t n, const typein* a, int_t lda) \
{ \
	return LAPACKE_##prefix##lantr(LAPACK_COL_MAJOR, norm, uplo, diag, m, n, a, lda); \
}
lantr_macro(real_t , real_t    , d)
lantr_macro(real4_t, real4_t   , s)
lantr_macro(real_t , complex_t , z)
lantr_macro(real4_t, complex8_t, c)
#undef lantr_macro
/*-------------------------------------------------*/
#define laswp_macro(typeout, typein, prefix) \
typeout laswp(int_t n, typein *a, int_t lda, int_t k1, int_t k2, const int_t* ipiv, int_t incx) \
{ \
	return LAPACKE_##prefix##laswp(LAPACK_COL_MAJOR, n, a, lda, k1, k2, ipiv, incx); \
}
laswp_macro(int_t, real_t    , d);
laswp_macro(int_t, real4_t   , s);
laswp_macro(int_t, complex_t , z);
laswp_macro(int_t, complex8_t, c);
#undef laswp_macro
/*-------------------------------------------------*/
#define laqp2_macro(typeout, rtypein, typein, prefix) \
typeout laqp2(int_t m, int_t n, int_t offset, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, rtypein *vn1, rtypein *vn2, typein *work) \
{ \
	prefix##laqp2(&m, &n, &offset, a, &lda, jpvt, tau, vn1, vn2, work); \
}
laqp2_macro(void, real_t , real_t    , d);
laqp2_macro(void, real4_t, real4_t   , s);
laqp2_macro(void, real_t , complex_t , z);
laqp2_macro(void, real4_t, complex8_t, c);
#undef laqp2_macro
/*-------------------------------------------------*/
#define laqps_macro(typeout, rtypein, typein, prefix) \
typeout laqps(int_t m, int_t n, int_t offset, int_t nb, int_t *kb, typein *a, int_t lda, \
		int_t *jpvt, typein *tau, rtypein *vn1, rtypein *vn2, typein *auxv, typein *f, int_t ldf) \
{ \
	prefix##laqps(&m, &n, &offset, &nb, kb, a, &lda, jpvt, tau, vn1, vn2, auxv, f, &ldf); \
}
laqps_macro(void, real_t , real_t    , d);
laqps_macro(void, real4_t, real4_t   , s);
laqps_macro(void, real_t , complex_t , z);
laqps_macro(void, real4_t, complex8_t, c);
#undef laqps_macro
/*-------------------------------------------------*/
#define getrf_macro(typeout, typein, prefix) \
typeout getrf(int_t m, int_t n, typein *a, int_t lda, int_t *ipiv) \
{ \
	return LAPACKE_##prefix##getrf(LAPACK_COL_MAJOR, m, n, a, lda, ipiv); \
}
getrf_macro(int_t, real_t    , d)
getrf_macro(int_t, real4_t   , s)
getrf_macro(int_t, complex_t , z)
getrf_macro(int_t, complex8_t, c)
#undef getrf_macro
/*-------------------------------------------------*/
#define getrs_macro(typeout, typein, prefix) \
typeout getrs(char trans, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##getrs(LAPACK_COL_MAJOR, trans, n, nrhs, a, lda, ipiv, b, ldb); \
}
getrs_macro(int_t, real_t    , d)
getrs_macro(int_t, real4_t   , s)
getrs_macro(int_t, complex_t , z)
getrs_macro(int_t, complex8_t, c)
#undef getrs_macro
/*-------------------------------------------------*/
#define getc2_macro(typeout, typein, prefix) \
typeout getc2(int_t n, typein *a, int_t lda, int_t *ipiv, int_t *jpiv) \
{ \
	int_t info = 0; \
	prefix##getc2(&n, a, &lda, ipiv, jpiv, &info); \
	return info; \
}
getc2_macro(int_t, real_t    , d)
getc2_macro(int_t, real4_t   , s)
getc2_macro(int_t, complex_t , z)
getc2_macro(int_t, complex8_t, c)
#undef getc2_macro
/*-------------------------------------------------*/
#define gesc2_macro(typeout, rtypein, typein, prefix) \
typeout gesc2(int_t n, const typein *a, int_t lda, typein *rhs, const int_t *ipiv, const int_t *jpiv, rtypein *scale) \
{ \
	int_t info = 0; \
	prefix##gesc2(&n, a, &lda, rhs, ipiv, jpiv, scale); \
	return info; \
}
gesc2_macro(int_t, real_t , real_t    , d)
gesc2_macro(int_t, real4_t, real4_t   , s)
gesc2_macro(int_t, real_t , complex_t , z)
gesc2_macro(int_t, real4_t, complex8_t, c)
#undef gesc2_macro
/*-------------------------------------------------*/
#define sytrf_macro(typeout, typein, prefix) \
typeout sytrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv) \
{ \
	return LAPACKE_##prefix##sytrf(LAPACK_COL_MAJOR, uplo, n, a, lda, ipiv); \
}
sytrf_macro(int_t, real_t    , d)
sytrf_macro(int_t, real4_t   , s)
sytrf_macro(int_t, complex_t , z)
sytrf_macro(int_t, complex8_t, c)
#undef sytrf_macro
/*-------------------------------------------------*/
#define sytrs_macro(typeout, typein, prefix) \
typeout sytrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##sytrs(LAPACK_COL_MAJOR, uplo, n, nrhs, a, lda, ipiv, b, ldb); \
}
sytrs_macro(int_t, real_t    , d)
sytrs_macro(int_t, real4_t   , s)
sytrs_macro(int_t, complex_t , z)
sytrs_macro(int_t, complex8_t, c)
#undef sytrs_macro
/*-------------------------------------------------*/
int_t hetrf(char, int_t, real_t *, int_t, int_t*){ throw err::Exception(msg::OpNotAllowed()); return 0; }
int_t hetrf(char, int_t, real4_t*, int_t, int_t*){ throw err::Exception(msg::OpNotAllowed()); return 0; }
/*-------------------------------------------------*/
#define hetrf_macro(typeout, typein, prefix) \
typeout hetrf(char uplo, int_t n, typein *a, int_t lda, int_t *ipiv) \
{ \
	return LAPACKE_##prefix##hetrf(LAPACK_COL_MAJOR, uplo, n, a, lda, ipiv); \
}
hetrf_macro(int_t, complex_t , z)
hetrf_macro(int_t, complex8_t, c)
#undef hetrf_macro
/*-------------------------------------------------*/
int_t hetrs(char, int_t, int_t, const real_t *, int_t, const int_t*, real_t *, int_t){ throw err::Exception(msg::OpNotAllowed()); return 0; }
int_t hetrs(char, int_t, int_t, const real4_t*, int_t, const int_t*, real4_t*, int_t){ throw err::Exception(msg::OpNotAllowed()); return 0; }
/*-------------------------------------------------*/
#define hetrs_macro(typeout, typein, prefix) \
typeout hetrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, const int_t *ipiv, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##hetrs(LAPACK_COL_MAJOR, uplo, n, nrhs, a, lda, ipiv, b, ldb); \
}
hetrs_macro(int_t, complex_t , z)
hetrs_macro(int_t, complex8_t, c)
#undef hetrs_macro
/*-------------------------------------------------*/
#define potrf_macro(typeout, typein, prefix) \
typeout potrf(char uplo, int_t n, typein *a, int_t lda) \
{ \
	return LAPACKE_##prefix##potrf(LAPACK_COL_MAJOR, uplo, n, a, lda); \
}
potrf_macro(int_t, real_t    , d)
potrf_macro(int_t, real4_t   , s)
potrf_macro(int_t, complex_t , z)
potrf_macro(int_t, complex8_t, c)
#undef potrf_macro
/*-------------------------------------------------*/
#define potrs_macro(typeout, typein, prefix) \
typeout potrs(char uplo, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##potrs(LAPACK_COL_MAJOR, uplo, n, nrhs, a, lda, b, ldb); \
}
potrs_macro(int_t, real_t    , d)
potrs_macro(int_t, real4_t   , s)
potrs_macro(int_t, complex_t , z)
potrs_macro(int_t, complex8_t, c)
#undef potrs_macro
/*-------------------------------------------------*/
#define trtrs_macro(typeout, typein, prefix) \
typeout trtrs(char uplo, char trans, char diag, int_t n, int_t nrhs, const typein *a, int_t lda, typein *b, int_t ldb) \
{ \
	return LAPACKE_##prefix##trtrs(LAPACK_COL_MAJOR, uplo, trans, diag, n, nrhs, a, lda, b, ldb); \
}
trtrs_macro(int_t, real_t    , d)
trtrs_macro(int_t, real4_t   , s)
trtrs_macro(int_t, complex_t , z)
trtrs_macro(int_t, complex8_t, c)
#undef trtrs_macro
/*-------------------------------------------------*/
#define gesvd_macro(typeout, rtypein, typein, prefix) \
typeout gesvd(char jobu, char jobvt, int_t m, int_t n, typein *a, int_t lda, \
    rtypein *s, typein *u, int_t ldu, typein *vt, int_t ldvt, rtypein *superb) \
{ \
	return LAPACKE_##prefix##gesvd(LAPACK_COL_MAJOR, jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, superb); \
}
gesvd_macro(int_t, real_t , real_t    , d)
gesvd_macro(int_t, real4_t, real4_t   , s)
gesvd_macro(int_t, real_t , complex_t , z)
gesvd_macro(int_t, real4_t, complex8_t, c)
#undef gesvd_macro
/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/
