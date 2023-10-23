#ifndef CLA3P_INTEGER_HPP_
#define CLA3P_INTEGER_HPP_

/** 
 * @file
 * Integer configuration
 */

#include <string>

#include "cla3p/types/basic_traits.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
using int_t = long long int;
using uint_t = unsigned long long int;
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
using int_t = int;
using uint_t = unsigned int;
#endif

using nint_t = int;

/**
 * @ingroup module_index_datatypes
 * @brief Standard indexing.
 */
using bulk_t = std::size_t;

/*-------------------------------------------------*/

template<> class BasicTypeTraits<int_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
};

template<> class BasicTypeTraits<uint_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_INTEGER_HPP_
