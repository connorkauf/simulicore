// this file inc
#include "scalar.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real_t>::type_name() { return stringReal(); }
const std::string& BasicTypeTraits<real_t>::prec_name() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real4_t>::type_name() { return stringReal(); }
const std::string& BasicTypeTraits<real4_t>::prec_name() { return stringSingle(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex_t>::type_name() { return stringComplex(); }
const std::string& BasicTypeTraits<complex_t>::prec_name() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex8_t>::type_name() { return stringComplex(); }
const std::string& BasicTypeTraits<complex8_t>::prec_name() { return stringSingle(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

