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
 * @ingroup operators_addsub
 * @brief Updates an entity with another compatible entity.
 * @{
 */
void operator+=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src);
void operator+=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src);
void operator+=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src);
void operator+=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src);
void operator+=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src);

void operator+=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src);
void operator+=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src);
void operator+=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src);
void operator+=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src);
void operator+=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src);

void operator-=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src);
void operator-=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src);
void operator-=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src);
void operator-=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src);
void operator-=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src);

void operator-=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src);
void operator-=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src);
void operator-=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src);
void operator-=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src);
void operator-=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src);
/** @} */

/**
 * @ingroup operators_addsub
 * @brief Adds two compatible entities.
 * @{
 */
cla3p::dns::RiVector operator+(const cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB);
cla3p::dns::RdVector operator+(const cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB);
cla3p::dns::RfVector operator+(const cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB);
cla3p::dns::CdVector operator+(const cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB);
cla3p::dns::CfVector operator+(const cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB);
                                     
cla3p::dns::RiMatrix operator+(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB);
cla3p::dns::RdMatrix operator+(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB);
cla3p::dns::RfMatrix operator+(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB);
cla3p::dns::CdMatrix operator+(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB);
cla3p::dns::CfMatrix operator+(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB);
/** @} */

/**
 * @ingroup operators_addsub
 * @brief Subtracts two compatible entities.
 * @{
 */
cla3p::dns::RiVector operator-(const cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB);
cla3p::dns::RdVector operator-(const cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB);
cla3p::dns::RfVector operator-(const cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB);
cla3p::dns::CdVector operator-(const cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB);
cla3p::dns::CfVector operator-(const cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB);
                                     
cla3p::dns::RiMatrix operator-(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB);
cla3p::dns::RdMatrix operator-(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB);
cla3p::dns::RfMatrix operator-(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB);
cla3p::dns::CdMatrix operator-(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB);
cla3p::dns::CfMatrix operator-(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB);
/** @} */

/**
 * @ingroup operators_mult
 * @brief Multiplies two compatible entities.
 * @{
 */
cla3p::dns::RiVector operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiVector& srcX);
cla3p::dns::RdVector operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdVector& srcX);
cla3p::dns::RfVector operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfVector& srcX);
cla3p::dns::CdVector operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdVector& srcX);
cla3p::dns::CfVector operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfVector& srcX);
                                     
cla3p::dns::RiMatrix operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB);
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
cla3p::dns::RiVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RiVector& srcX);
cla3p::dns::RdVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RdVector& srcX);
cla3p::dns::RfVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RfVector& srcX);
cla3p::dns::CdVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CdVector& srcX);
cla3p::dns::CfVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CfVector& srcX);

cla3p::dns::RiMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RiMatrix& srcA);
cla3p::dns::RdMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RdMatrix& srcA);
cla3p::dns::RfMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RfMatrix& srcA);
cla3p::dns::CdMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CdMatrix& srcA);
cla3p::dns::CfMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CfMatrix& srcA);

cla3p::dns::RiMatrix operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::PermMatrix& srcP);
cla3p::dns::RdMatrix operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::PermMatrix& srcP);
cla3p::dns::RfMatrix operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::PermMatrix& srcP);
cla3p::dns::CdMatrix operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::PermMatrix& srcP);
cla3p::dns::CfMatrix operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::PermMatrix& srcP);

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
