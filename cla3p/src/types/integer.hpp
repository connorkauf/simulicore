#ifndef CLA3P_INTEGER_HPP_
#define CLA3P_INTEGER_HPP_

/** 
 * @file
 * Integer configuration
 */

#include <string>

#include "../types/basic_traits.hpp"

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

template<> class BasicTypeTraits<int_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
};

template<> class BasicTypeTraits<uint_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_INTEGER_HPP_
