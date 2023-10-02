#ifndef CLA3P_TYPE_LITERALS_HPP_
#define CLA3P_TYPE_LITERALS_HPP_

#include <string>

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/
std::string Unknown();

std::string Integer();
std::string UnsignedInteger();
std::string Real();
std::string Complex();
std::string Single();
std::string Double();
std::string Dense();
std::string SparseCsc();
std::string Vector();
std::string Matrix();
std::string PermutationMatrix();
std::string DenseVector();
std::string DenseMatrix();

std::string NoOperation();
std::string TransposeOperation();
std::string ConjugateTransposeOperation();

std::string General();
std::string Symmetric();
std::string Hermitian();
std::string Triangular();
std::string Skew();

std::string Upper();
std::string Lower();

/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_TYPE_LITERALS_HPP_
