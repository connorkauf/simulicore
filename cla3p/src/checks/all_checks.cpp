// this file inc
#include "all_checks.hpp"

// system

// 3rd

// cla3p
#include "../support/error_internal.hpp"
#include "../support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static status_t dns_input_consistency_status(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
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
void dns_consistency_check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
{
	status_t stype = dns_input_consistency_status(ptype, m, n, a, lda);
	Status status(stype);
	if(!status.success()) {
		throw NoConsistency(status.message());
	}
}
/*-------------------------------------------------*/
#if 0
static std::string block_op_dims_to_str(
		uint_t nrows, 
		uint_t ncols, 
		uint_t ibgn, 
		uint_t jbgn, 
		uint_t ni, 
		uint_t nj)
{
	std::string ret;
	ret.append("\n  Starting position: (" + std::to_string(ibgn) + "," + std::to_string(jbgn) +  ")");
	ret.append("\n  Block dimensions : (" + std::to_string(ni) + "," + std::to_string(nj) +  ")");
	ret.append("\n  Dimension limits : (" + std::to_string(nrows) + "," + std::to_string(ncols) +  ")");
	return ret;
}
#endif
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
	prop_t ret = ptype;

	uint_t iend = ibgn + ni;
	uint_t jend = jbgn + nj;

	if(ibgn >= nrows || jbgn >= ncols || iend > nrows || jend > ncols) {
		throw OutOfBounds("Block size exceeds matrix dimensions");
	} // error

	Property prop(ptype);

	if(prop.is_lower()) {

		if(jbgn > ibgn) {
			throw NoConsistency("Start of block should be in lower part for Symmetric/Hermitian matrices");
		}

		if(ibgn == jbgn) {
			if(iend != jend) {
				throw NoConsistency("Start of block on diagonal of Symmetric/Hermitian matrices should be associated with a diagonal block");
			}
			ret = ptype;
		} else {
			if(jend > ibgn + 1) {
				throw NoConsistency("Block overlaps with upper part of Symmetric/Hermitian matrix");
			}
			ret = prop_t::GENERAL;
		} // (non-)diag case

	} // lower

	return ret;
}
/*-------------------------------------------------*/
void block_op_consistency_check(
		prop_t block_ptype, 
		prop_t ptype, 
		uint_t nrows, 
		uint_t ncols, 
		uint_t ibgn, 
		uint_t jbgn, 
		uint_t ni, 
		uint_t nj)
{
	prop_t blptype = block_op_consistency_check(ptype, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blptype != block_ptype) {
		throw NoConsistency("Invalid block property for block operation");
	}
}
/*-------------------------------------------------*/
static void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	if(nrows != np || ncols != nq) {
		throw NoConsistency(msg_invalid_dimensions() + " for permute operation");
	}
}
/*-------------------------------------------------*/
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	perm_op_consistency_check(nrows, ncols, np, nq);
	if(ptype != prop_t::GENERAL) {
		throw InvalidOp("Right/Left sided permutations are applied on general matrices");
	}
}
/*-------------------------------------------------*/
void perm_syhe_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	perm_op_consistency_check(nrows, ncols, np, nq);
	if(ptype != prop_t::SYMMETRIC && ptype != prop_t::HERMITIAN) {
		throw InvalidOp("Symmetric/Hermitian permutations are applied on Symmetric/Hermitian matrices");
	}
}
/*-------------------------------------------------*/
void transp_op_consistency_check(prop_t ptype, bool conjop)
{
	if(ptype != prop_t::GENERAL) {
		throw InvalidOp(std::string(conjop ? "Conjugate t" : "T") + "ranspositions are applied on general matrices");
	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
