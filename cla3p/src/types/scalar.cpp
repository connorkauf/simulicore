// this file inc
#include "scalar.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real_t>::typeStr() { return stringReal(); }
const std::string& BasicTypeTraits<real_t>::precStr() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real4_t>::typeStr() { return stringReal(); }
const std::string& BasicTypeTraits<real4_t>::precStr() { return stringSingle(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex_t>::typeStr() { return stringComplex(); }
const std::string& BasicTypeTraits<complex_t>::precStr() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex8_t>::typeStr() { return stringComplex(); }
const std::string& BasicTypeTraits<complex8_t>::precStr() { return stringSingle(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

