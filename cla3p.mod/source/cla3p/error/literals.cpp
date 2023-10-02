// this file inc
#include "cla3p/error/literals.hpp"

// system
#include <iostream>

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/
std::string IndexOutOfBounds(uint_t m, uint_t n, uint_t i, uint_t j)
{
	std::string ret1 = "requested index (" + std::to_string(i) + "," + std::to_string(j) + ")";
	std::string ret2 = " of matrix with dimensions (" + std::to_string(m) + " x " + std::to_string(n) + ")";

	return (ret1 + ret2);
}
/*-------------------------------------------------*/
std::string IndexOutOfBounds(uint_t n, uint_t i)
{
	std::string ret1 = "requested index " + std::to_string(i);
	std::string ret2 = " of vector with size " + std::to_string(n);

	return (ret1 + ret2);
}
/*-------------------------------------------------*/
std::string Success()
{ 
	return "Success";
}
/*-------------------------------------------------*/
std::string InvalidDimensions()
{ 
	return "Invalid/mismatching dimension(s)";
}
/*-------------------------------------------------*/
std::string InvalidPointer()
{ 
	return "Invalid pointer(s)";
}
/*-------------------------------------------------*/
std::string InvalidLeadingDimension()
{ 
	return "Invalid leading dimension";
}
/*-------------------------------------------------*/
std::string InvalidProperty()
{ 
	return "Invalid/mismatching property(/ies)";
}
/*-------------------------------------------------*/
std::string InvalidPropertyForSquare()
{ 
	return "Property requires square matrix";
}
/*-------------------------------------------------*/
std::string EmptyObject()
{ 
	return "Empty object(s) detected";
}
/*-------------------------------------------------*/
std::string OpNotAllowed()
{ 
	return "This operation is not allowed";
}
/*-------------------------------------------------*/
std::string LapackError()
{ 
	return "Lapack error";
}
/*-------------------------------------------------*/
std::string DivisionByZero()
{ 
	return "Division by zero detected";
}
/*-------------------------------------------------*/
std::string HermitianInconsistency()
{ 
	return "Operation is not consistent with hermitian property"; 
}
/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/
