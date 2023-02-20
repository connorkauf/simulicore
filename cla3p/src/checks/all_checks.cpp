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
void dns_consistency_check(prop_t ptype, uint_t m, uint_t n, const void *a, uint_t lda)
{
	Property prop(ptype);

	if(!m || !n) {
		throw NoConsistency(msg::invalid_dimensions());
	}

	if(!a) {
		throw NoConsistency(msg::invalid_pointer());
	}

	if(lda < m) {
		throw NoConsistency(msg::invalid_leading_dimension());
	}

	if(!prop.is_valid()) {
		throw NoConsistency(msg::invalid_property());
	}

	if(prop.is_lower() && m != n) {
		throw NoConsistency(msg::invalid_property_for_square());
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
	//
	// Used for when getting a block
	//
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
	//
	// Used for when setting a block
	//
	prop_t blptype = block_op_consistency_check(ptype, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blptype != block_ptype) {
		throw NoConsistency(msg::invalid_property() + " for block operation");
	}
}
/*-------------------------------------------------*/
void real_block_op_consistency_check(
		prop_t block_ptype, 
		prop_t ptype, 
		uint_t nrows, 
		uint_t ncols, 
		uint_t ibgn, 
		uint_t jbgn, 
		uint_t ni, 
		uint_t nj)
{
	//
	// Used for when setting a real object as a real part of a complex object
	//
	prop_t blptype = block_op_consistency_check(ptype, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blptype == prop_t::HERMITIAN) {
		blptype = prop_t::SYMMETRIC;
	}

	if(blptype != block_ptype) {
		throw NoConsistency(msg::invalid_property() + " for block operation");
	}
}
/*-------------------------------------------------*/
void imag_block_op_consistency_check(
		prop_t block_ptype, 
		prop_t ptype, 
		uint_t nrows, 
		uint_t ncols, 
		uint_t ibgn, 
		uint_t jbgn, 
		uint_t ni, 
		uint_t nj)
{
	//
	// Used for when setting a real object as a imag part of a complex object
	//
	prop_t blptype = block_op_consistency_check(ptype, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blptype == prop_t::HERMITIAN) {
		throw InvalidOp("Input should be a skew matrix. Skew matrices are not yet supported");
	}

	if(blptype != block_ptype) {
		throw NoConsistency(msg::invalid_property() + " for block operation");
	}
}
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
void transp_op_consistency_check(prop_t ptype, bool conjop)
{
	if(ptype != prop_t::GENERAL) {
		throw InvalidOp(std::string(conjop ? "Conjugate t" : "T") + "ranspositions are applied on non-empty general matrices");
	}
}
/*-------------------------------------------------*/
void op_similarity_check(prop_t ptype1, uint_t nrows1, uint_t ncols1, prop_t ptype2, uint_t nrows2, uint_t ncols2)
{
	if(nrows1 != nrows2 || ncols1 != ncols2) {
		throw NoConsistency(msg::invalid_dimensions());
	}

	if(ptype1 != ptype2) {
		throw NoConsistency(msg::invalid_property());
	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
