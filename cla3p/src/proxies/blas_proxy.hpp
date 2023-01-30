#ifndef CLA3P_BLAS_PROXY_HPP_
#define CLA3P_BLAS_PROXY_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blas {
/*-------------------------------------------------*/

/*------------------ Level 1 ----------------------*/
#define nrm2_macro(typeout, typein) \
typeout nrm2(int_t n, const typein *x, int_t incx);
nrm2_macro(real_t , real_t    )
nrm2_macro(real4_t, real4_t   )
nrm2_macro(real_t , complex_t )
nrm2_macro(real4_t, complex8_t)
#undef nrm2_macro

#define dot_macro(typeio) \
typeio dot(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy);
dot_macro(real_t )
dot_macro(real4_t)
#undef dot_macro

#define dotu_macro(typeio) \
typeio dotu(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy);
dotu_macro(complex_t )
dotu_macro(complex8_t)
#undef dotu_macro

#define dotc_macro(typeio) \
typeio dotc(int_t n, const typeio *x, int_t incx, const typeio *y, int_t incy);
dotc_macro(complex_t )
dotc_macro(complex8_t)
#undef dotc_macro

/*------------------ Level 2 ----------------------*/

/*------------------ Level 3 ----------------------*/

/*-------------------------------------------------*/
} // namespace blas
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BLAS_PROXY_HPP_
