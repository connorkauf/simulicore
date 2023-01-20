#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** @file types.hpp
 * Basic datatypes and enumerations declaration
 */

#include <cstddef>
#include <ostream>
#include "mkl_types.h"

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
#endif

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

typedef int nint_t;
typedef MKL_INT int_t;
typedef MKL_UINT uint_t;
typedef double real_t;
typedef MKL_Complex16 complex_t;
typedef std::size_t bulk_t;

inline complex_t cval(real_t re, real_t im)
{
	return {re, im};
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

std::ostream& operator<<(std::ostream&, const cla3p::complex_t&);

cla3p::complex_t operator+(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator-(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator*(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator/(const cla3p::complex_t&, const cla3p::complex_t&);

/*-------------------------------------------------*/

#endif // CLA3P_TYPES_HPP_
