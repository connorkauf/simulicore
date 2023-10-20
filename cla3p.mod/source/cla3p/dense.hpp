/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CLA3P_DENSE_HPP_
#define CLA3P_DENSE_HPP_

#include "cla3p/dense/dns_rxvector.hpp"
#include "cla3p/dense/dns_cxvector.hpp"
#include "cla3p/dense/dns_rxmatrix.hpp"
#include "cla3p/dense/dns_cxmatrix.hpp"

namespace cla3p {
namespace dns {

/**
 * @ingroup module_index_vectors_dense
 * @brief Double precision real vector.
 */
using RdVector = RxVector<real_t>;

/**
 * @ingroup module_index_vectors_dense
 * @brief Single precision real vector.
 */
using RfVector = RxVector<real4_t>;

/**
 * @ingroup module_index_vectors_dense
 * @brief Double precision complex vector.
 */
using CdVector = CxVector<complex_t>;

/**
 * @ingroup module_index_vectors_dense
 * @brief Single precision complex vector.
 */
using CfVector = CxVector<complex8_t>;

/**
 * @ingroup module_index_matrices_dense
 * @brief Double precision real matrix.
 */
using RdMatrix = RxMatrix<real_t>;

/**
 * @ingroup module_index_matrices_dense
 * @brief Single precision real matrix.
 */
using RfMatrix = RxMatrix<real4_t>;

/**
 * @ingroup module_index_matrices_dense
 * @brief Double precision complex matrix.
 */
using CdMatrix = CxMatrix<complex_t>;

/**
 * @ingroup module_index_matrices_dense
 * @brief Single precision complex matrix.
 */
using CfMatrix = CxMatrix<complex8_t>;

} // namespace dns
} // namespace cla3p

#endif // CLA3P_DENSE_HPP_
