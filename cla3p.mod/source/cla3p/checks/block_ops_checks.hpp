#ifndef CLA3P_BLOCK_OPS_CHECKS_HPP_
#define CLA3P_BLOCK_OPS_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

Property block_op_consistency_check(const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

void      block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void real_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void imag_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BLOCK_OPS_CHECKS_HPP_
