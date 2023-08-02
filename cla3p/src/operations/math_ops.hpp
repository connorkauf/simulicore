#ifndef CLA3P_MATH_OPS_HPP_
#define CLA3P_MATH_OPS_HPP_

/**
 * @file
 * Global math operations
 */

#include "../types/operation.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Object> class XxObject;
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup math_op_matadd
 * @brief Update operation on object.
 *
 * Performs the operation:
 @verbatim
 trg += alpha * src
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] src The input object.
 * @param[in,out] trg The object to be updated.
 */
template <typename T_Scalar, typename T_Object>
void update(T_Scalar alpha, const dns::XxObject<T_Scalar,T_Object>& src, dns::XxObject<T_Scalar,T_Object>& trg)
{
	trg.updateSelfWithScaledOther(alpha, src);
}

/**
 * @ingroup math_op_matadd
 * @brief Adds two scaled objects.
 *
 * Performs the operation:
 @verbatim
 trg = alpha * srcA + beta * srcB
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient for srcA.
 * @param[in] srcA The first input object.
 * @param[in] beta The scaling coefficient for srcB.
 * @param[in] srcB The second input object.
 * @return The resulting object.
 */
template <typename T_Scalar, typename T_Object>
T_Object add(
		T_Scalar alpha, const dns::XxObject<T_Scalar,T_Object>& srcA, 
		T_Scalar beta , const dns::XxObject<T_Scalar,T_Object>& srcB)
{
	T_Object ret;
	ret.createFromScaledSum(alpha, srcA, beta, srcB);
	return ret;
}

/**
 * @ingroup math_op_matvec
 * @brief Updates a vector with a matrix vector product.
 *
 * Performs the operation:
 @verbatim
 trg += alpha * opA(srcA) * srcX
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @param[in,out] trg The vector to be updated.
 */

template <typename T_Scalar, typename T_Vector, typename T_Matrix>
void mult(T_Scalar alpha, const Operation& opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& srcA, 
		const dns::XxVector<T_Scalar,T_Vector>& srcX, 
		dns::XxVector<T_Scalar,T_Vector>& trg)
{
	trg.updateSelfWithScaledMatVec(alpha, opA, srcA, srcX);
}

/**
 * @ingroup math_op_matvec
 * @brief Creates a vector from a matrix vector product.
 *
 * Performs the operation:
 @verbatim
 trg = alpha * opA(srcA) * srcX
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @return The resulting vector.
 *
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
T_Vector mult(T_Scalar alpha, const Operation& opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& srcA, 
		const dns::XxVector<T_Scalar,T_Vector>& srcX)
{
	T_Vector ret(opA.isTranspose() ? srcA.ncols() : srcA.nrows());
	ret = 0;
	dns::XxVector<T_Scalar,T_Vector>& tmp = ret;
	mult(alpha, opA, srcA, srcX, tmp);
	return ret;
}

/**
 * @ingroup math_op_matmat
 * @brief Updates a general matrix with a matrix matrix product.
 *
 * Performs the operation:
 @verbatim
 trg += alpha * opA(srcA) * opB(srcB)
 @endverbatim
 * Valid combinations are the following:
 @verbatim
  srcA: GENERAL     srcB: GENERAL     opA: unconstrained      opB: unconstrained
  srcA: SYMMETRIC   srcB: GENERAL     opA: ignored            opB: must be set to N
  srcA: HERMITIAN   srcB: GENERAL     opA: ignored            opB: must be set to N
  srcA: TRIANGULAR  srcB: GENERAL     opA: unconstrained      opB: must be set to N
  srcA: GENERAL     srcB: SYMMETRIC   opA: must be set to N   opB: ignored         
  srcA: GENERAL     srcB: HERMITIAN   opA: must be set to N   opB: ignored         
  srcA: GENERAL     srcB: TRIANGULAR  opA: must be set to N   opB: unconstrained
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA.
 * @param[in] srcA The input matrix.
 * @param[in] opB The operation to be performed for matrix srcB.
 * @param[in] srcB The input matrix.
 * @param[in,out] trg The matrix to be updated.
 *
 * @{
 */
template <typename T_Scalar, typename T_Matrix>
void mult(T_Scalar alpha, 
		const Operation& opA, const dns::XxMatrix<T_Scalar,T_Matrix>& srcA, 
		const Operation& opB, const dns::XxMatrix<T_Scalar,T_Matrix>& srcB, 
		dns::XxMatrix<T_Scalar,T_Matrix>& trg)
{
	trg.updateSelfWithScaledMatMat(alpha, opA, srcA, opB, srcB);
}
/** @} */

/**
 * @ingroup math_op_matmat
 * @brief Creates a general matrix from a matrix matrix product.
 *
 * Performs the operation:
 @verbatim
 trg = alpha * opA(srcA) * opB(srcB)
 @endverbatim
 * Valid combinations are the following:
 @verbatim
  srcA: GENERAL     srcB: GENERAL     opA: unconstrained      opB: unconstrained
  srcA: SYMMETRIC   srcB: GENERAL     opA: ignored            opB: must be set to N
  srcA: HERMITIAN   srcB: GENERAL     opA: ignored            opB: must be set to N
  srcA: TRIANGULAR  srcB: GENERAL     opA: unconstrained      opB: must be set to N
  srcA: GENERAL     srcB: SYMMETRIC   opA: must be set to N   opB: ignored         
  srcA: GENERAL     srcB: HERMITIAN   opA: must be set to N   opB: ignored         
  srcA: GENERAL     srcB: TRIANGULAR  opA: must be set to N   opB: unconstrained
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA.
 * @param[in] srcA The input matrix.
 * @param[in] opB The operation to be performed for matrix srcB.
 * @param[in] srcB The input matrix.
 * @return The resulting matrix.
 */
template <typename T_Scalar, typename T_Matrix>
T_Matrix mult(T_Scalar alpha, 
		const Operation& opA, const dns::XxMatrix<T_Scalar,T_Matrix>& srcA, 
		const Operation& opB, const dns::XxMatrix<T_Scalar,T_Matrix>& srcB)
{
	T_Matrix ret(opA.isTranspose() ? srcA.ncols() : srcA.nrows(), opB.isTranspose() ? srcB.nrows() : srcB.ncols());
	ret = 0;
	mult(alpha, opA, srcA, opB, srcB, ret);
	return ret;
}

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
