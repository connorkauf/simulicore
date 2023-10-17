#ifndef CLA3P_ERROR_LITERALS_HPP_
#define CLA3P_ERROR_LITERALS_HPP_

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/

std::string IndexOutOfBounds(uint_t m, uint_t n, uint_t i, uint_t j);
std::string IndexOutOfBounds(uint_t n, uint_t i);

std::string Success();
std::string InvalidDimensions();
std::string InvalidPointer();
std::string InvalidLeadingDimension();
std::string InvalidProperty();
std::string NeedSquareMatrix();
std::string EmptyObject();
std::string OpNotAllowed();
std::string LapackError();
std::string DivisionByZero();
std::string HermitianInconsistency();

/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_LITERALS_HPP_
