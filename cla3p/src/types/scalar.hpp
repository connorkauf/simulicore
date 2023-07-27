#ifndef CLA3P_SCALAR_HPP_
#define CLA3P_SCALAR_HPP_

/** 
 * @file
 * Scalar configuration
 */

#include <cstddef>
#include <complex>
#include <string>

#include "../types/basic_traits.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes 
 * @brief Single precision real.
 */
using real4_t = float;

/**
 * @ingroup basic_datatypes 
 * @brief Double precision real.
 */
using real_t = double;

/**
 * @ingroup basic_datatypes 
 * @brief Single precision complex.
 */
using complex8_t = std::complex<real4_t>;

/**
 * @ingroup basic_datatypes 
 * @brief Double precision complex.
 */
using complex_t = std::complex<real_t>;

/**
 * @ingroup basic_datatypes 
 * @brief Standard indexing.
 */
using bulk_t = std::size_t;

/*-------------------------------------------------*/

inline real_t conj(const real_t& d) { return d; }
inline real4_t conj(const real4_t& s) { return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }

inline real_t  getRe(const real_t& d) { return d; }
inline real4_t getRe(const real4_t& f) { return f; }
inline real_t  getRe(const complex_t& z) { return z.real(); }
inline real4_t getRe(const complex8_t& c) { return c.real(); }

inline void setim(real_t&, real_t) { }
inline void setim(real4_t&, real4_t) { }
inline void setim(complex_t& z, real_t d) { z.imag(d); }
inline void setim(complex8_t& c, real4_t s) { c.imag(s); }

/*-------------------------------------------------*/

template<> class BasicTypeTraits<real_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
    using real_type = real_t;
};

template<> class BasicTypeTraits<real4_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
    using real_type = real4_t;
};

template<> class BasicTypeTraits<complex_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
    using real_type = complex_t::value_type;
};

template<> class BasicTypeTraits<complex8_t> {
  public:
    static const std::string& type_name();
    static const std::string& prec_name();
    using real_type = complex8_t::value_type;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SCALAR_HPP_
