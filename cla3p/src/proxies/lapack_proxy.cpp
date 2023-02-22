// this file inc
#include "lapack_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p
#include "../support/error.hpp"
#include "../support/error_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
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
#define lacp2_macro(typeout, rtypein, ctypein, prefix) \
typeout lacp2(char uplo, int_t m, int_t n, const rtypein *a, int_t lda, ctypein *b, int_t ldb) \
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
real_t  lanhe(char, char, int_t, const real_t *, int_t) { throw Exception(msg::op_not_allowed()); return 0; }
real4_t lanhe(char, char, int_t, const real4_t*, int_t) { throw Exception(msg::op_not_allowed()); return 0; }
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
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/
