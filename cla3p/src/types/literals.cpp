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
static const std::string literal_stringDense = "Dense";
static const std::string literal_stringSparseCsc = "Sparse (csc)";
static const std::string literal_stringVector = "Vector";
static const std::string literal_stringMatrix = "Matrix";
/*-------------------------------------------------*/
const std::string& stringDense() { return literal_stringDense; }
const std::string& stringSparseCsc() { return literal_stringSparseCsc; }
const std::string& stringVector() { return literal_stringVector; }
const std::string& stringMatrix() { return literal_stringMatrix; }
/*-------------------------------------------------*/
static const std::string literal_stringPermutationMatrix = "Permutation Matrix";
/*-------------------------------------------------*/
const std::string& stringPermutationMatrix() { return literal_stringPermutationMatrix; }
/*-------------------------------------------------*/
static const std::string literal_stringDenseVector = "Dense Vector";
static const std::string literal_stringDenseMatrix = "Dense Matrix";
/*-------------------------------------------------*/
const std::string& stringDenseVector() { return literal_stringDenseVector; }
const std::string& stringDenseMatrix() { return literal_stringDenseMatrix; }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
