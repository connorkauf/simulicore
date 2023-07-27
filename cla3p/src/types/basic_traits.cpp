// this file inc
#include "basic_traits.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static const std::string traitNameInteger = "Integer";
static const std::string traitNameUnsignedInteger = "Unsigned Integer";
static const std::string traitNameReal = "Real";
static const std::string traitNameComplex = "Complex";
static const std::string traitNameSingle = "Single (32bit)";
static const std::string traitNameDouble = "Double (64bit)";
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::typeStr()
{ 
	return traitNameInteger; 
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<int_t>::precStr() 
{ 
#if defined (CLA3P_I64)
	return traitNameDouble; 
#else
	return traitNameSingle; 
#endif
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<uint_t>::typeStr()
{ 
	return traitNameUnsignedInteger; 
}
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<uint_t>::precStr()
{ 
#if defined (CLA3P_I64)
	return traitNameDouble; 
#else
	return traitNameSingle; 
#endif
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real_t>::typeStr() { return traitNameReal; }
const std::string& BasicTypeTraits<real_t>::precStr() { return traitNameDouble; }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<real4_t>::typeStr() { return traitNameReal; }
const std::string& BasicTypeTraits<real4_t>::precStr() { return traitNameSingle; }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex_t>::typeStr() { return traitNameComplex; }
const std::string& BasicTypeTraits<complex_t>::precStr() { return traitNameDouble; }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
const std::string& BasicTypeTraits<complex8_t>::typeStr() { return traitNameComplex; }
const std::string& BasicTypeTraits<complex8_t>::precStr() { return traitNameSingle; }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
