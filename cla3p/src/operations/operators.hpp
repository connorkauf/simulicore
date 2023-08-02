#ifndef CLA3P_OPERATORS_HPP_
#define CLA3P_OPERATORS_HPP_

/**
 * @file
 * Global math operator definitions
 */

#include "../operations/math_ops.hpp"

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
 * @brief Multiplies a matrix with a vector.
 *
 * Performs the operation:
 @verbatim
 trg = srcA * srcX
 @endverbatim
 *
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @return The resulting vector.
 */
template <typename T_Scalar, typename T_Vector, typename T_Matrix>
cla3p::dns::XxVector<T_Scalar,T_Vector> operator*(
		const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& srcA, 
		const cla3p::dns::XxVector<T_Scalar,T_Vector>& srcX) 
{ 
	return cla3p::ops::mult(T_Scalar(1), cla3p::noOp(), srcA, srcX); 
}

/**
 * @ingroup operators_perm
 * @brief Multiplies permutation matrix with a vector.
 *
 * Performs the operation:
 @verbatim
 trg = srcP * srcX
 @endverbatim
 *
 * @param[in] srcP The input permutation matrix.
 * @param[in] srcX The input vector.
 * @return The resulting vector.
 */
template <typename T_Int, typename T_Scalar, typename T_Vector>
T_Vector operator*(const cla3p::PxMatrix<T_Int>& srcP, const cla3p::dns::XxVector<T_Scalar,T_Vector>& srcX)
{
	return srcX.permuteLeft(srcP);
}

/**
 * @ingroup operators_perm
 * @brief Multiplies permutation matrix with a general matrix.
 *
 * Performs the operation:
 @verbatim
 trg = srcP * srcA
 @endverbatim
 *
 * @param[in] srcP The input permutation matrix.
 * @param[in] srcA The input matrix.
 * @return The resulting matrix.
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
T_Matrix operator*(const cla3p::PxMatrix<T_Int>& srcP, const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& srcA)
{
	return srcA.permuteLeft(srcP);
}

/**
 * @ingroup operators_perm
 * @brief Multiplies general matrix with a permutation matrix.
 *
 * Performs the operation:
 @verbatim
 trg = srcA * srcP
 @endverbatim
 *
 * @param[in] srcA The input matrix.
 * @param[in] srcP The input permutation matrix.
 * @return The resulting matrix.
 */

template <typename T_Int, typename T_Scalar, typename T_Matrix>
T_Matrix operator*(const cla3p::dns::XxMatrix<T_Scalar,T_Matrix>& srcA, const cla3p::PxMatrix<T_Int>& srcP)
{
	return srcA.permuteRight(srcP);
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_HPP_
