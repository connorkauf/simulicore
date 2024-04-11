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
#include "cla3p/algebra/operators_multmm.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra/functional_multmm.hpp"

/*-------------------------------------------------*/
template <typename T_CscMatrix, typename T_DnsMatrix>
T_DnsMatrix operator*(
		const cla3p::csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A,
		const cla3p::dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B)
{
	using T_Scalar = typename T_CscMatrix::value_type;
	T_DnsMatrix ret(A.nrows(), B.ncols());
	ret = 0;
	cla3p::ops::mult(T_Scalar(1), cla3p::op_t::N, A, B, ret);
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_mm(T_Csc, T_Dns) \
template T_Dns operator*( \
		const cla3p::csc::XxMatrix<typename T_Csc::index_type,typename T_Csc::value_type,T_Csc>&, \
		const cla3p::dns::XxMatrix<typename T_Dns::value_type,T_Dns>&)
instantiate_op_mm(cla3p::csc::RdMatrix, cla3p::dns::RdMatrix);
instantiate_op_mm(cla3p::csc::RfMatrix, cla3p::dns::RfMatrix);
instantiate_op_mm(cla3p::csc::CdMatrix, cla3p::dns::CdMatrix);
instantiate_op_mm(cla3p::csc::CfMatrix, cla3p::dns::CfMatrix);
#undef instantiate_op_mm
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix operator*(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	using T_Scalar = typename T_Matrix::value_type;
	return cla3p::ops::mult(T_Scalar(1), cla3p::op_t::N, A, cla3p::op_t::N, B);
}
/*-------------------------------------------------*/
#define instantiate_op_mm(T_Mat) \
template T_Mat operator*( \
		const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_op_mm(cla3p::csc::RdMatrix);
instantiate_op_mm(cla3p::csc::RfMatrix);
instantiate_op_mm(cla3p::csc::CdMatrix);
instantiate_op_mm(cla3p::csc::CfMatrix);
#undef instantiate_op_mm
/*-------------------------------------------------*/
