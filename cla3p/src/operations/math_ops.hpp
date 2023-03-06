#ifndef CLA3P_MATH_OPS_HPP_
#define CLA3P_MATH_OPS_HPP_

#include "../types.hpp"
#include "../dense.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup math_addition_group
 * @brief Vector update.
 *
 * Performs the operation trg += alpha * src.
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] src The input vector.
 * @param[in,out] trg The vector to be updated.
 *
 * @{
 */
void update(int_t      alpha, const dns::RiVector& src, dns::RiVector& trg);
void update(real_t     alpha, const dns::RdVector& src, dns::RdVector& trg);
void update(real4_t    alpha, const dns::RfVector& src, dns::RfVector& trg);
void update(complex_t  alpha, const dns::CdVector& src, dns::CdVector& trg);
void update(complex8_t alpha, const dns::CfVector& src, dns::CfVector& trg);
/** @} */

/**
 * @ingroup math_addition_group
 * @brief Matrix update.
 *
 * Performs the operation trg += alpha * src.
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] src The input matrix.
 * @param[in,out] trg The matrix to be updated.
 *
 * @{
 */
void update(int_t      alpha, const dns::RiMatrix& src, dns::RiMatrix& trg);
void update(real_t     alpha, const dns::RdMatrix& src, dns::RdMatrix& trg);
void update(real4_t    alpha, const dns::RfMatrix& src, dns::RfMatrix& trg);
void update(complex_t  alpha, const dns::CdMatrix& src, dns::CdMatrix& trg);
void update(complex8_t alpha, const dns::CfMatrix& src, dns::CfMatrix& trg);
/** @} */

/**
 * @ingroup math_addition_group
 * @brief Vector sum.
 *
 * Performs the operation trg = alpha * srcA + beta * srcB.
 *
 * @param[in] alpha The scaling coefficient for srcA.
 * @param[in] srcA The first input vector.
 * @param[in] beta The scaling coefficient for srcB.
 * @param[in] srcB The second input vector.
 * @return The resulting vector.
 *
 * @{
 */
dns::RiVector add(int_t      alpha, const dns::RiVector& srcA, int_t      beta, const dns::RiVector& srcB);
dns::RdVector add(real_t     alpha, const dns::RdVector& srcA, real_t     beta, const dns::RdVector& srcB);
dns::RfVector add(real4_t    alpha, const dns::RfVector& srcA, real4_t    beta, const dns::RfVector& srcB);
dns::CdVector add(complex_t  alpha, const dns::CdVector& srcA, complex_t  beta, const dns::CdVector& srcB);
dns::CfVector add(complex8_t alpha, const dns::CfVector& srcA, complex8_t beta, const dns::CfVector& srcB);
/** @} */

/**
 * @ingroup math_addition_group
 * @brief Matrix sum.
 *
 * Performs the operation trg = alpha * srcA + beta * srcB.
 *
 * @param[in] alpha The scaling coefficient for srcA.
 * @param[in] srcA The first input matrix.
 * @param[in] beta The scaling coefficient for srcB.
 * @param[in] srcB The second input matrix.
 * @return The resulting matrix.
 *
 * @{
 */
dns::RiMatrix add(int_t      alpha, const dns::RiMatrix& srcA, int_t      beta, const dns::RiMatrix& srcB);
dns::RdMatrix add(real_t     alpha, const dns::RdMatrix& srcA, real_t     beta, const dns::RdMatrix& srcB);
dns::RfMatrix add(real4_t    alpha, const dns::RfMatrix& srcA, real4_t    beta, const dns::RfMatrix& srcB);
dns::CdMatrix add(complex_t  alpha, const dns::CdMatrix& srcA, complex_t  beta, const dns::CdMatrix& srcB);
dns::CfMatrix add(complex8_t alpha, const dns::CfMatrix& srcA, complex8_t beta, const dns::CfMatrix& srcB);
/** @} */

/**
 * @ingroup math_matvec_group
 * @brief Updates a vector with a matrix vector product.
 *
 * Performs the operation trg += alpha * opA(srcA) * srcX.
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @param[in,out] trg The vector to be updated.
 *
 * @{
 */
void mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const dns::RiVector& srcX, dns::RiVector& trg);
void mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX, dns::RdVector& trg);
void mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX, dns::RfVector& trg);
void mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX, dns::CdVector& trg);
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX, dns::CfVector& trg);
/** @} */

/**
 * @ingroup math_matvec_group
 * @brief Creates a vector from a matrix vector product.
 *
 * Performs the operation trg = alpha * opA(srcA) * srcX.
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @return The resulting vector.
 *
 * @{
 */
dns::RiVector mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const dns::RiVector& srcX);
dns::RdVector mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX);
dns::RfVector mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX);
dns::CdVector mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX);
dns::CfVector mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX);
/** @} */

/**
 * @ingroup math_ge_matmat_group
 * @brief Updates a general matrix with a general matrix matrix product.
 *
 * Performs the operation trg += alpha * opA(srcA) * opB(srcB).
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA.
 * @param[in] srcA The input general matrix.
 * @param[in] opB The operation to be performed for matrix srcB.
 * @param[in] srcB The input general matrix.
 * @param[in,out] trg The matrix to be updated.
 *
 * @{
 */
void mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const Operation& opB, const dns::RiMatrix& srcB, dns::RiMatrix& trg);
void mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB, dns::RdMatrix& trg);
void mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB, dns::RfMatrix& trg);
void mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB, dns::CdMatrix& trg);
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const Operation& opB, const dns::CfMatrix& srcB, dns::CfMatrix& trg);
/** @} */

/**
 * @ingroup math_ge_matmat_group
 * @brief Creates a general matrix from a general matrix matrix product.
 *
 * Performs the operation trg = alpha * opA(srcA) * opB(srcB).
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix srcA.
 * @param[in] srcA The input general matrix.
 * @param[in] opB The operation to be performed for matrix srcB.
 * @param[in] srcB The input general matrix.
 * @return The resulting matrix.
 *
 * @{
 */
dns::RiMatrix mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const Operation& opB, const dns::RiMatrix& srcB);
dns::RdMatrix mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB);
dns::RfMatrix mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB);
dns::CdMatrix mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB);
dns::CfMatrix mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const Operation& opB, const dns::CfMatrix& srcB);
/** @} */

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
