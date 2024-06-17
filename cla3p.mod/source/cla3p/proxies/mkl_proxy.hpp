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

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

std::string version();

void* malloc(std::size_t size);
void* calloc(std::size_t size, std::size_t nmemb);
void* realloc(void *ptr, std::size_t nmemb);
void free(void *ptr);

nint_t get_dynamic();
nint_t get_max_threads();
void set_num_threads(nint_t numThreads);
nint_t set_num_threads_local(nint_t numThreads);

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

/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_PROXY_HPP_
