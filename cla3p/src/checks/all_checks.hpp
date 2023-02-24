#ifndef CLA3P_GENERIC_CHECKS_HPP_
#define CLA3P_GENERIC_CHECKS_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

// 
// Checks if m == n
//
void square_check(uint_t m, uint_t n);

// 
// Checks if dense input is valid
//
void dns_consistency_check(const Property& prop, uint_t m, uint_t n, const void *a, uint_t lda);

// 
// Checks if block request is valid
//
Property block_op_consistency_check(const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

void      block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void real_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void imag_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

// 
// Checks if permutation op is valid
//
void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq);
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq);

// 
// Checks if (conjugate) transposition op is valid
//
void transp_op_consistency_check(prop_t ptype, bool conjop);

// 
// Checks if input is similar (dims & prop)
//
void op_similarity_check(prop_t ptype1, uint_t nrows1, uint_t ncols1, prop_t ptype2, uint_t nrows2, uint_t ncols2);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_CHECKS_HPP_
