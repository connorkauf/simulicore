#ifndef CLA3P_DECOMP_LLT_CHECKS_HPP_
#define CLA3P_DECOMP_LLT_CHECKS_HPP_

#include "cla3p/types.hpp"
#include "cla3p/dense.hpp"
#include "cla3p/support/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

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
		throw InvalidOp("Matrices with property " + mat.prop().name() + " not supported for PD Cholesky (LL') decomposition");
	} // valid prop

	if(mat.nrows() != mat.ncols()) {
		throw InvalidOp("Only square matrices are supported for linear decomposition");
	} // square
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DECOMP_LLT_CHECKS_HPP_
