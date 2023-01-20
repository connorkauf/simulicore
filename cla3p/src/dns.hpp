#ifndef CLA3P_DNS_HPP_
#define CLA3P_DNS_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
//#define __dnsentry__(lda, a, i, j) 
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {

template <class T>
inline T& entry(uint_t lda, T *a, uint_t i, uint_t j)
{
	return a[i + j * lda];
}

template <class T>
inline T* entry_ptr(uint_t lda, T *a, uint_t i, uint_t j)
{
	return (a + i + j * lda);
}

real_t* rnew(uint_t m, uint_t n, uint_t lda, bool zero = false);
complex_t* cnew(uint_t m, uint_t n, uint_t lda, bool zero = false);

void setzero(uint_t m, uint_t n, real_t *a, uint_t lda);
void setzero(uint_t m, uint_t n, complex_t *a, uint_t lda);

void fill(uint_t m, uint_t n, real_t *a, uint_t lda, real_t val);
void fill(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t val);

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_HPP_
