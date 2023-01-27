#ifndef CLA3P_MKL_PROXY_HPP_
#define CLA3P_MKL_PROXY_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

std::string version();

#define omatcopy_macro(typeout, typein) \
typeout omatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, const typein *a, bulk_t lda, typein *b, bulk_t ldb);
omatcopy_macro(void, real_t    )
omatcopy_macro(void, real4_t   )
omatcopy_macro(void, complex_t )
omatcopy_macro(void, complex8_t)
#undef omatcopy_macro

#define imatcopy_macro(typeout, typein) \
typeout imatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, typein *a, bulk_t lda, bulk_t ldb);
imatcopy_macro(void, real_t    )
imatcopy_macro(void, real4_t   )
imatcopy_macro(void, complex_t )
imatcopy_macro(void, complex8_t)
#undef imatcopy_macro

/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_PROXY_HPP_
