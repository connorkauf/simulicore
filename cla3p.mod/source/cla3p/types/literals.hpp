#ifndef CLA3P_TYPE_LITERALS_HPP_
#define CLA3P_TYPE_LITERALS_HPP_

#include <string>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

std::string stringInteger();
std::string stringUnsignedInteger();
std::string stringReal();
std::string stringComplex();
std::string stringSingle();
std::string stringDouble();
std::string stringDense();
std::string stringSparseCsc();
std::string stringVector();
std::string stringMatrix();
std::string stringPermutationMatrix();
std::string stringDenseVector();
std::string stringDenseMatrix();

std::string stringUnknown();

std::string stringNoOperation();
std::string stringTransposeOperation();
std::string stringConjugateTransposeOperation();

std::string stringGeneral();
std::string stringSymmetric();
std::string stringHermitian();
std::string stringTriangular();
std::string stringSkew();

std::string stringUpper();
std::string stringLower();

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_TYPE_LITERALS_HPP_
