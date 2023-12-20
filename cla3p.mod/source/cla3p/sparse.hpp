/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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

#ifndef CLA3P_SPARSE_HPP_
#define CLA3P_SPARSE_HPP_

#include "cla3p/sparse/csc_rxmatrix.hpp"
#include "cla3p/sparse/csc_cxmatrix.hpp"
#include "cla3p/sparse/coo_rxmatrix.hpp"
#include "cla3p/sparse/coo_cxmatrix.hpp"

namespace cla3p {
namespace csc {

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision real matrix.
 */
using RdMatrix = RxMatrix<int_t,real_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision real matrix.
 */
using RfMatrix = RxMatrix<int_t,real4_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision complex matrix.
 */
using CdMatrix = CxMatrix<int_t,complex_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision complex matrix.
 */
using CfMatrix = CxMatrix<int_t,complex8_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision real matrix (unsigned indeces).
 */
using RdUMatrix = RxMatrix<uint_t,real_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision real matrix (unsigned indeces).
 */
using RfUMatrix = RxMatrix<uint_t,real4_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision complex matrix (unsigned indeces).
 */
using CdUMatrix = CxMatrix<uint_t,complex_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision complex matrix (unsigned indeces).
 */
using CfUMatrix = CxMatrix<uint_t,complex8_t>;

} // namespace csc
} // namespace cla3p


namespace cla3p {
namespace coo {

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision real matrix.
 */
using RdMatrix = RxMatrix<int_t,real_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision real matrix.
 */
using RfMatrix = RxMatrix<int_t,real4_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision complex matrix.
 */
using CdMatrix = CxMatrix<int_t,complex_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision complex matrix.
 */
using CfMatrix = CxMatrix<int_t,complex8_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision real matrix (unsigned indeces).
 */
using RdUMatrix = RxMatrix<uint_t,real_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision real matrix (unsigned indeces).
 */
using RfUMatrix = RxMatrix<uint_t,real4_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Double precision complex matrix (unsigned indeces).
 */
using CdUMatrix = CxMatrix<uint_t,complex_t>;

/**
 * @ingroup module_index_matrices_sparse
 * @brief Single precision complex matrix (unsigned indeces).
 */
using CfUMatrix = CxMatrix<uint_t,complex8_t>;

} // namespace coo
} // namespace cla3p

#endif // CLA3P_SPARSE_HPP_
