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

// this file inc
#include "cla3p/proxies/mkl_pardiso_proxy.hpp"

// system

// 3rd
#include <mkl.h>

// cla3p

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
		void *x)
{
	int_t error = 0;

	pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n, 
			values, colptr, rowidx, perm, &nrhs, iparm, 
			&msglvl, b, x, &error);

	return error;
}
/*-------------------------------------------------*/
std::string pardisoGetErrorMsg(int_t error)
{
	std::string ret;

	switch(error) {

		case 0:
			ret = "Success";
			break;

		case -1:
			ret = "Input inconsistent";
			break;

		case -2:
			ret = "Not enough memory";
			break;

		case -3:
			ret = "Reordering problem";
			break;

		case -4:
			ret = "Zero pivot, numerical factorization or iterative refinement problem";
			break;

		case -5:
			ret = "Unclassified (internal) error";
			break;

		case -6:
			ret = "Reordering failed";
			break;

		case -7:
			ret = "Diagonal matrix is singular";
			break;

		case -8:
			ret = "32-bit integer overflow problem";
			break;

		case -9:
			ret = "Not enough memory for OOC";
			break;

		case -10:
			ret = "Problems with opening OOC temporary files";
			break;

		case -11:
			ret = "Read/write problems with the OOC data file";
			break;

		default:
			ret = "Unknown Error";

	} // error switch

	return ret;
}
/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/
