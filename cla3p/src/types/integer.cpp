// this file inc
#include "integer.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::typeStr()
{
  return stringInteger();
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::precStr()
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
const std::string& BasicTypeTraits<uint_t>::typeStr()
{
  return stringUnsignedInteger();
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<uint_t>::precStr()
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
