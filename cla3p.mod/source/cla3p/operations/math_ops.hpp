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
 * @brief Update an object with a compatible scaled object.
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
 * @brief Adds two compatible scaled objects.
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
 * @return The result of the operation `alpha*A + beta*B`.
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
 * @brief Updates a vector with a matrix-vector product.
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
	Y.updateSelfWithScaledMatVec(alpha, opA, A, X);
}

/**
 * @ingroup math_op_matvec
 * @brief Creates a vector from a matrix-vector product.
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
 * @return The vector `alpha*opA(A)*X`.
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
 * @ingroup math_op_matvec
 * @brief Replaces a vector with a triangular matrix-vector product.
 *
 * Performs the operation:
 @verbatim
  X = opA(A) * X
 @endverbatim
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] X The vector to be replaced.
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
void trimult(op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		dns::XxVector<T_Scalar,T_Vector>& X)
{
	X.replaceSelfWithTriVec(opA, A);
}

/**
 * @ingroup math_op_matvec
 * @brief Replaces a vector with the solution of a triangular system.
 *
 * Solves the system:
 @verbatim
  opA(A) * X = X
 @endverbatim
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] X The vector to be replaced.
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
void trisol(op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		dns::XxVector<T_Scalar,T_Vector>& X)
{
	X.replaceSelfWithInvTriVec(opA, A);
}

/**
 * @ingroup math_op_matmat
 * @brief Updates a general matrix with a matrix-matrix product.
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
 */
template <typename T_Scalar, typename T_Matrix>
void mult(T_Scalar alpha, 
		op_t opA, const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		op_t opB, const dns::XxMatrix<T_Scalar,T_Matrix>& B, 
		dns::XxMatrix<T_Scalar,T_Matrix>& C)
{
	C.updateSelfWithScaledMatMat(alpha, opA, A, opB, B);
}

/**
 * @ingroup math_op_matmat
 * @brief Creates a general matrix from a matrix-matrix product.
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
 * @return The matrix `alpha*opA(A)*opB(B)`.
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

/**
 * @ingroup math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation:
 @verbatim
  B = alpha * opA(A) * B
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B The matrix to be replaced.
 */
template <typename T_Scalar, typename T_Matrix>
void trimult(T_Scalar alpha, op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		dns::XxMatrix<T_Scalar,T_Matrix>& B)
{
	B.replaceSelfWithScaledTriMat(alpha, side_t::Left, opA, A);
}

/**
 * @ingroup math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation:
 @verbatim
  B = alpha * B * opA(A)
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B The matrix to be replaced.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Scalar, typename T_Matrix>
void trimult(T_Scalar alpha, 
		dns::XxMatrix<T_Scalar,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<T_Scalar,T_Matrix>& A) 
{
	B.replaceSelfWithScaledTriMat(alpha, side_t::Right, opA, A);
}

/**
 * @ingroup math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system:
 @verbatim
  opA(A) * B = alpha * B
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B The matrix to be replaced.
 */
template <typename T_Scalar, typename T_Matrix>
void trisol(T_Scalar alpha, op_t opA, 
		const dns::XxMatrix<T_Scalar,T_Matrix>& A, 
		dns::XxMatrix<T_Scalar,T_Matrix>& B)
{
	B.replaceSelfWithScaledInvTriMat(alpha, side_t::Left, opA, A);
}

/**
 * @ingroup math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system:
 @verbatim
  B * opA(A) = alpha * B
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B The matrix to be replaced.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Scalar, typename T_Matrix>
void trisol(T_Scalar alpha, 
		dns::XxMatrix<T_Scalar,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<T_Scalar,T_Matrix>& A) 
{
	B.replaceSelfWithScaledInvTriMat(alpha, side_t::Right, opA, A);
}

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
