// this file inc
#include "cla3p/types/scalar.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string BasicTypeTraits<real_t>::type_name() { return msg::Real(); }
std::string BasicTypeTraits<real_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<real4_t>::type_name() { return msg::Real(); }
std::string BasicTypeTraits<real4_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex_t>::type_name() { return msg::Complex(); }
std::string BasicTypeTraits<complex_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex8_t>::type_name() { return msg::Complex(); }
std::string BasicTypeTraits<complex8_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

