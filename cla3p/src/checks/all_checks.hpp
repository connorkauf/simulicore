#ifndef CLA3P_GENERIC_CHECKS_HPP_
#define CLA3P_GENERIC_CHECKS_HPP_

#include "../types.hpp"
#include "../support/error_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

// 
// Checks if dense input is valid
//
void dns_consistency_check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda);

// 
// Checks if block request is valid
//
prop_t block_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void block_op_consistency_check(prop_t block_ptype, prop_t ptype, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

// 
// Checks if permutation op is valid
//
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq);
void perm_syhe_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq);

// 
// Checks if (conjugate) transposition op is valid
//
void transp_op_consistency_check(prop_t ptype, bool conjop);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_CHECKS_HPP_
