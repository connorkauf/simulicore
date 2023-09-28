#ifndef CLA3P_DNS_CHECKS_HPP_
#define CLA3P_DNS_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void dns_consistency_check(const Property& prop, uint_t m, uint_t n, const void *a, uint_t lda);
void dns_consistency_check(uint_t m, uint_t n, const void *a, uint_t lda);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CHECKS_HPP_
