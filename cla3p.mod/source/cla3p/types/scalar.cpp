// this file inc
#include "cla3p/types/scalar.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string BasicTypeTraits<real_t>::type_name() { return stringReal(); }
std::string BasicTypeTraits<real_t>::prec_name() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<real4_t>::type_name() { return stringReal(); }
std::string BasicTypeTraits<real4_t>::prec_name() { return stringSingle(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex_t>::type_name() { return stringComplex(); }
std::string BasicTypeTraits<complex_t>::prec_name() { return stringDouble(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex8_t>::type_name() { return stringComplex(); }
std::string BasicTypeTraits<complex8_t>::prec_name() { return stringSingle(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

