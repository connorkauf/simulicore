#ifndef CLA3P_DENSE2_HPP_
#define CLA3P_DENSE2_HPP_

#include "dense/dns_xxvector.hpp"

namespace cla3p {

/**
 * @ingroup dense_vectors
 * @brief Double precision real vector.
 */
using RdVector = XxObject<real_t,real_t>;

/**
 * @ingroup dense_vectors
 * @brief Single precision real vector.
 */
using RfVector = XxObject<real4_t,real4_t>;

} // namespace cla3p

#endif // CLA3P_DENSE2_HPP_
