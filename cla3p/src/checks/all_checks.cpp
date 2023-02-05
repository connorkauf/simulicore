// this file inc
#include "all_checks.hpp"

// system

// 3rd

// cla3p
#include "../support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
status_t dns_input_consistency_status(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
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
bool dns_consistency_check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
{
	status_t stype = dns_input_consistency_status(ptype, m, n, a, lda);

	Property prop(ptype);
	Status status(stype);

	if(!status.success()) {
		throw Exception(status.message());
	}

	return prop.is_lower();
}
/*-------------------------------------------------*/
prop_t block_op_consistency_check(
		prop_t ptype, 
		uint_t nrows, 
		uint_t ncols, 
		uint_t ibgn, 
		uint_t jbgn, 
		uint_t ni, 
		uint_t nj)
{
	// 
	// TODO: proper messages
	//

	prop_t ret = ptype;

	uint_t iend = ibgn + ni;
	uint_t jend = jbgn + nj;

	if(ibgn >= nrows || jbgn >= ncols || iend > nrows || jend > ncols) {
		throw OutOfBounds("Block size breaches dimension limits");
	} // error

	Property prop(ptype);

	if(prop.is_lower()) {

		if(jbgn > ibgn) {
			throw NoConsistency("Start of block should be in lower part");
		}

		if(ibgn == jbgn) {
			if(iend != jend) {
				throw NoConsistency("Start of block on diagonal should result a diagonal block");
			}
			ret = ptype;
		} else {
			if(jend > ibgn + 1) {
				throw NoConsistency("Block overlaps with upper part");
			}
			ret = prop_t::GENERAL;
		} // (non-)diag case

	} // lower

	return ret;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
