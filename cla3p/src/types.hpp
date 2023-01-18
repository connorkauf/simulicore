#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** @file types.hpp
 * Basic datatypes and enumerations declaration
 */

#include <cstddef>
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

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_TYPES_HPP_
