// this file inc
#include "blas_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/
#define nrm2_macro(typeout, typein, prefix_real, prefix_complex) \
typeout nrm2(int_t n, const typein *x, int_t incx) \
{ \
	return prefix_real##prefix_complex##nrm2(&n, x, &incx); \
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
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/
