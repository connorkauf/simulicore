// this file inc
#include "literals.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static const std::string literal_stringInteger = "Integer";
static const std::string literal_stringUnsignedInteger = "Unsigned Integer";
static const std::string literal_stringReal = "Real";
static const std::string literal_stringComplex = "Complex";
static const std::string literal_stringSingle = "Single (32bit)";
static const std::string literal_stringDouble = "Double (64bit)";
/*-------------------------------------------------*/
const std::string& stringInteger() { return literal_stringInteger; }
const std::string& stringUnsignedInteger() { return literal_stringUnsignedInteger; }
const std::string& stringReal() { return literal_stringReal; }
const std::string& stringComplex() { return literal_stringComplex; }
const std::string& stringSingle() { return literal_stringSingle; }
const std::string& stringDouble() { return literal_stringSingle; }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
