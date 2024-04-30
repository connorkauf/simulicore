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
#include "cla3p/algebra/operators_linsol.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/algebra/functional_multmv.hpp"
#include "cla3p/algebra/functional_multmm.hpp"
#include "cla3p/linsol/dns_auto_lsolver.hpp"

/*-------------------------------------------------*/
template <typename T_Matrix, typename T_Vector>
T_Vector operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B)
{
	T_Vector ret = B.copy();
	ret /= A;
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Mat, T_Vec) \
template T_Vec operator/( \
		const cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
		const cla3p::dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_op_linsol(cla3p::dns::RdMatrix, cla3p::dns::RdVector);
instantiate_op_linsol(cla3p::dns::RfMatrix, cla3p::dns::RfVector);
instantiate_op_linsol(cla3p::dns::CdMatrix, cla3p::dns::CdVector);
instantiate_op_linsol(cla3p::dns::CfMatrix, cla3p::dns::CfVector);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	T_Matrix ret = B.copy();
	ret /= A;
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Mat) \
template T_Mat operator/( \
		const cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
		const cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_op_linsol(cla3p::dns::RdMatrix);
instantiate_op_linsol(cla3p::dns::RfMatrix);
instantiate_op_linsol(cla3p::dns::CdMatrix);
instantiate_op_linsol(cla3p::dns::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void operator/=(
		cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	if(A.prop().isTriangular() && A.nrows() == A.ncols()) {

		cla3p::ops::trisol(cla3p::op_t::N, A, B);

	} else {

		T_Vector rhs = B.rcopy();
		cla3p::dns::default_linear_solver<T_Matrix,T_Vector>(A.self(), rhs);

	} // property case
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Vec, T_Mat) \
template void operator/=( \
		cla3p::dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
		const cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_op_linsol(cla3p::dns::RdVector, cla3p::dns::RdMatrix);
instantiate_op_linsol(cla3p::dns::RfVector, cla3p::dns::RfMatrix);
instantiate_op_linsol(cla3p::dns::CdVector, cla3p::dns::CdMatrix);
instantiate_op_linsol(cla3p::dns::CfVector, cla3p::dns::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_Matrix>
void operator/=(
		cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	using T_Scalar = typename T_Matrix::value_type;

	if(A.prop().isTriangular() && A.nrows() == A.ncols()) {

		cla3p::ops::trisol(T_Scalar(1), cla3p::op_t::N, A, B);

	} else {

		T_Matrix rhs = B.rcopy();
		cla3p::dns::default_linear_solver<T_Matrix,T_Matrix>(A.self(), rhs);

	} // property case
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Mat) \
template void operator/=( \
		cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
		const cla3p::dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_op_linsol(cla3p::dns::RdMatrix);
instantiate_op_linsol(cla3p::dns::RfMatrix);
instantiate_op_linsol(cla3p::dns::CdMatrix);
instantiate_op_linsol(cla3p::dns::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
