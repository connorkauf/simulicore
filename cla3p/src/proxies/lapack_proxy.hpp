#ifndef CLA3P_LAPACK_PROXY_HPP_
#define CLA3P_LAPACK_PROXY_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/

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

// TODO: ?lantr ?larnv

/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_PROXY_HPP_
