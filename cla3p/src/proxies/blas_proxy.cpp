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
	return prefix##copy(&n, x, &incx, y, &incy); \
}
copy_macro(void, real_t    , d)
copy_macro(void, real4_t   , s)
copy_macro(void, complex_t , z)
copy_macro(void, complex8_t, c)
#undef copy_macro
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
	return prefix##axpy(&n, &alpha, x, &incx, y, &incy); \
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
	return prefix##gemv(&trans, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
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
	return prefix##symv(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
symv_macro(void, real_t    , d)
symv_macro(void, real4_t   , s)
symv_macro(void, complex_t , z)
symv_macro(void, complex8_t, c)
#undef symv_macro
/*-------------------------------------------------*/
void hemv(char, int_t, real_t , const real_t *, int_t, const real_t *, int_t, real_t , real_t *, int_t) { throw Exception(msg::op_not_allowed()); }
void hemv(char, int_t, real4_t, const real4_t*, int_t, const real4_t*, int_t, real4_t, real4_t*, int_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
#define hemv_macro(typeout, typein, prefix) \
typeout hemv(char uplo, int_t n, typein alpha, \
		const typein *a, int_t lda, const typein *x, int_t incx, \
		typein beta, typein *y, int_t incy) \
{ \
	return prefix##hemv(&uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy); \
}
hemv_macro(void, complex_t , z)
hemv_macro(void, complex8_t, c)
#undef hemv_macro
/*-------------------------------------------------*/
#define trmv_macro(typeout, typein, prefix) \
typeout trmv(char uplo, char transa, char diag, int_t n, \
		const typein *a, int_t lda, typein *b, int_t incx) \
{ \
	return prefix##trmv(&uplo, &transa, &diag, &n, a, &lda, b, &incx); \
}
trmv_macro(void, real_t    , d)
trmv_macro(void, real4_t   , s)
trmv_macro(void, complex_t , z)
trmv_macro(void, complex8_t, c)
#undef trmv_macro
/*-------------------------------------------------*/
#define gemm_macro(typeout, typein, prefix) \
typeout gemm(char transa, char transb, int_t m, int_t n, int_t k, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	return prefix##gemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
gemm_macro(void, real_t    , d)
gemm_macro(void, real4_t   , s)
gemm_macro(void, complex_t , z)
gemm_macro(void, complex8_t, c)
#undef gemm_macro
/*-------------------------------------------------*/
#define symm_macro(typeout, typein, prefix) \
typeout symm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	return prefix##symm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
}
symm_macro(void, real_t    , d)
symm_macro(void, real4_t   , s)
symm_macro(void, complex_t , z)
symm_macro(void, complex8_t, c)
#undef symm_macro
/*-------------------------------------------------*/
void hemm(char, char, int_t, int_t, real_t , const real_t *, int_t, const real_t *, int_t, real_t , real_t *, int_t) { throw Exception(msg::op_not_allowed()); }
void hemm(char, char, int_t, int_t, real4_t, const real4_t*, int_t, const real4_t*, int_t, real4_t, real4_t*, int_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
#define hemm_macro(typeout, typein, prefix) \
typeout hemm(char side, char uplo, int_t m, int_t n, \
		typein alpha, const typein *a, int_t lda, const typein *b, int_t ldb, \
		typein beta, typein *c, int_t ldc) \
{ \
	return prefix##hemm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); \
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
	return prefix##trmm(&side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b, &ldb); \
}
trmm_macro(void, real_t    , d)
trmm_macro(void, real4_t   , s)
trmm_macro(void, complex_t , z)
trmm_macro(void, complex8_t, c)
#undef trmm_macro
/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/
