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
#include "cla3p/checks/matrix_math_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void mult_dim_check(
		uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		uint_t nrowsC, uint_t ncolsC)
{
	uint_t m = (opA.isTranspose() ? ncolsA : nrowsA);
	uint_t n = (opB.isTranspose() ? nrowsB : ncolsB);

	uint_t kA = (opA.isTranspose() ? nrowsA : ncolsA);
	uint_t kB = (opB.isTranspose() ? ncolsB : nrowsB);

	if(nrowsC != m || ncolsC != n || kA != kB) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}
}
/*-------------------------------------------------*/
void mat_x_vec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		uint_t sizeX, uint_t sizeY)
{
	if(!prA.isValid()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	mult_dim_check(nrowsA, ncolsA, opA, sizeX, 1, Operation(op_t::N), sizeY, 1);
}
/*-------------------------------------------------*/
#if 0
void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC)
{
	//
	// Check dimensions
	//

	mult_dim_check(nrowsA, ncolsA, opA, nrowsB, ncolsB, opB, nrowsC, ncolsC);

	//
	// Check individual properties
	//

	bool specialA = (prA.isSymmetric() || prA.isHermitian() || prA.isTriangular());
	bool specialB = (prB.isSymmetric() || prB.isHermitian() || prB.isTriangular());
	bool specialC = (prC.isSymmetric() || prC.isHermitian());

	if(!(prA.isGeneral() || specialA)) {
		throw err::NoConsistency(msg::InvalidProperty() + " for first matrix in matrix-matrix product");
	}

	if(!(prB.isGeneral() || specialB)) {
		throw err::NoConsistency(msg::InvalidProperty() + " for second matrix in matrix-matrix product");
	}

	if(!(prC.isGeneral() || specialC)) {
		throw err::NoConsistency(msg::InvalidProperty() + " for resulting matrix in matrix-matrix product");
	}

	//
	// Check property combos
	//

	if(specialC && !(prA.isGeneral() && prB.isGeneral())) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	//
	// Check property-operation combos
	//

	if(specialA && !(prB.isGeneral() && !opB.isTranspose())) {
		throw err::NoConsistency(msg::OpNotAllowed());
	}

	if(specialB && !(prA.isGeneral() && !opA.isTranspose())) {
		throw err::NoConsistency(msg::OpNotAllowed());
	}
}
#endif
/*-------------------------------------------------*/
void trivec_mult_replace_check(const Property& prA, 
		uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		uint_t sizeX)
{
	if(!prA.isTriangular()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	//
	// Check dimensions
	//

	square_check(nrowsA, ncolsA);

	mult_dim_check(nrowsA, ncolsA, opA, sizeX, 1, noOp(), sizeX, 1);
}
/*-------------------------------------------------*/
void trimat_mult_replace_check(side_t sideA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB)
{
	if(!prA.isTriangular() || !prB.isGeneral()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	//
	// Check dimensions
	//

	square_check(nrowsA, ncolsA);

	if(sideA == side_t::Left) {
		mult_dim_check(
				nrowsA, ncolsA, opA, 
				nrowsB, ncolsB, noOp(), 
				nrowsB, ncolsB);
	} else if(sideA == side_t::Right) {
		mult_dim_check(
				nrowsB, ncolsB, noOp(), 
				nrowsA, ncolsA, opA, 
				nrowsB, ncolsB);
	} // sideA
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
