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
#include "cla3p/algebra/operators_multmv.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra/functional_multmv.hpp"

/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
	using T_Scalar = typename T_Matrix::value_type;
	T_Vector ret(A.nrows());
	ret = 0;
	cla3p::ops::mult(T_Scalar(1), cla3p::op_t::N, A, X, ret);
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_mv(T_Mat, T_Vec) \
template T_Vec operator*( \
		const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		const cla3p::dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_op_mv(cla3p::csc::RdMatrix, cla3p::dns::RdVector);
instantiate_op_mv(cla3p::csc::RfMatrix, cla3p::dns::RfVector);
instantiate_op_mv(cla3p::csc::CdMatrix, cla3p::dns::CdVector);
instantiate_op_mv(cla3p::csc::CfMatrix, cla3p::dns::CfVector);
#undef instantiate_op_mv
/*-------------------------------------------------*/
