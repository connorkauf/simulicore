// this file inc
#include "cla3p/checks/matrix_math_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static void mult_dim_check(
		uint_t nrowsA, uint_t ncolsA, bool syheA, const Operation& opA, 
		uint_t nrowsB, uint_t ncolsB, bool syheB, const Operation& opB, 
		uint_t nrowsC, uint_t ncolsC)
{
	uint_t m = (syheA ? nrowsA : (opA.isTranspose() ? ncolsA : nrowsA));
	uint_t n = (syheB ? ncolsB : (opB.isTranspose() ? nrowsB : ncolsB));

	uint_t kA = (syheA ? ncolsA : (opA.isTranspose() ? nrowsA : ncolsA));
	uint_t kB = (syheB ? nrowsB : (opB.isTranspose() ? ncolsB : nrowsB));

	if(nrowsC != m || ncolsC != n || kA != kB) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}
}
/*-------------------------------------------------*/
void mat_x_vec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		const Property& prX, uint_t nrowsX, uint_t ncolsX, 
		const Property& prY, uint_t nrowsY, uint_t ncolsY)
{
	if(!prA.isValid() || !prX.isGeneral() || !prY.isGeneral()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	bool syheA = (prA.isSymmetric() || prA.isHermitian());

	if(ncolsX > 1 || ncolsY > 1) {
		throw err::NoConsistency("X and Y must be vectors.");
	}

	mult_dim_check(nrowsA, ncolsA, syheA, opA, nrowsX, ncolsX, false, Operation(op_t::N), nrowsY, ncolsY);
}
/*-------------------------------------------------*/
void trm_x_vec_mult_check(const Operation& opA, const Property& prA, uint_t nrowsA, uint_t ncolsA, uint_t sizeX)
{
	if(!prA.isTriangular()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	if(nrowsA != ncolsA) {
		throw err::NoConsistency(msg::NeedSquareMatrix());
	}

	mult_dim_check(nrowsA, ncolsA, false, opA, sizeX, 1, false, Operation(op_t::N), sizeX, 1);
}
/*-------------------------------------------------*/
void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC)
{
	if(!prA.isValid() || !prB.isValid() || !prC.isValid()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	bool syheA = (prA.isSymmetric() || prA.isHermitian());
	bool syheB = (prB.isSymmetric() || prB.isHermitian());

	//
	// Check dimensions
	//

	mult_dim_check(nrowsA, ncolsA, syheA, opA, nrowsB, ncolsB, syheB, opB, nrowsC, ncolsC);

	//
	// Check property-operation combos
	//

	if(!prC.isGeneral()){
		throw err::NoConsistency(msg::InvalidProperty());
	}

	if(prA.isGeneral() && prB.isGeneral()) return;

	if((syheA || prA.isTriangular()) && prB.isGeneral()) {
		if(opB.isTranspose()) {
			throw err::NoConsistency(msg::OpNotAllowed());
		} else {
			return;
		}
	}

	if((syheB || prB.isTriangular()) && prA.isGeneral()) {
		if(opA.isTranspose()) {
			throw err::NoConsistency(msg::OpNotAllowed());
		} else {
			return;
		}
	}

	throw err::NoConsistency(msg::InvalidProperty());
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
