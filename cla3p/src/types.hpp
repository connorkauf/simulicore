/** @file types.hpp
 *
 * Basic datatypes and enumerations declaration
 */

#include <cstdint>

#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

namespace cla3p {

#if defined (CLA3P_I64)
typedef std::int64_t int_t;
typedef std::uint64_t uint_t;
#else
typedef std::int32_t int_t;
typedef std::uint32_t uint_t;
#endif

typedef double real_t;

} // namespace cla3p

#endif // CLA3P_TYPES_HPP_
