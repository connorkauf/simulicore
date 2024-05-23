/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/checks/block_ops_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
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
		throw err::OutOfBounds("Block size exceeds matrix dimensions");
	} // error

	if(prop.isLower()) {

		if(jbgn > ibgn) {
			throw err::NoConsistency("Start of block should be in lower part for " + prop.name() + " matrices");
		}

		if(ibgn == jbgn) {
			if(prop.isSquare() && iend != jend) {
				throw err::NoConsistency("Start of block on diagonal of " + prop.name() + " matrices should be associated with a diagonal block");
			}
		} else {
			if(jend > ibgn + 1) {
				throw err::NoConsistency("Block overlaps with upper part of " + prop.name() + " matrix");
			}
			ptype = prop_t::General;
			uplo  = uplo_t::Full;
		} // (non-)diag case

	} // lower

	if(prop.isUpper()) {

		if(ibgn > jbgn) {
			throw err::NoConsistency("Start of block should be in upper part for " + prop.name() + " matrices");
		}

		if(ibgn == jbgn) {
			if(prop.isSquare() && iend != jend) {
				throw err::NoConsistency("Start of block on diagonal of " + prop.name() + " matrices should be associated with a diagonal block");
			}
		} else {
			if(iend > jbgn + 1) {
				throw err::NoConsistency("Block overlaps with lower part of " + prop.name() + " matrix");
			}
			ptype = prop_t::General;
			uplo  = uplo_t::Full;
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
		throw err::NoConsistency(msg::InvalidProperty() + " for block operation");
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
		blprop = Property(prop_t::Symmetric, blprop.uplo());
	}

	if(blprop != block_prop) {
		throw err::NoConsistency(msg::InvalidProperty() + " for block operation");
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
		blprop = Property(prop_t::Skew, blprop.uplo());
	}

	if(blprop != block_prop) {
		throw err::NoConsistency(msg::InvalidProperty() + " for block operation");
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
} // namespace cla3p
/*-------------------------------------------------*/
