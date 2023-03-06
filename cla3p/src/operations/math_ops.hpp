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
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] alpha The scaling coefficient.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @param[in,out] trg The vector to be updated.
 *
 * @{
 */
void mult(const Operation& opA, int_t      alpha, const dns::RiMatrix& srcA, const dns::RiVector& srcX, dns::RiVector& trg);
void mult(const Operation& opA, real_t     alpha, const dns::RdMatrix& srcA, const dns::RdVector& srcX, dns::RdVector& trg);
void mult(const Operation& opA, real4_t    alpha, const dns::RfMatrix& srcA, const dns::RfVector& srcX, dns::RfVector& trg);
void mult(const Operation& opA, complex_t  alpha, const dns::CdMatrix& srcA, const dns::CdVector& srcX, dns::CdVector& trg);
void mult(const Operation& opA, complex8_t alpha, const dns::CfMatrix& srcA, const dns::CfVector& srcX, dns::CfVector& trg);
/** @} */

/**
 * @ingroup math_matvec_group
 * @brief Creates a vector with a matrix vector product.
 *
 * Performs the operation trg = alpha * opA(srcA) * srcX.
 *
 * @param[in] opA The operation to be performed for matrix srcA. If srcA is symmetric or hermitian, opA is ignored.
 * @param[in] alpha The scaling coefficient.
 * @param[in] srcA The input matrix.
 * @param[in] srcX The input vector.
 * @return The resulting vector.
 *
 * @{
 */
dns::RiVector mult(const Operation& opA, int_t      alpha, const dns::RiMatrix& srcA, const dns::RiVector& srcX);
dns::RdVector mult(const Operation& opA, real_t     alpha, const dns::RdMatrix& srcA, const dns::RdVector& srcX);
dns::RfVector mult(const Operation& opA, real4_t    alpha, const dns::RfMatrix& srcA, const dns::RfVector& srcX);
dns::CdVector mult(const Operation& opA, complex_t  alpha, const dns::CdMatrix& srcA, const dns::CdVector& srcX);
dns::CfVector mult(const Operation& opA, complex8_t alpha, const dns::CfMatrix& srcA, const dns::CfVector& srcX);
/** @} */

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
