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

#ifndef CLA3P_MKL_PROXY_HPP_
#define CLA3P_MKL_PROXY_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

std::string version();

#define omatcopy_macro(typeout, typein) \
typeout omatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, \
		const typein *a, bulk_t lda, \
		      typein *b, bulk_t ldb)
omatcopy_macro(void, real_t);
omatcopy_macro(void, real4_t);
omatcopy_macro(void, complex_t);
omatcopy_macro(void, complex8_t);
#undef omatcopy_macro

#define omatcopy_macro(typeout, typein) \
typeout omatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, \
		const typein *a, bulk_t lda, bulk_t stridea, \
		      typein *b, bulk_t ldb, bulk_t strideb)
omatcopy_macro(void, real_t);
omatcopy_macro(void, real4_t);
omatcopy_macro(void, complex_t);
omatcopy_macro(void, complex8_t);
#undef omatcopy_macro

#define imatcopy_macro(typeout, typein) \
typeout imatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, typein *a, bulk_t lda, bulk_t ldb)
imatcopy_macro(void, real_t);
imatcopy_macro(void, real4_t);
imatcopy_macro(void, complex_t);
imatcopy_macro(void, complex8_t);
#undef imatcopy_macro

#define omatadd_macro(typeout, typein) \
typeout omatadd(char ordering, char transa, char transb, bulk_t rows, bulk_t cols, \
		typein alpha, const typein *A, bulk_t lda, \
		typein beta , const typein *B, bulk_t ldb, typein *C, bulk_t ldc)
omatadd_macro(void, real_t);
omatadd_macro(void, real4_t);
omatadd_macro(void, complex_t);
omatadd_macro(void, complex8_t);
#undef omatadd_macro

template <typename T_Scalar>
void csc_add(uint_t m, uint_t n, T_Scalar alpha,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC);

template <typename T_Scalar>
void csc_mv(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		const T_Scalar* x, T_Scalar beta, T_Scalar *y);

template <typename T_Scalar>
void csc_mm(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		uint_t k, const T_Scalar* b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc);

/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_PROXY_HPP_
