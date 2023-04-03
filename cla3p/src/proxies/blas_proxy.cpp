// this file inc
#include "blas_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p
#include "../support/error.hpp"
#include "../support/error_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/
#define copy_macro(typeout, typein, prefix) \
typeout copy(int_t n, const typein *x, int_t incx, typein *y, int_t incy) \
{ \
	prefix##copy(&n, x, &incx, y, &incy); \
}
copy_macro(void, real_t    , d)
copy_macro(void, real4_t   , s)
copy_macro(void, complex_t , z)
copy_macro(void, complex8_t, c)
#undef copy_macro
/*-------------------------------------------------*/
#define swap_macro(typeout, typein, prefix) \
typeout swap(int_t n, typein *x, int_t incx, typein *y, int_t incy) \
{ \
	prefix##swap(&n, x, &incx, y, &incy); \
}
swap_macro(void, real_t    , d)
swap_macro(void, real4_t   , s)
swap_macro(void, complex_t , z)
swap_macro(void, complex8_t, c)
#undef swap_macro
/*-------------------------------------------------*/
#define scal_macro(typeout, atypein, typein, prefix) \
typeout scal(int_t n, atypein alpha, typein *x, int_t incx) \
{ \
	prefix##scal(&n, &alpha, x, &incx); \
}
scal_macro(void, real_t    , real_t    , d );
scal_macro(void, real4_t   , real4_t   , s );
scal_macro(void, real_t    , complex_t , zd);
scal_macro(void, real4_t   , complex8_t, cs);
scal_macro(void, complex_t , complex_t , z );
scal_macro(void, complex8_t, complex8_t, c );
#undef scal_macro
/*-------------------------------------------------*/
#define nrm2_macro(typeout, typein, rprefix, cprefix) \
typeout nrm2(int_t n, const typein *x, int_t incx) \
{ \
	return rprefix##cprefix##nrm2(&n, x, &incx); \
}
nrm2_macro(real_t , real_t    ,  , d)
nrm2_macro(real4_t, real4_t   ,  , s)
nrm2_macro(real_t , complex_t , d, z)
nrm2_macro(real4_t, complex8_t, s, c)
#undef nrm2_macro
/*-------------------------------------------------*/
#define dot_macro(typeio, prefix) \
typeio dot(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy) \
{ \
	return prefix##dot(&n, x, &incx, y, &incy); \
}
dot_macro(real_t , d)
dot_macro(real4_t, s)
#undef dot_macro
/*-------------------------------------------------*/
#define dotu_macro(typeio, prefix) \
typeio dotu(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy) \
{ \
	typeio res;  \
	prefix##dotu(&res, &n, x, &incx, y, &incy); \
	return res; \
}
dotu_macro(complex_t , z)
dotu_macro(complex8_t, c)
#undef dotu_macro
/*-------------------------------------------------*/
#define dotc_macro(typeio, prefix) \
typeio dotc(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy) \
{ \
	typeio res;  \
	prefix##dotc(&res, &n, x, &incx, y, &incy); \
	return res; \
}
dotc_macro(complex_t , z)
dotc_macro(complex8_t, c)
#undef dotc_macro
/*-------------------------------------------------*/
#define axpy_macro(typeout, typein, prefix) \
typeout axpy(int_t n, typein alpha, const typein *x, int_t incx, typein *y, int_t incy) \
{ \
	prefix##axpy(&n, &alpha, x, &incx, y, &incy); \
}
axpy_macro(void, real_t    , d)
axpy_macro(void, real4_t   , s)
axpy_macro(void, complex_t , z)
axpy_macro(void, complex8_t, c)
#undef axpy_macro
/*-------------------------------------------------*/
#define gemv_macro(typeout, typein, prefix) \
typeout gemv(char trans, int_t m, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy) \
{ \
	prefix##gemv(&trans, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
gemv_macro(void, real_t    , d)
gemv_macro(void, real4_t   , s)
gemv_macro(void, complex_t , z)
gemv_macro(void, complex8_t, c)
#undef gemv_macro
/*-------------------------------------------------*/
#define symv_macro(typeout, typein, prefix) \
typeout symv(char uplo, int_t n, typein alpha, const typein *a, int_t lda, \
		const typein *x, int_t incx, typein beta, typein *y, int_t incy) \
{ \
	prefix##symv(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
symv_macro(void, real_t    , d)
symv_macro(void, real4_t   , s)
symv_macro(void, complex_t , z)
symv_macro(void, complex8_t, c)
#undef symv_macro
/*-------------------------------------------------*/
#define hemv_macro(typeout, typein, prefix) \
typeout hemv(char uplo, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy) \
{ \
	prefix##hemv(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
hemv_macro(void, complex_t , z)
hemv_macro(void, complex8_t, c)
#undef hemv_macro
/*-------------------------------------------------*/
#define trmv_macro(typeout, typein, prefix) \
typeout trmv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx) \
{ \
	prefix##trmv(&uplo, &transa, &diag, &n, a, &lda, b, &incx); \
}
trmv_macro(void, real_t    , d)
trmv_macro(void, real4_t   , s)
trmv_macro(void, complex_t , z)
trmv_macro(void, complex8_t, c)
#undef trmv_macro
/*-------------------------------------------------*/
#define ger_macro(typeout, typein, prefix) \
typeout ger(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda) \
{ \
	prefix##ger(&m, &n, &alpha, x, &incx, y, &incy, a, &lda); \
}
ger_macro(void, real_t , d)
ger_macro(void, real4_t, s)
#undef ger_macro
/*-------------------------------------------------*/
#define geru_macro(typeout, typein, prefix) \
typeout geru(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda) \
{ \
	prefix##geru(&m, &n, &alpha, x, &incx, y, &incy, a, &lda); \
}
geru_macro(void, complex_t , z)
geru_macro(void, complex8_t, c)
#undef geru_macro
/*-------------------------------------------------*/
#define gerc_macro(typeout, typein, prefix) \
typeout gerc(int_t m, int_t n, typein alpha, const typein *x, int_t incx, \
		const typein *y, int_t incy, typein *a, int_t lda) \
{ \
	prefix##gerc(&m, &n, &alpha, x, &incx, y, &incy, a, &lda); \
}
gerc_macro(void, complex_t , z)
gerc_macro(void, complex8_t, c)
#undef geru_macro
/*-------------------------------------------------*/
#define gemm_macro(typeout, typein, prefix) \
typeout gemm(char transa, char transb, int_t m, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	prefix##gemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
gemm_macro(void, real_t    , d)
gemm_macro(void, real4_t   , s)
gemm_macro(void, complex_t , z)
gemm_macro(void, complex8_t, c)
#undef gemm_macro
/*-------------------------------------------------*/
#define gemmt_macro(typeout, typein, prefix) \
typeout gemmt(char uplo, char transa, char transb, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	prefix##gemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
gemmt_macro(void, real_t    , d)
gemmt_macro(void, real4_t   , s)
gemmt_macro(void, complex_t , z)
gemmt_macro(void, complex8_t, c)
#undef gemmt_macro
/*-------------------------------------------------*/
#define symm_macro(typeout, typein, prefix) \
typeout symm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	prefix##symm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
symm_macro(void, real_t    , d)
symm_macro(void, real4_t   , s)
symm_macro(void, complex_t , z)
symm_macro(void, complex8_t, c)
#undef symm_macro
/*-------------------------------------------------*/
#define hemm_macro(typeout, typein, prefix) \
typeout hemm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	prefix##hemm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
hemm_macro(void, complex_t , z)
hemm_macro(void, complex8_t, c)
#undef hemm_macro
/*-------------------------------------------------*/
#define trmm_macro(typeout, typein, prefix) \
typeout trmm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb) \
{ \
	prefix##trmm(&side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b, &ldb); \
}
trmm_macro(void, real_t    , d)
trmm_macro(void, real4_t   , s)
trmm_macro(void, complex_t , z)
trmm_macro(void, complex8_t, c)
#undef trmm_macro
/*-------------------------------------------------*/
#define trsm_macro(typeout, typein, prefix) \
typeout trsm(char side, char uplo, char transa, char diag, \
		int_t m, int_t n, typein alpha, const typein *a, int_t lda, \
		typein *b, int_t ldb) \
{ \
	prefix##trsm(&side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b, &ldb); \
}
trsm_macro(void, real_t    , d)
trsm_macro(void, real4_t   , s)
trsm_macro(void, complex_t , z)
trsm_macro(void, complex8_t, c)
#undef trsm_macro
/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/
