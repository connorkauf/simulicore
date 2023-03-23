#ifndef CLA3P_GENERIC_CHECKS_HPP_
#define CLA3P_GENERIC_CHECKS_HPP_

#include "../types.hpp"
#include "../dense.hpp"
#include "../support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

// 
// Checks if m == n
//
void square_check(uint_t m, uint_t n);

// 
// Checks if dense input is valid
//
void dns_consistency_check(const Property& prop, uint_t m, uint_t n, const void *a, uint_t lda);

// 
// Checks if block request is valid
//
Property block_op_consistency_check(const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

void      block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void real_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void imag_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

// 
// Checks if permutation op is valid
//
void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq);
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq);

// 
// Checks if (conjugate) transposition op is valid
//
void transp_op_consistency_check(prop_t ptype, bool conjop);

// 
// Checks if input is similar (dims & prop)
//
void op_similarity_check(const Property& prop1, uint_t nrows1, uint_t ncols1, const Property& prop2, uint_t nrows2, uint_t ncols2);

// 
// Checks for matrix times vector compatibility
//
void matvec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		const Property& prX, uint_t nrowsX, uint_t ncolsX, 
		const Property& prY, uint_t nrowsY, uint_t ncolsY);

// 
// Checks for matrix times matrix compatibility
//
void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC);

// 
// Checks for matrix decomposition
//
template <typename T>
void default_decomp_input_check(const T& mat)
{
	bool supported_prop = (mat.prop().isGeneral() || mat.prop().isSymmetric() || mat.prop().isHermitian());

	if(mat.empty()) {
		throw InvalidOp("Input matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp("Matrices with property " + mat.prop().name() + " not supported for linear decomposition");
	} // valid prop
}

template <typename T>
void llt_decomp_input_check(const T& mat)
{
	bool supported_prop = (
			(std::is_same<T,dns::RdMatrix>::value && mat.prop().isSymmetric()) || 
			(std::is_same<T,dns::RfMatrix>::value && mat.prop().isSymmetric()) || 
			(std::is_same<T,dns::CdMatrix>::value && mat.prop().isHermitian()) || 
			(std::is_same<T,dns::CfMatrix>::value && mat.prop().isHermitian()) ); 

	if(mat.empty()) {
		throw InvalidOp("Input matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp("Matrices with property " + mat.prop().name() + " not supported for SPD Cholesky decomposition");
	} // valid prop
}

// 
// Checks for matrix solution
//
template <typename T>
void default_solve_input_check(const T& rhs)
{
	bool supported_prop = rhs.prop().isGeneral();

	if(rhs.empty()) {
		throw InvalidOp("Input rhs matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp(rhs.prop().name() + " not supported for rhs in linear solution stage");
	} // valid prop
}

// 
// Checks for lapack numerical error
//
void lapack_info_check(int_t info);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_CHECKS_HPP_
