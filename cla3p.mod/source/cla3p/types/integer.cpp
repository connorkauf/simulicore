// this file inc
#include "cla3p/types/integer.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::type_name()
{
  return stringInteger();
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::prec_name()
{
#if defined (CLA3P_I64)
  return stringDouble();
#else
  return stringSingle();
#endif
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<uint_t>::type_name()
{
  return stringUnsignedInteger();
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<uint_t>::prec_name()
{
#if defined (CLA3P_I64)
  return stringDouble();
#else
  return stringSingle();
#endif
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
