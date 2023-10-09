#ifndef CLA3P_OPERATORS_HPP_
#define CLA3P_OPERATORS_HPP_

/**
 * @file
 * Global math operator definitions
 */

#include "cla3p/operations/math_ops.hpp"

/*-------------------------------------------------*/
namespace cla3p {
template <typename T_Int> class PxMatrix;
namespace dns {
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup operators_mult
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
	ret.scale(val);
	return ret; 
}

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

#endif // CLA3P_OPERATORS_HPP_
