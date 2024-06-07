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
#include "cla3p/proxies/blas_proxy.hpp"

// system

// 3rd
#if defined(SIMULICORE_MACOS)
#include <Accelerate/Accelerate.h>
#elif defined(CLA3P_INTEL_MKL)
#include <mkl_blas.h>
#include <mkl_lapack.h> // blas header misses some definitions
#endif

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/bulk/dns.hpp"

/*-------------------------------------------------*/
#if defined(SIMULICORE_MACOS)
#define blas_func_name(name) name##_
#else
#define blas_func_name(name) name
#endif
/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/
#define iamax_macro(typein, prefix) \
int_t iamax(int_t n, const typein *x, int_t incx) \
{ \
	return (blas_func_name(i##prefix##amax)(&n, x, &incx) - 1); \
}
iamax_macro(real_t    , d);
iamax_macro(real4_t   , s);
iamax_macro(complex_t , z);
iamax_macro(complex8_t, c);
#undef iamax_macro
/*-------------------------------------------------*/
#define asum_macro(typein, prefix) \
TypeTraits<typein>::real_type asum(int_t n, const typein *x, int_t incx) \
{ \
	return blas_func_name(prefix##asum)(&n, x, &incx); \
}
asum_macro(real_t    ,  d);
asum_macro(real4_t   ,  s);
asum_macro(complex_t , dz);
asum_macro(complex8_t, sc);
#undef asum_macro
/*-------------------------------------------------*/
#define copy_macro(typein, prefix) \
void copy(int_t n, const typein *x, int_t incx, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##copy)(&n, x, &incx, y, &incy); \
}
copy_macro(real_t    , d)
copy_macro(real4_t   , s)
copy_macro(complex_t , z)
copy_macro(complex8_t, c)
#undef copy_macro
/*-------------------------------------------------*/
#define swap_macro(typein, prefix) \
void swap(int_t n, typein *x, int_t incx, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##swap)(&n, x, &incx, y, &incy); \
}
swap_macro(real_t    , d)
swap_macro(real4_t   , s)
swap_macro(complex_t , z)
swap_macro(complex8_t, c)
#undef swap_macro
/*-------------------------------------------------*/
#define scal_macro(typein, prefix) \
void scal(int_t n, typein alpha, typein *x, int_t incx) \
{ \
	blas_func_name(prefix##scal)(&n, &alpha, x, &incx); \
}
scal_macro(real_t    , d)
scal_macro(real4_t   , s);
scal_macro(complex_t , z);
scal_macro(complex8_t, c);
#undef scal_macro
/*-------------------------------------------------*/
#define scal_macro(typein, prefix) \
void scal(int_t n, TypeTraits<typein>::real_type alpha, typein *x, int_t incx) \
{ \
	blas_func_name(prefix##scal)(&n, &alpha, x, &incx); \
}
scal_macro(complex_t , zd);
scal_macro(complex8_t, cs);
#undef scal_macro
/*-------------------------------------------------*/
#define nrm2_macro(typein, prefix) \
TypeTraits<typein>::real_type nrm2(int_t n, const typein *x, int_t incx) \
{ \
	return blas_func_name(prefix##nrm2)(&n, x, &incx); \
}
nrm2_macro(real_t    ,  d)
nrm2_macro(real4_t   ,  s)
nrm2_macro(complex_t , dz)
nrm2_macro(complex8_t, sc)
#undef nrm2_macro
/*-------------------------------------------------*/
#define real_dot_macro(typeio, prefix, suffix) \
typeio dot##suffix(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy) \
{ \
	return blas_func_name(prefix##dot)(&n, x, &incx, y, &incy); \
}
real_dot_macro(real_t , d,  )
real_dot_macro(real4_t, s,  )
real_dot_macro(real_t , d, c)
real_dot_macro(real4_t, s, c)
#undef real_dot_macro
/*-------------------------------------------------*/
#define complex_dot_macro(typeio, prefix, suffix, blas_suffix) \
typeio dot##suffix(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy) \
{ \
	typeio res;  \
	blas_func_name(prefix##dot##blas_suffix)(&res, &n, x, &incx, y, &incy); \
	return res; \
}
complex_dot_macro(complex_t , z,  , u)
complex_dot_macro(complex8_t, c,  , u)
complex_dot_macro(complex_t , z, c, c)
complex_dot_macro(complex8_t, c, c, c)
#undef complex_dot_macro
/*-------------------------------------------------*/
#define axpy_macro(typein, prefix) \
void axpy(int_t n, typein alpha, const typein *x, int_t incx, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##axpy)(&n, &alpha, x, &incx, y, &incy); \
}
axpy_macro(real_t    , d)
axpy_macro(real4_t   , s)
axpy_macro(complex_t , z)
axpy_macro(complex8_t, c)
#undef axpy_macro
/*-------------------------------------------------*/
#define real_ger_macro(typein, prefix, suffix) \
void ger##suffix(int_t m, int_t n, typein alpha, \
		const typein *x, int_t incx, \
		const typein *y, int_t incy, \
		typein *a, int_t lda) \
{ \
	blas_func_name(prefix##ger)(&m, &n, &alpha, x, &incx, y, &incy, a, &lda); \
}
real_ger_macro(real_t , d,  )
real_ger_macro(real4_t, s,  )
real_ger_macro(real_t , d, c)
real_ger_macro(real4_t, s, c)
#undef real_ger_macro
/*-------------------------------------------------*/
#define complex_ger_macro(typein, prefix, suffix, blas_suffix) \
void ger##suffix(int_t m, int_t n, typein alpha, \
    const typein *x, int_t incx, \
    const typein *y, int_t incy, \
    typein *a, int_t lda) \
{ \
	blas_func_name(prefix##ger##blas_suffix)(&m, &n, &alpha, x, &incx, y, &incy, a, &lda); \
}
complex_ger_macro(complex_t , z,  , u)
complex_ger_macro(complex8_t, c,  , u)
complex_ger_macro(complex_t , z, c, c)
complex_ger_macro(complex8_t, c, c, c)
#undef complex_ger_macro
/*-------------------------------------------------*/
#define syr_macro(typein, prefix) \
void syr(char uplo, int_t n, typein alpha, \
		const typein *x, int_t incx, \
		typein *a, int_t lda) \
{ \
	blas_func_name(prefix##syr)(&uplo, &n, &alpha, x, &incx, a, &lda); \
}
syr_macro(real_t    , d)
syr_macro(real4_t   , s)
syr_macro(complex_t , z)
syr_macro(complex8_t, c)
#undef syr_macro
/*-------------------------------------------------*/
#define her_macro(typein, prefix) \
void her(char uplo, int_t n, TypeTraits<typein>::real_type alpha, \
		const typein *x, int_t incx, \
		typein *a, int_t lda) \
{ \
	blas_func_name(prefix##syr)(&uplo, &n, &alpha, x, &incx, a, &lda); \
}
her_macro(real_t , d)
her_macro(real4_t, s)
#undef her_macro
/*-------------------------------------------------*/
#define her_macro(typein, prefix) \
void her(char uplo, int_t n, TypeTraits<typein>::real_type alpha, \
		const typein *x, int_t incx, \
		typein *a, int_t lda) \
{ \
	blas_func_name(prefix##her)(&uplo, &n, &alpha, x, &incx, a, &lda); \
}
her_macro(complex_t , z)
her_macro(complex8_t, c)
#undef her_macro
/*-------------------------------------------------*/
#define gemv_macro(typein, prefix) \
void gemv(char trans, int_t m, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##gemv)(&trans, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
gemv_macro(real_t    , d)
gemv_macro(real4_t   , s)
gemv_macro(complex_t , z)
gemv_macro(complex8_t, c)
#undef gemv_macro
/*-------------------------------------------------*/
#define symv_macro(typein, prefix) \
void symv(char uplo, int_t n, typein alpha, const typein *a, int_t lda, \
		const typein *x, int_t incx, typein beta, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##symv)(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
symv_macro(real_t    , d)
symv_macro(real4_t   , s)
symv_macro(complex_t , z)
symv_macro(complex8_t, c)
#undef symv_macro
/*-------------------------------------------------*/
#define hemv_macro(typein, prefix) \
void hemv(char uplo, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy) \
{ \
	blas_func_name(prefix##hemv)(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
hemv_macro(complex_t , z)
hemv_macro(complex8_t, c)
#undef hemv_macro
/*-------------------------------------------------*/
#define trmv_macro(typein, prefix) \
void trmv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx) \
{ \
	blas_func_name(prefix##trmv)(&uplo, &transa, &diag, &n, a, &lda, b, &incx); \
}
trmv_macro(real_t    , d)
trmv_macro(real4_t   , s)
trmv_macro(complex_t , z)
trmv_macro(complex8_t, c)
#undef trmv_macro
/*-------------------------------------------------*/
#define trsv_macro(typein, prefix) \
void trsv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx) \
{ \
	blas_func_name(prefix##trsv)(&uplo, &transa, &diag, &n, a, &lda, b, &incx); \
}
trsv_macro(real_t    , d)
trsv_macro(real4_t   , s)
trsv_macro(complex_t , z)
trsv_macro(complex8_t, c)
#undef trsv_macro
/*-------------------------------------------------*/
#define gemm_macro(typein, prefix) \
void gemm(char transa, char transb, int_t m, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	blas_func_name(prefix##gemm)(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
gemm_macro(real_t    , d)
gemm_macro(real4_t   , s)
gemm_macro(complex_t , z)
gemm_macro(complex8_t, c)
#undef gemm_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
static void gemmt_recursive(char uplo, char transa, char transb, int_t n, int_t k,
		T_Scalar alpha, const T_Scalar *a, int_t lda, const T_Scalar *b, int_t ldb,
		T_Scalar beta, T_Scalar *c, int_t ldc)
{
	constexpr int_t gemmtRecLimit = 64;

	if(n < gemmtRecLimit) {

		for(int_t j = 0; j < n; j++) {

			int_t incb = (transb == 'N' ? 1 : ldb);
			const T_Scalar *bj = (transb == 'N' ? bulk::dns::ptrmv(ldb,b,0,j) : bulk::dns::ptrmv(ldb,b,j,0));

			if(uplo == 'L') {

				const T_Scalar *al = (transa == 'N' ? bulk::dns::ptrmv(lda,a,j,0) : bulk::dns::ptrmv(lda,a,0,j));

				int_t ma = (transa == 'N' ? n-j : k  );
				int_t na = (transa == 'N' ? k   : n-j);
				int_t incc = 1;
				T_Scalar *cj = bulk::dns::ptrmv(ldc,c,j,j);
				gemv(transa, ma, na, alpha, al, lda, bj, incb, beta, cj, incc);

			} else if(uplo == 'U') {

				const T_Scalar *au = a;

				int_t ma = (transa == 'N' ? j+1 : k  );
				int_t na = (transa == 'N' ? k   : j+1);
				int_t incc = 1;
				T_Scalar *cj = bulk::dns::ptrmv(ldc,c,0,j);
				gemv(transa, ma, na, alpha, au, lda, bj, incb, beta, cj, incc);

			} // U/L

		} // j

	} else {

		int_t n1 = n/2;
		int_t n2 = n - n1;

		const T_Scalar *a1 = a;
		const T_Scalar *a2 = (transa == 'N' ? bulk::dns::ptrmv(lda,a,n1,0) : bulk::dns::ptrmv(lda,a,0,n1));

		const T_Scalar *b1 = b;
		const T_Scalar *b2 = (transb == 'N' ? bulk::dns::ptrmv(ldb,b,0,n1) : bulk::dns::ptrmv(ldb,b,n1,0));

		T_Scalar *c11 = c;
		T_Scalar *c22 = bulk::dns::ptrmv(ldc,c,n1,n1);

		gemmt_recursive(uplo, transa, transb, n1, k, alpha, a1, lda, b1, ldb, beta, c11, ldc);
		gemmt_recursive(uplo, transa, transb, n2, k, alpha, a2, lda, b2, ldb, beta, c22, ldc);

		if(uplo == 'L') {

			T_Scalar *c21 = bulk::dns::ptrmv(ldc,c,n1,0);
			gemm(transa, transb, n2, n1, k, alpha, a2, lda, b1, ldb, beta, c21, ldc);

		} else if(uplo == 'U') {

			T_Scalar *c12 = bulk::dns::ptrmv(ldc,c,0,n1);
			gemm(transa, transb, n1, n2, k, alpha, a1, lda, b2, ldb, beta, c12, ldc);

		} // U/L

	} // n
}
/*-------------------------------------------------*/
#if defined(CLA3P_INTEL_MKL)
#define gemmt_macro(typein, prefix) \
void gemmt(char uplo, char transa, char transb, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	blas_func_name(prefix##gemmt)(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
#else
#define gemmt_macro(typein, prefix) \
void gemmt(char uplo, char transa, char transb, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	gemmt_recursive<typein>(uplo, transa, transb, n, k, alpha, a, lda, b, ldb, beta, c, ldc); \
}
#endif
gemmt_macro(real_t    , d)
gemmt_macro(real4_t   , s)
gemmt_macro(complex_t , z)
gemmt_macro(complex8_t, c)
#undef gemmt_macro
/*-------------------------------------------------*/
#define symm_macro(typein, prefix) \
void symm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	blas_func_name(prefix##symm)(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
symm_macro(real_t    , d)
symm_macro(real4_t   , s)
symm_macro(complex_t , z)
symm_macro(complex8_t, c)
#undef symm_macro
/*-------------------------------------------------*/
#define hemm_macro(typein, prefix) \
void hemm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	blas_func_name(prefix##hemm)(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
hemm_macro(complex_t , z)
hemm_macro(complex8_t, c)
#undef hemm_macro
/*-------------------------------------------------*/
#define trmm_macro(typein, prefix) \
void trmm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb) \
{ \
	blas_func_name(prefix##trmm)(&side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b, &ldb); \
}
trmm_macro(real_t    , d)
trmm_macro(real4_t   , s)
trmm_macro(complex_t , z)
trmm_macro(complex8_t, c)
#undef trmm_macro
/*-------------------------------------------------*/
#define trsm_macro(typein, prefix) \
void trsm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb) \
{ \
	blas_func_name(prefix##trsm)(&side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b, &ldb); \
}
trsm_macro(real_t    , d)
trsm_macro(real4_t   , s)
trsm_macro(complex_t , z)
trsm_macro(complex8_t, c)
#undef trsm_macro
/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/
#undef blas_func_name
/*-------------------------------------------------*/
