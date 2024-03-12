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

#ifndef CLA3P_BULK_CSC_HPP_
#define CLA3P_BULK_CSC_HPP_

/**
 * @file
 */

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace csc {
/*-------------------------------------------------*/

template <typename T_Int>
void roll(uint_t n, T_Int *colptr);

template <typename T_Int>
void unroll(uint_t n, T_Int *colptr);

template <typename T_Int>
uint_t maxrlen(uint_t n, const T_Int *colptr);

template <typename T_Int>
void check(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx);

template <typename T_Int>
void sort(uint_t n, const T_Int *colptr, T_Int *rowidx);

template <typename T_Int, typename T_Scalar>
void sort(uint_t n, const T_Int *colptr, T_Int *rowidx, T_Scalar *values);

template <typename T_Int, typename T_Scalar>
std::string print_to_string(uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, uint_t nsd = 3);

template <typename T_Int, typename T_Scalar>
void print(uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, uint_t nsd = 3);

template <typename T_Int, typename T_Scalar>
void transpose(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, T_Scalar coeff = 1);

template <typename T_Int, typename T_Scalar>
void conjugate_transpose(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, T_Scalar coeff = 1);

template <typename T_Int>
void uplo2ge_colptr(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, T_Int *colptr_out);

template <typename T_Int, typename T_Scalar>
void sy2ge(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out);

template <typename T_Int, typename T_Scalar>
void he2ge(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out);

template <typename T_Int, typename T_Scalar>
void remove_duplicates(uint_t n, T_Int *colptr, T_Int *rowidx, T_Scalar *values, dup_t op);

template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type 
norm_one(prop_t ptype, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values);

template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type 
norm_inf(prop_t ptype, uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values);

template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type 
norm_max(uint_t n, const T_Int *colptr, const T_Scalar *values);

template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type 
norm_fro(prop_t ptype, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values);

template <typename T_Int, typename T_Scalar>
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, 
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *P, const int_t *Q);

/*-------------------------------------------------*/
} // namespace csc
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_CSC_HPP_
