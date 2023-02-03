#ifndef CLA3P_DNS_CHECKS_HPP_
#define CLA3P_DNS_CHECKS_HPP_

#include "../types.hpp"
#include "../support/error_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
namespace bulk {
/*-------------------------------------------------*/

// simple check of input
status_t input_consistency_status(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda);

// throws exception on error
// returns if pattern is lower
bool check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda);

/*-------------------------------------------------*/
} // namespace bulk
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CHECKS_HPP_
