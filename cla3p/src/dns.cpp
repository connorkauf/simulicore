// this file inc
#include "dns.hpp"

// system
#include <cstring>
#include <algorithm>

// 3rd

// cla3p
#include "imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template <class T>
T* new_tmpl(uint_t m, uint_t n, uint_t lda, bool zero)
{
	T *ret = static_cast<T*>(i_malloc(lda * n, sizeof(T)));

	if(zero) {
		setzero(m, n, ret, lda);
	} // zero

	return ret;
}
/*-------------------------------------------------*/
real_t* rnew(uint_t m, uint_t n, uint_t lda, bool zero)
{
	return new_tmpl<real_t>(m, n, lda, zero);
}
/*-------------------------------------------------*/
complex_t* cnew(uint_t m, uint_t n, uint_t lda, bool zero)
{
	return new_tmpl<complex_t>(m, n, lda, zero);
}
/*-------------------------------------------------*/
template <class T>
static void setzero_tmpl(uint_t m, uint_t n, T *a, uint_t lda)
{
	if(m == lda) {
		std::memset(a, 0, m * n * sizeof(T));
	} else {
		for(uint_t j = 0; j < n; j++) {
			std::memset(entry_ptr(lda,a,0,j), 0, m * sizeof(T));
		} // j
	} // m = lda
}
/*-------------------------------------------------*/
void setzero(uint_t m, uint_t n, real_t *a, uint_t lda)
{
	setzero_tmpl(m, n, a, lda);
}
/*-------------------------------------------------*/
void setzero(uint_t m, uint_t n, complex_t *a, uint_t lda)
{
	setzero_tmpl(m, n, a, lda);
}
/*-------------------------------------------------*/
template <class T>
static void fill_tmpl(uint_t m, uint_t n, T *a, uint_t lda, T val)
{
	// TODO: if !val call setzero() fix when operators for complex are done
	
	if(m == lda) {
		std::fill_n(a, m * n, val);
	} else {
		for(uint_t j = 0; j < n; j++) {
			std::fill_n(entry_ptr(lda,a,0,j), m, val);
		} // j
	} // m = lda
}
/*-------------------------------------------------*/
void fill(uint_t m, uint_t n, real_t *a, uint_t lda, real_t val)
{
	fill_tmpl(m, n, a, lda, val);
}
/*-------------------------------------------------*/
void fill(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t val)
{
	fill_tmpl(m, n, a, lda, val);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
