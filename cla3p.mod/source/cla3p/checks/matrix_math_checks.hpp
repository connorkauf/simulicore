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

void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC);

void trivec_mult_replace_check(const Property& prA, 
		uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		uint_t sizeX);

void trimat_mult_replace_check(side_t sideA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATRIX_MATH_CHECKS_HPP_
