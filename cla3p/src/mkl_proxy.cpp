// this file inc
#include "mkl_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/
std::string version()
{
	const nint_t len = 256;
	char buffer[len];
	mkl_get_version_string(buffer, len);
	return buffer;
}
/*-------------------------------------------------*/
#define omatcopy_macro(typeout, typein, prefix) \
typeout omatcopy(char ordering, char trans, size_t rows, size_t cols, typein alpha, const typein *a, size_t lda, typein *b, size_t ldb) \
{ \
	mkl_##prefix##omatcopy(ordering, trans, rows, cols, alpha, a, lda, b, ldb); \
}
omatcopy_macro(void, real_t    , d)
omatcopy_macro(void, real4_t   , s)
omatcopy_macro(void, complex_t , z)
omatcopy_macro(void, complex8_t, c)
#undef omatcopy_macro
/*-------------------------------------------------*/
#define imatcopy_macro(typeout, typein, prefix) \
typeout imatcopy(char ordering, char trans, size_t rows, size_t cols, typein alpha, typein *a, size_t lda, size_t ldb) \
{ \
	mkl_##prefix##imatcopy(ordering, trans, rows, cols, alpha, a, lda, ldb); \
}
imatcopy_macro(void, real_t    , d)
imatcopy_macro(void, real4_t   , s)
imatcopy_macro(void, complex_t , z)
imatcopy_macro(void, complex8_t, c)
#undef omatcopy_macro
/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/
