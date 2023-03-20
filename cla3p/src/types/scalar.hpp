#ifndef CLA3P_SCALAR_HPP_
#define CLA3P_SCALAR_HPP_

/** 
 * @file
 * Scalar configuration
 */

#include <cstddef>
#include <complex>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes_group 
 * @brief Single precision real.
 */
using real4_t = float;

/**
 * @ingroup basic_datatypes_group 
 * @brief Double precision real.
 */
using real_t = double;

/**
 * @ingroup basic_datatypes_group 
 * @brief Single precision complex.
 */
using complex8_t = std::complex<real4_t>;

/**
 * @ingroup basic_datatypes_group 
 * @brief Double precision complex.
 */
using complex_t = std::complex<real_t>;

/**
 * @ingroup basic_datatypes_group 
 * @brief Standard indexing.
 */
using bulk_t = std::size_t;

/*-------------------------------------------------*/

inline real_t conj(const real_t& d) { return d; }
inline real4_t conj(const real4_t& s) { return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }

inline void setim(real_t&, real_t) { }
inline void setim(real4_t&, real4_t) { }
inline void setim(complex_t& z, real_t d) { z.imag(d); }
inline void setim(complex8_t& c, real4_t s) { c.imag(s); }

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SCALAR_HPP_
