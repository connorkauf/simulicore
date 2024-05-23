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

#ifndef CLA3P_MKL_PARDISO_PROXY_HPP_
#define CLA3P_MKL_PARDISO_PROXY_HPP_

/**
 * @file
 */

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/

int_t pardisoDriver(
		void *pt, 
		int_t maxfct, 
		int_t mnum, 
		int_t mtype,
		int_t phase, 
		int_t n, 
		const void *values, 
		const int_t *colptr,
		const int_t *rowidx, 
		int_t *perm, 
		int_t nrhs, 
		int_t *iparm,
		int_t msglvl, 
		void *b,
		void *x);

std::string pardisoGetErrorMsg(int_t error);

/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_PARDISO_HPP_
