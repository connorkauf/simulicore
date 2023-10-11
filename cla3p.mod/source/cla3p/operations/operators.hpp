#ifndef CLA3P_OPERATORS_HPP_
#define CLA3P_OPERATORS_HPP_

/**
 * @file
 * Global math operator definitions
 */

#include "cla3p/error/error.hpp"
#include "cla3p/operations/math_ops.hpp"
#include "cla3p/linsol/dns_auto_lsolver.hpp"

/*-------------------------------------------------*/
namespace cla3p {
template <typename T_Int> class PxMatrix;
namespace dns {
template <typename T_Scalar, typename T_Object> class XxObject;
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup operators_scal
 * @brief Multiplies a scalar with an object.
 *
 * Performs the operation:
 @verbatim
 ret = val * src
 @endverbatim
 *
 * @param[in] val The coefficient value.
 * @param[in] src The input object.
 * @return The scaled object.
 */
template <typename T_Scalar, typename T_Object>
T_Object operator*(T_Scalar val, const cla3p::dns::XxObject<T_Scalar,T_Object>& src) 
{ 
	T_Object ret = src.copy();
	ret *= val;
	return ret; 
}

/**
 * @ingroup operators_scal
 * @brief Multiplies an object with a scalar.
 *
 * Performs the operation:
 @verbatim
 ret = src * val
 @endverbatim
 *
 * @param[in] src The input object.
 * @param[in] val The coefficient value.
 * @return The scaled object.
 */
template <typename T_Scalar, typename T_Object>
T_Object operator*(const cla3p::dns::XxObject<T_Scalar,T_Object>& src, T_Scalar val) 
{ 
	return (val * src);
}

/**
 * @ingroup operators_scal
 * @brief Devides an object by a scalar.
 *
 * Performs the operation:
 @verbatim
 ret = src / val
 @endverbatim
 *
 * @param[in] src The input object.
 * @param[in] val The coefficient value.
 * @return The scaled object.
 */
template <typename T_Scalar, typename T_Object>
T_Object operator/(const cla3p::dns::XxObject<T_Scalar,T_Object>& src, T_Scalar val) 
{ 
	T_Object ret = src.copy();
	ret /= val;
	return ret; 
}

/**
 * @ingroup operators_scal
 * @brief Scaling operator.
 *
 * Scales src by val.
 *
 * @param[in] src The input object.
 * @param[in] val The scaling coefficient.
 */
template <typename T_Scalar, typename T_Object>
void operator*=(cla3p::dns::XxObject<T_Scalar,T_Object>& src, T_Scalar val)
{
	src.scale(val);
}

/**
 * @ingroup operators_scal
 * @brief Scaling operator.
 *
 * Scales src by 1/val.
 *
 * @param[in] src The input object.
 * @param[in] val The scaling coefficient.
 */
template <typename T_Scalar, typename T_Object>
void operator/=(cla3p::dns::XxObject<T_Scalar,T_Object>& src, T_Scalar val)
{
	if(val == T_Scalar(0)) {
		throw cla3p::err::InvalidOp("Division by zero");
	}

	T_Scalar one(1);
	T_Scalar coeff = one / val;
	src.scale(coeff);
}

/*-------------------------------------------------*/

/**
 * @ingroup operators_mult
 * @brief Multiplies a matrix with a vector.
 *
 * Performs the operation:
 @verbatim
 ret = A * X
 @endverbatim
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The resulting vector.
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A, 
	const cla3p::dns::XxVector<T_Scalar,T_Vector>& X) 
{ 
	return cla3p::ops::mult(T_Scalar(1), cla3p::op_t::N, A, X); 
}

/**
 * @ingroup operators_perm
 * @brief Multiplies permutation matrix with a vector.
 *
 * Performs the operation:
 @verbatim
 ret = P * X
 @endverbatim
 *
 * @param[in] P The input permutation matrix.
 * @param[in] X The input vector.
 * @return The resulting vector.
 */
template <typename T_Int, typename T_Scalar, typename T_Vector>
T_Vector operator*(const cla3p::PxMatrix<T_Int>& P, const cla3p::dns::XxVector<T_Scalar,T_Vector>& X)
{
	return X.permuteLeft(P);
}

/*-------------------------------------------------*/

/**
 * @ingroup operators_perm
 * @brief Multiplies permutation matrix with a general matrix.
 *
 * Performs the operation:
 @verbatim
 ret = P * A
 @endverbatim
 *
 * @param[in] P The input permutation matrix.
 * @param[in] A The input matrix.
 * @return The resulting matrix.
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
T_Matrix operator*(const cla3p::PxMatrix<T_Int>& P, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A)
{
	return A.permuteLeft(P);
}

/**
 * @ingroup operators_perm
 * @brief Multiplies general matrix with a permutation matrix.
 *
 * Performs the operation:
 @verbatim
 ret = A * P
 @endverbatim
 *
 * @param[in] A The input matrix.
 * @param[in] P The input permutation matrix.
 * @return The resulting matrix.
 */

template <typename T_Int, typename T_Scalar, typename T_Matrix>
T_Matrix operator*(const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A, const cla3p::PxMatrix<T_Int>& P)
{
	return A.permuteRight(P);
}

/*-------------------------------------------------*/

/**
 * @ingroup operators_linsol
 * @brief Solves the linear system A * X = B.
 *
 * @param[in] A The lhs matrix.
 * @param[in] B The rhs vector.
 * @return The result of the operation (A^{-1} * B).
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
T_Vector operator/(const cla3p::dns::XxVector<T_Scalar,T_Vector>& B, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A)
{
	T_Vector ret = B.copy();
	ret /= A;
	return ret;
}

/**
 * @ingroup operators_linsol
 * @brief Solves the linear system A * X = B.
 *
 * @param[in] A The lhs matrix.
 * @param[in] B The rhs matrix.
 * @return The result of the operation (A^{-1} * B).
 */
template <typename T_Scalar, typename T_Matrix>
T_Matrix operator/(const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& B, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A)
{
	T_Matrix ret = B.copy();
	ret /= A;
	return ret;
}

/**
 * @ingroup operators_linsol
 * @brief Overwrites B with the solution (A^{-1} * B).
 *
 * @param[in] B The rhs vector.
 * @param[in] A The lhs matrix.
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
void operator/=(cla3p::dns::XxVector<T_Scalar,T_Vector>& B, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A)
{
	T_Vector rhs = B.rcopy();
	cla3p::dns::default_linear_solver<T_Matrix,T_Vector>(A.rcopy().get(), rhs);
}

/**
 * @ingroup operators_linsol
 * @brief Overwrites B with the solution (A^{-1} * B).
 *
 * @param[in] B The rhs matrix.
 * @param[in] A The lhs matrix.
 */
template <typename T_Scalar, typename T_Matrix>
void operator/=(cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& B, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& A)
{
	T_Matrix rhs = B.rcopy();
	cla3p::dns::default_linear_solver<T_Matrix,T_Matrix>(A.rcopy().get(), rhs);
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_HPP_
