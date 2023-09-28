// this file inc
#include "cla3p/checks/dns_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/error_internal.hpp"
#include "cla3p/support/error.hpp"
#include "cla3p/checks/basic_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void dns_consistency_check(uint_t m, uint_t n, const void *a, uint_t lda)
{
	if(!m || !n) {
		throw NoConsistency(msg::invalid_dimensions());
	}

	if(!a) {
		throw NoConsistency(msg::invalid_pointer());
	}

	if(lda < m) {
		throw NoConsistency(msg::invalid_leading_dimension());
	}
}
/*-------------------------------------------------*/
void dns_consistency_check(const Property& prop, uint_t m, uint_t n, const void *a, uint_t lda)
{
	dns_consistency_check(m, n, a, lda);
	property_compatibility_check(prop, m, n);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
