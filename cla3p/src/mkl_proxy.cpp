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
	MKLVersion ver;
	const nint_t len = 256;
	char buffer[len];
	mkl_get_version_string(buffer, len);
	return buffer;
}
/*-------------------------------------------------*/
void omatcopy(char ordering, char trans, size_t rows, size_t cols,
    real_t alpha, const real_t *a, size_t lda, real_t *b, size_t ldb)
{
	mkl_domatcopy(ordering, trans, rows, cols, alpha, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void omatcopy(char ordering, char trans, size_t rows, size_t cols,
		complex_t alpha, const complex_t *a, size_t lda, complex_t *b, size_t ldb)
{
	mkl_zomatcopy(ordering, trans, rows, cols, alpha, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void imatcopy(char ordering, char trans, size_t rows, size_t cols,
    real_t alpha, real_t *a, size_t lda, size_t ldb)
{
	mkl_dimatcopy(ordering, trans, rows, cols, alpha, a, lda, ldb);
}
/*-------------------------------------------------*/
void imatcopy(char ordering, char trans, size_t rows, size_t cols,
    complex_t alpha, complex_t *a, size_t lda, size_t ldb)
{
	mkl_zimatcopy(ordering, trans, rows, cols, alpha, a, lda, ldb);
}
/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/
