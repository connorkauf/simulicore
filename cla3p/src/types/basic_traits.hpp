#ifndef CLA3P_BASIC_TYPE_TRAITS_HPP_
#define CLA3P_BASIC_TYPE_TRAITS_HPP_

#include <string>

#include "integer.hpp"
#include "scalar.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T>
class BasicTypeTraits {
};

template<> class BasicTypeTraits<int_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
};

template<> class BasicTypeTraits<uint_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
};

template<> class BasicTypeTraits<real_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
    using real_type = real_t;
};

template<> class BasicTypeTraits<real4_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
    using real_type = real4_t;
};

template<> class BasicTypeTraits<complex_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
    using real_type = complex_t::value_type;
};

template<> class BasicTypeTraits<complex8_t> {
  public:
    static const std::string& typeStr();
    static const std::string& precStr();
    using real_type = complex8_t::value_type;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BASIC_TYPE_TRAITS_HPP_
