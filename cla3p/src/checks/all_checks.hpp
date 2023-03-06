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
void op_similarity_check(const Property& prop1, uint_t nrows1, uint_t ncols1, const Property& prop2, uint_t nrows2, uint_t ncols2);

// 
// Checks for matrix times vector compatibility
//
void matvec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		const Property& prX, uint_t nrowsX, uint_t ncolsX, 
		const Property& prY, uint_t nrowsY, uint_t ncolsY);

// 
// Checks for matrix times matrix compatibility
//
void gematmat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_CHECKS_HPP_
