// this file inc
#include "cla3p/types/integer.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string BasicTypeTraits<int_t>::type_name()
{
  return msg::Integer();
}
/*-------------------------------------------------*/
std::string BasicTypeTraits<int_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<uint_t>::type_name()
{
  return msg::UnsignedInteger();
}
/*-------------------------------------------------*/
std::string BasicTypeTraits<uint_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
