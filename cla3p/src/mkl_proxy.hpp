#ifndef CLA3P_MKL_PROXY_HPP_
#define CLA3P_MKL_PROXY_HPP_

#include <stddef.h>
#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

std::string version();

#define omatcopy_macro(typeout, typein) \
typeout omatcopy(char ordering, char trans, size_t rows, size_t cols, typein alpha, const typein *a, size_t lda, typein *b, size_t ldb);
omatcopy_macro(void, real_t    )
omatcopy_macro(void, real4_t   )
omatcopy_macro(void, complex_t )
omatcopy_macro(void, complex8_t)
#undef omatcopy_macro

#define imatcopy_macro(typeout, typein) \
typeout imatcopy(char ordering, char trans, size_t rows, size_t cols, typein alpha, typein *a, size_t lda, size_t ldb);
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
