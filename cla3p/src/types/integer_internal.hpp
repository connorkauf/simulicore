#ifndef CLA3P_INTEGER_INTERNAL_HPP_
#define CLA3P_INTEGER_INTERNAL_HPP_

#include "integer.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

inline int_t conj(const int_t& i) { return i; }
inline uint_t conj(const uint_t& u) { return u; }

inline void setim(int_t&, int_t) { }
inline void setim(uint_t&, uint_t) { }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_INTEGER_INTERNAL_HPP_
