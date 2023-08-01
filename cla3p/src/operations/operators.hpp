#ifndef CLA3P_OPERATORS_HPP_
#define CLA3P_OPERATORS_HPP_

/**
 * @file
 * Global math operator definitions
 */

#include "../types.hpp"
#include "../dense.hpp"
#include "../perms.hpp"

/*-------------------------------------------------*/

/**
 * @ingroup operators_mult
 * @brief Multiplies two compatible entities.
 * @{
 */
cla3p::dns::RdVector operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdVector& srcX);
cla3p::dns::RfVector operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfVector& srcX);
cla3p::dns::CdVector operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdVector& srcX);
cla3p::dns::CfVector operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfVector& srcX);
                                     
cla3p::dns::RdMatrix operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB);
cla3p::dns::RfMatrix operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB);
cla3p::dns::CdMatrix operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB);
cla3p::dns::CfMatrix operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB);
/** @} */

/**
 * @ingroup operators_perm
 * @brief Multiplies permutation matrix with a compatible entity.
 * @{
 */
cla3p::dns::RdVector operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::RdVector& srcX);
cla3p::dns::RfVector operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::RfVector& srcX);
cla3p::dns::CdVector operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::CdVector& srcX);
cla3p::dns::CfVector operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::CfVector& srcX);

cla3p::dns::RdMatrix operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::RdMatrix& srcA);
cla3p::dns::RfMatrix operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::RfMatrix& srcA);
cla3p::dns::CdMatrix operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::CdMatrix& srcA);
cla3p::dns::CfMatrix operator*(const cla3p::PiMatrix& srcP, const cla3p::dns::CfMatrix& srcA);

cla3p::dns::RdMatrix operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::PiMatrix& srcP);
cla3p::dns::RfMatrix operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::PiMatrix& srcP);
cla3p::dns::CdMatrix operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::PiMatrix& srcP);
cla3p::dns::CfMatrix operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::PiMatrix& srcP);

/** @} */

/**
 * @ingroup operators_lsol
 * @brief Performs linear solution X = A^{-1} * B.
 * @{
 */

cla3p::dns::RdVector operator/(const cla3p::dns::RdVector& srcX, const cla3p::dns::RdMatrix& srcA);
cla3p::dns::RfVector operator/(const cla3p::dns::RfVector& srcX, const cla3p::dns::RfMatrix& srcA);
cla3p::dns::CdVector operator/(const cla3p::dns::CdVector& srcX, const cla3p::dns::CdMatrix& srcA);
cla3p::dns::CfVector operator/(const cla3p::dns::CfVector& srcX, const cla3p::dns::CfMatrix& srcA);

cla3p::dns::RdMatrix operator/(const cla3p::dns::RdMatrix& srcX, const cla3p::dns::RdMatrix& srcA);
cla3p::dns::RfMatrix operator/(const cla3p::dns::RfMatrix& srcX, const cla3p::dns::RfMatrix& srcA);
cla3p::dns::CdMatrix operator/(const cla3p::dns::CdMatrix& srcX, const cla3p::dns::CdMatrix& srcA);
cla3p::dns::CfMatrix operator/(const cla3p::dns::CfMatrix& srcX, const cla3p::dns::CfMatrix& srcA);

/** @} */

/**
 * @ingroup operators_lsol
 * @brief Overwrites srcX with the solution A^{-1} * srcX.
 * @{
 */

void operator/=(cla3p::dns::RdVector& srcX, const cla3p::dns::RdMatrix& srcA);
void operator/=(cla3p::dns::RfVector& srcX, const cla3p::dns::RfMatrix& srcA);
void operator/=(cla3p::dns::CdVector& srcX, const cla3p::dns::CdMatrix& srcA);
void operator/=(cla3p::dns::CfVector& srcX, const cla3p::dns::CfMatrix& srcA);

void operator/=(cla3p::dns::RdMatrix& srcX, const cla3p::dns::RdMatrix& srcA);
void operator/=(cla3p::dns::RfMatrix& srcX, const cla3p::dns::RfMatrix& srcA);
void operator/=(cla3p::dns::CdMatrix& srcX, const cla3p::dns::CdMatrix& srcA);
void operator/=(cla3p::dns::CfMatrix& srcX, const cla3p::dns::CfMatrix& srcA);

/** @} */

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_HPP_
