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
void square_check(uint_t m, uint_t n)
{
	if(m != n) {
		throw NoConsistency(msg::invalid_property_for_square());
	}
}
/*-------------------------------------------------*/
void dns_consistency_check(const Property& prop, uint_t m, uint_t n, const void *a, uint_t lda)
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

	if(!prop.isValid()) {
		throw NoConsistency(msg::invalid_property());
	}

	if(prop.isSquare()) {
		square_check(m, n);
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
Property block_op_consistency_check(
		const Property& prop, 
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
	prop_t ptype = prop.type();
	uplo_t uplo  = prop.uplo();

	uint_t iend = ibgn + ni;
	uint_t jend = jbgn + nj;

	if(ibgn >= nrows || jbgn >= ncols || iend > nrows || jend > ncols) {
		throw OutOfBounds("Block size exceeds matrix dimensions");
	} // error

	if(prop.isLower()) {

		if(jbgn > ibgn) {
			throw NoConsistency("Start of block should be in lower part for " + prop.name() + " matrices");
		}

		if(ibgn == jbgn) {
			if(iend != jend) {
				throw NoConsistency("Start of block on diagonal of " + prop.name() + " matrices should be associated with a diagonal block");
			}
		} else {
			if(jend > ibgn + 1) {
				throw NoConsistency("Block overlaps with upper part of " + prop.name() + " matrix");
			}
			ptype = prop_t::GENERAL;
			uplo  = uplo_t::F;
		} // (non-)diag case

	} // lower

	if(prop.isUpper()) {

		if(ibgn > jbgn) {
			throw NoConsistency("Start of block should be in upper part for " + prop.name() + " matrices");
		}

		if(ibgn == jbgn) {
			if(iend != jend) {
				throw NoConsistency("Start of block on diagonal of " + prop.name() + " matrices should be associated with a diagonal block");
			}
		} else {
			if(iend > jbgn + 1) {
				throw NoConsistency("Block overlaps with lower part of " + prop.name() + " matrix");
			}
			ptype = prop_t::GENERAL;
			uplo  = uplo_t::F;
		} // (non-)diag case

	} // lower

	return Property(ptype, uplo);
}
/*-------------------------------------------------*/
void block_op_consistency_check(
		const Property& block_prop, 
		const Property& prop, 
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
	Property blprop = block_op_consistency_check(prop, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blprop != block_prop) {
		throw NoConsistency(msg::invalid_property() + " for block operation");
	}
}
/*-------------------------------------------------*/
void real_block_op_consistency_check(
		const Property& block_prop, 
		const Property& prop, 
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
	Property blprop = block_op_consistency_check(prop, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blprop.isHermitian()) {
		blprop = Property(prop_t::SYMMETRIC, blprop.uplo());
	}

	if(blprop != block_prop) {
		throw NoConsistency(msg::invalid_property() + " for block operation");
	}
}
/*-------------------------------------------------*/
void imag_block_op_consistency_check(
		const Property& block_prop, 
		const Property& prop, 
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
	Property blprop = block_op_consistency_check(prop, nrows, ncols, ibgn, jbgn, ni, nj);

	if(blprop.isHermitian()) {
		throw InvalidOp("Block should be a skew matrix. Skew matrices are not yet supported");
	}

	if(blprop != block_prop) {
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
void op_similarity_check(const Property& prop1, uint_t nrows1, uint_t ncols1, const Property&  prop2, uint_t nrows2, uint_t ncols2)
{
	if(nrows1 != nrows2 || ncols1 != ncols2) {
		throw NoConsistency(msg::invalid_dimensions());
	}

	if(prop1 != prop2) {
		throw NoConsistency(msg::invalid_property());
	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
