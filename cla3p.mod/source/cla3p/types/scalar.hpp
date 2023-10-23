#ifndef CLA3P_SCALAR_HPP_
#define CLA3P_SCALAR_HPP_

/** 
 * @file
 * Scalar configuration
 */

#include <cstddef>
#include <complex>
#include <string>

#include "cla3p/types/basic_traits.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_datatypes
 * @brief Single precision real.
 */
using real4_t = float;

/**
 * @ingroup module_index_datatypes
 * @brief Double precision real.
 */
using real_t = double;

/**
 * @ingroup module_index_datatypes
 * @brief Single precision complex.
 */
using complex8_t = std::complex<real4_t>;

/**
 * @ingroup module_index_datatypes
 * @brief Double precision complex.
 */
using complex_t = std::complex<real_t>;

/*-------------------------------------------------*/

template<> class BasicTypeTraits<real_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
    using real_type = real_t;
};

template<> class BasicTypeTraits<real4_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
    using real_type = real4_t;
};

template<> class BasicTypeTraits<complex_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
    using real_type = complex_t::value_type;
};

template<> class BasicTypeTraits<complex8_t> {
  public:
    static std::string type_name();
    static std::string prec_name();
    using real_type = complex8_t::value_type;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SCALAR_HPP_
