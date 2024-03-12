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

#ifndef CLA3P_BULK_DNS_IO_HPP_
#define CLA3P_BULK_DNS_IO_HPP_

/**
 * @file
 */

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
std::string print_to_string(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);

void print(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t nsd = 0, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);
void print(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, uint_t nsd = 3, uint_t line_maxlen = 128);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_IO_HPP_
