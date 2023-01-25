#ifndef CLA3P_LAPACK_PROXY_HPP_
#define CLA3P_LAPACK_PROXY_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace lapack {
/*-------------------------------------------------*/

#define lange_macro(typeout, typein) \
typeout lange(char norm, int_t m, int_t n, const typein *a, int_t lda);
lange_macro(real_t , real_t    )
lange_macro(real4_t, real4_t   )
lange_macro(real_t , complex_t )
lange_macro(real4_t, complex8_t)
#undef lange_macro

#define lansy_macro(typeout, typein) \
typeout lansy(char norm, char uplo, int_t n, const typein *a, int_t lda);
lansy_macro(real_t , real_t    )
lansy_macro(real4_t, real4_t   )
lansy_macro(real_t , complex_t )
lansy_macro(real4_t, complex8_t)
#undef lansy_macro

#define lanhe_macro(typeout, typein) \
typeout lanhe(char norm, char uplo, int_t n, const typein *a, int_t lda);
lanhe_macro(real_t , real_t    ) // same as lansy
lanhe_macro(real4_t, real4_t   ) // same as lansy
lanhe_macro(real_t , complex_t )
lanhe_macro(real4_t, complex8_t)
#undef lanhe_macro

/*-------------------------------------------------*/
} // namespace lapack
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_PROXY_HPP_
