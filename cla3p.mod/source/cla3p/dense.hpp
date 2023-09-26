#ifndef CLA3P_DENSE_HPP_
#define CLA3P_DENSE_HPP_

#include "cla3p/dense/dns_rxvector.hpp"
#include "cla3p/dense/dns_cxvector.hpp"
#include "cla3p/dense/dns_rxmatrix.hpp"
#include "cla3p/dense/dns_cxmatrix.hpp"

namespace cla3p {
namespace dns {

/**
 * @ingroup dense_vectors
 * @brief Double precision real vector.
 */
using RdVector = RxVector<real_t>;

/**
 * @ingroup dense_vectors
 * @brief Single precision real vector.
 */
using RfVector = RxVector<real4_t>;

/**
 * @ingroup dense_vectors
 * @brief Double precision complex vector.
 */
using CdVector = CxVector<complex_t>;

/**
 * @ingroup dense_vectors
 * @brief Single precision complex vector.
 */
using CfVector = CxVector<complex8_t>;

/**
 * @ingroup dense_matrices
 * @brief Double precision real matrix.
 */
using RdMatrix = RxMatrix<real_t>;

/**
 * @ingroup dense_matrices
 * @brief Single precision real matrix.
 */
using RfMatrix = RxMatrix<real4_t>;

/**
 * @ingroup dense_matrices
 * @brief Double precision complex matrix.
 */
using CdMatrix = CxMatrix<complex_t>;

/**
 * @ingroup dense_matrices
 * @brief Single precision complex matrix.
 */
using CfMatrix = CxMatrix<complex8_t>;

} // namespace dns
} // namespace cla3p

#endif // CLA3P_DENSE_HPP_
