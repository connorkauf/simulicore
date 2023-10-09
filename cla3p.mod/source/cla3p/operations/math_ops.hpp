#ifndef CLA3P_MATH_OPS_HPP_
#define CLA3P_MATH_OPS_HPP_

/**
 * @file
 * Global math operations
 */

#include "cla3p/types/operation.hpp"

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
 ret = alpha * A + beta * B
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient for A.
 * @param[in] A The first input object.
 * @param[in] beta The scaling coefficient for B.
 * @param[in] B The second input object.
 * @return The resulting object.
 */
template <typename T_Scalar, typename T_Object>
T_Object add(
		T_Scalar alpha, const dns::XxObject<T_Scalar,T_Object>& A, 
		T_Scalar beta , const dns::XxObject<T_Scalar,T_Object>& B)
{
	T_Object ret;
	ret.createFromScaledSum(alpha, A, beta, B);
	return ret;
}

/**
 * @ingroup math_op_matvec
 * @brief Updates a vector with a matrix vector product.
 *
 * Performs the operation:
 @verbatim
 Y += alpha * opA(A) * X
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @param[in,out] Y The vector to be updated.
 */

template <typename T_Scalar, typename T_Vector, typename T_Matrix>
void mult(T_Scalar alpha, op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		const dns::XxVector<T_Scalar,T_Vector>& X, 
		dns::XxVector<T_Scalar,T_Vector>& Y)
{
	Operation _opA(opA);
	Y.updateSelfWithScaledMatVec(alpha, _opA, A, X);
}

/**
 * @ingroup math_op_matvec
 * @brief Creates a vector from a matrix vector product.
 *
 * Performs the operation:
 @verbatim
 ret = alpha * opA(A) * X
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The resulting vector.
 *
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
T_Vector mult(T_Scalar alpha, op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		const dns::XxVector<T_Scalar,T_Vector>& X)
{
	Operation _opA(opA);
	T_Vector ret(_opA.isTranspose() ? A.ncols() : A.nrows());
	ret = 0;
	dns::XxVector<T_Scalar,T_Vector>& tmp = ret;
	mult(alpha, opA, A, X, tmp);
	return ret;
}

/**
 * @ingroup math_op_matmat
 * @brief Updates a general matrix with a matrix matrix product.
 *
 * Performs the operation:
 @verbatim
 C += alpha * opA(A) * opB(B)
 @endverbatim
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained
  A: Symmetric   B: General     opA: ignored            opB: must be set to N
  A: Hermitian   B: General     opA: ignored            opB: must be set to N
  A: Triangular  B: General     opA: unconstrained      opB: must be set to N
  A: General     B: Symmetric   opA: must be set to N   opB: ignored         
  A: General     B: Hermitian   opA: must be set to N   opB: ignored         
  A: General     B: Triangular  opA: must be set to N   opB: unconstrained
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input matrix.
 * @param[in,out] C The matrix to be updated.
 *
 * @{
 */
template <typename T_Scalar, typename T_Matrix>
void mult(T_Scalar alpha, 
		op_t opA, const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		op_t opB, const dns::XxMatrix<T_Scalar,T_Matrix>& B, 
		dns::XxMatrix<T_Scalar,T_Matrix>& C)
{
	Operation _opA(opA);
	Operation _opB(opB);
	C.updateSelfWithScaledMatMat(alpha, _opA, A, _opB, B);
}
/** @} */

/**
 * @ingroup math_op_matmat
 * @brief Creates a general matrix from a matrix matrix product.
 *
 * Performs the operation:
 @verbatim
 ret = alpha * opA(A) * opB(B)
 @endverbatim
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained
  A: Symmetric   B: General     opA: ignored            opB: must be set to N
  A: Hermitian   B: General     opA: ignored            opB: must be set to N
  A: Triangular  B: General     opA: unconstrained      opB: must be set to N
  A: General     B: Symmetric   opA: must be set to N   opB: ignored         
  A: General     B: Hermitian   opA: must be set to N   opB: ignored         
  A: General     B: Triangular  opA: must be set to N   opB: unconstrained
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input matrix.
 * @return The resulting matrix.
 */
template <typename T_Scalar, typename T_Matrix>
T_Matrix mult(T_Scalar alpha, 
		op_t opA, const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		op_t opB, const dns::XxMatrix<T_Scalar,T_Matrix>& B)
{
	Operation _opA(opA);
	Operation _opB(opB);
	T_Matrix ret(_opA.isTranspose() ? A.ncols() : A.nrows(), _opB.isTranspose() ? B.nrows() : B.ncols());
	ret = 0;
	mult(alpha, opA, A, opB, B, ret);
	return ret;
}

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
