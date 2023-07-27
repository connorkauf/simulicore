#ifndef CLA3P_LITERALS_HPP_
#define CLA3P_LITERALS_HPP_

#include <string>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

const std::string& stringInteger();
const std::string& stringUnsignedInteger();
const std::string& stringReal();
const std::string& stringComplex();
const std::string& stringSingle();
const std::string& stringDouble();

const std::string& stringDense();
const std::string& stringSparseCsc();
const std::string& stringVector();
const std::string& stringMatrix();

const std::string& stringPermutationMatrix();

const std::string& stringDenseVector();
const std::string& stringDenseMatrix();

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LITERALS_HPP_
