#ifndef CLA3P_MATRIX_MATH_CHECKS_HPP_
#define CLA3P_MATRIX_MATH_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void mat_x_vec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		const Property& prX, uint_t nrowsX, uint_t ncolsX, 
		const Property& prY, uint_t nrowsY, uint_t ncolsY);

void trm_x_vec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		uint_t sizeX);

void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATRIX_MATH_CHECKS_HPP_
