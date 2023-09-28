// this file inc
#include "cla3p/checks/perm_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/error_internal.hpp"
#include "cla3p/support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	if(nrows != np || ncols != nq) {
		throw NoConsistency(msg::invalid_dimensions() + " for permute operation");
	}
}
/*-------------------------------------------------*/
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	if(ptype != prop_t::GENERAL) {
		throw InvalidOp("Right/Left sided permutations are applied on non-empty general matrices");
	}
	perm_op_consistency_check(nrows, ncols, np, nq);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
