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
#include "cla3p/linsol/lapack_llt.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/error/exceptions.hpp"

#include "cla3p/checks/decomp_llt_checks.hpp"
#include "cla3p/checks/solve_checks.hpp"
#include "cla3p/checks/lapack_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackLLt<T_Matrix>::LapackLLt()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackLLt<T_Matrix>::LapackLLt(uint_t n)
	: LapackBase<T_Matrix>(n)
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LapackLLt<T_Matrix>::~LapackLLt()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackLLt<T_Matrix>::decomposeFactor()
{
	llt_decomp_input_check(this->factor());

	int_t info = lapack::potrf(
			this->factor().prop().cuplo(), 
			this->factor().ncols(), 
			this->factor().values(), 
			this->factor().ld());
	
	this->setInfo(info);
	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LapackLLt<T_Matrix>::solveForRhs(T_Matrix& rhs) const
{
	if(this->factor().empty()) {
		throw err::InvalidOp("Decomposition stage is not performed");
	} // empty factor
	
	default_solve_input_check(this->factor().ncols(), rhs);
	
	int_t info = lapack::potrs(
			this->factor().prop().cuplo(), 
			this->factor().ncols(), 
			rhs.ncols(), 
			this->factor().values(), 
			this->factor().ld(), rhs.values(), rhs.ld());
	
	lapack_info_check(info);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LapackLLt<dns::RdMatrix>;
template class LapackLLt<dns::RfMatrix>;
template class LapackLLt<dns::CdMatrix>;
template class LapackLLt<dns::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

