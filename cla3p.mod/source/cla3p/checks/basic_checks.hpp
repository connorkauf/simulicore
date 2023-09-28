#ifndef CLA3P_BASIC_CHECKS_HPP_
#define CLA3P_BASIC_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void square_check(uint_t m, uint_t n);

void property_compatibility_check(const Property& prop, uint_t m, uint_t n);

void similarity_check(
		const Property& prop1, uint_t nrows1, uint_t ncols1, 
		const Property& prop2, uint_t nrows2, uint_t ncols2);


/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BASIC_CHECKS_HPP_
