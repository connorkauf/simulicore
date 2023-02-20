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
