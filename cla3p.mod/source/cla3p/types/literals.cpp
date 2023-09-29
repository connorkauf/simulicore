// this file inc
#include "cla3p/types/literals.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string stringInteger()           { return "Integer"; }
std::string stringUnsignedInteger()   { return "Unsigned " + stringInteger(); }
std::string stringReal()              { return "Real"; }
std::string stringComplex()           { return "Complex"; }
std::string stringSingle()            { return "Single (32bit)"; }
std::string stringDouble()            { return "Double (64bit)"; }
std::string stringDense()             { return "Dense"; }
std::string stringSparseCsc()         { return "Sparse (csc)"; }
std::string stringVector()            { return "Vector"; }
std::string stringMatrix()            { return "Matrix"; }
std::string stringPermutationMatrix() { return "Permutation " + stringMatrix(); }
std::string stringDenseVector()       { return stringDense() + " " + stringVector(); }
std::string stringDenseMatrix ()      { return stringDense() + " " + stringMatrix(); }
/*-------------------------------------------------*/
std::string stringUnknown() { return "Unknown"; }
/*-------------------------------------------------*/
std::string stringNoOperation()                 { return "No operation";}
std::string stringTransposeOperation()          { return "Transpose";}
std::string stringConjugateTransposeOperation() { return "Conjugate Transpose";}
/*-------------------------------------------------*/
std::string stringGeneral()    { return "General"; }
std::string stringSymmetric()  { return "Symmetric"; }
std::string stringHermitian()  { return "Hermitian"; }
std::string stringTriangular() { return "Triangular/Trapezoidal"; }
std::string stringSkew()       { return "Skew"; }
/*-------------------------------------------------*/
std::string stringUpper() { return "Upper"; }
std::string stringLower() { return "Lower"; }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
