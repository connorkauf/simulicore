#ifndef CLA3P_GENERIC_CHECKS_HPP_
#define CLA3P_GENERIC_CHECKS_HPP_

#include "../types.hpp"
#include "../support/error_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

// 
// Checks if dense input is valid and returns status
//
status_t dns_input_consistency_status(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda);

// 
// Checks if dense input is valid and returns lower flg
//
bool dns_consistency_check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda);

// 
// Checks if block request is valid and returns block property type
//
prop_t block_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_CHECKS_HPP_
