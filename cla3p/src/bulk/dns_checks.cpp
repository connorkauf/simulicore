// this file inc
#include "dns_checks.hpp"

// system
//#include <cstring>
//#include <algorithm>
//#include <functional>

// 3rd

// cla3p
#include "../error.hpp"
#include "../error_internal.hpp"
//#include "../utils.hpp"
//#include "../proxies/lapack_proxy.hpp"
//#include "../proxies/mkl_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
namespace bulk {
/*-------------------------------------------------*/
status_t input_consistency_status(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
{
	Property prop(ptype);

	if(!m || !n) return status_t::ERROR_DIM;

	if(!a) return status_t::ERROR_PTR;

	if(lda < m) return status_t::ERROR_LD;

	if(!prop.is_valid()) return status_t::ERROR_PROP;

	if(prop.is_lower() && m != n) return status_t::ERROR_PRSQ;

	return status_t::SUCCESS;
}
/*-------------------------------------------------*/
bool check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
{
	status_t stype = input_consistency_status(ptype, m, n, a, lda);

	Property prop(ptype);
	Status status(stype);

	if(!status.success()) throw Exception(status.message());

	return prop.is_lower();
}
/*-------------------------------------------------*/
} // namespace bulk
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
