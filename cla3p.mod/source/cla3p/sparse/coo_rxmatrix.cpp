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
#include "cla3p/sparse/coo_rxmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace coo {
/*-------------------------------------------------*/
#define RxMatrixTmpl RxMatrix<T_Int,T_Scalar>
#define RxMatrixTlst template <typename T_Int, typename T_Scalar>
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
	: RxMatrixTmpl::XxMatrix(nr, nc, nz, pr)
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::~RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
const RxMatrixTmpl& RxMatrixTmpl::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxMatrixTmpl
#undef RxMatrixTlst
/*-------------------------------------------------*/
template class RxMatrix<int_t,real_t>;
template class RxMatrix<int_t,real4_t>;
/*-------------------------------------------------*/
} // namespace coo
} // namespace cla3p
/*-------------------------------------------------*/

