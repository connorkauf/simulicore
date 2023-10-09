#ifndef CLA3P_SOLVE_CHECKS_HPP_
#define CLA3P_SOLVE_CHECKS_HPP_

#include "cla3p/error/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T>
void default_solve_input_check(uint_t n, const T& rhs)
{
	bool supported_prop = rhs.prop().isGeneral();

	if(rhs.nrows() != n) {
		throw err::InvalidOp("Mismatching dimensions for linear solution stage");
	} // dim check

	if(rhs.empty()) {
		throw err::InvalidOp("Input rhs matrix is empty");
	} else if(!supported_prop) {
		throw err::InvalidOp(rhs.prop().name() + " not supported for rhs in linear solution stage");
	} // valid prop
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SOLVE_CHECKS_HPP_
