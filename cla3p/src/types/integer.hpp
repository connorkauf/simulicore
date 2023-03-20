#ifndef CLA3P_INTEGER_HPP_
#define CLA3P_INTEGER_HPP_

/** 
 * @file
 * Integer configuration
 */

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
using  int_t =          long long int;
using uint_t = unsigned long long int;
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
using  int_t =          int;
using uint_t = unsigned int;
#endif

using nint_t = int;

/*-------------------------------------------------*/

inline int_t conj(const int_t& i) { return i; }
inline uint_t conj(const uint_t& u) { return u; }

inline void setim(int_t&, int_t) { }
inline void setim(uint_t&, uint_t) { }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_INTEGER_HPP_
