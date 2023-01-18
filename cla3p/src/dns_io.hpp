#ifndef CLA3P_DNS_IO_HPP_
#define CLA3P_DNS_IO_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void dns_print(uint_t m, uint_t n, const real_t *a, uint_t lda,
		bool lower = false, uint_t nsd = 3, uint_t line_maxlen = 128);

// TODO: for complex & tide it up

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_IO_HPP_
