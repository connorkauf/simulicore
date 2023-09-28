#ifndef CLA3P_PERM_CHECKS_HPP_
#define CLA3P_PERM_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq);
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PERM_CHECKS_HPP_
