#ifndef CLA3P_SCALAR_INTERNAL_HPP_
#define CLA3P_SCALAR_INTERNAL_HPP_

#include "cla3p/types/scalar.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

inline real_t conj(const real_t& d) { return d; }
inline real4_t conj(const real4_t& s) { return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }

inline real_t  getRe(const real_t& d) { return d; }
inline real4_t getRe(const real4_t& f) { return f; }
inline real_t  getRe(const complex_t& z) { return z.real(); }
inline real4_t getRe(const complex8_t& c) { return c.real(); }

inline real_t  getIm(const real_t&) { return 0; }
inline real4_t getIm(const real4_t&) { return 0; }
inline real_t  getIm(const complex_t& z) { return z.imag(); }
inline real4_t getIm(const complex8_t& c) { return c.imag(); }

inline void setim(real_t&, real_t) { }
inline void setim(real4_t&, real4_t) { }
inline void setim(complex_t& z, real_t d) { z.imag(d); }
inline void setim(complex8_t& c, real4_t s) { c.imag(s); }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SCALAR_INTERNAL_HPP_
