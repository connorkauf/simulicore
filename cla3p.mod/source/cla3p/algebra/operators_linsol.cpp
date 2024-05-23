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
#include "cla3p/linsol/lapack_auto.hpp"
#include "cla3p/linsol/pardiso_auto.hpp"

/*-------------------------------------------------*/
template <typename T_Matrix, typename T_Vector>
T_Vector operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B)
{
	T_Vector ret = B.self();
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
	T_Matrix ret = B.self();
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

		T_Vector& rhs = B.self();
		cla3p::LapackAuto<T_Matrix> autoSolver;
		autoSolver.decompose(A.self());
		autoSolver.solve(rhs);

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

		T_Matrix& rhs = B.self();
		cla3p::LapackAuto<T_Matrix> autoSolver;
		autoSolver.decompose(A.self());
		autoSolver.solve(rhs);

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
template <typename T_Matrix, typename T_Vector>
T_Vector operator/(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B)
{
	T_Vector ret = B.self();
	ret /= A;
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Mat, T_Vec) \
template T_Vec operator/( \
		const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		const cla3p::dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_op_linsol(cla3p::csc::RdMatrix, cla3p::dns::RdVector);
instantiate_op_linsol(cla3p::csc::RfMatrix, cla3p::dns::RfVector);
instantiate_op_linsol(cla3p::csc::CdMatrix, cla3p::dns::CdVector);
instantiate_op_linsol(cla3p::csc::CfMatrix, cla3p::dns::CfVector);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_CscMatrix, typename T_DnsMatrix>
T_DnsMatrix operator/(
		const cla3p::csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A,
		const cla3p::dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B)
{
	T_DnsMatrix ret = B.self();
	ret /= A;
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_CscMat,T_DnsMat) \
template T_DnsMat operator/( \
		const cla3p::csc::XxMatrix<typename T_CscMat::index_type,typename T_CscMat::value_type,T_CscMat>&, \
		const cla3p::dns::XxMatrix<typename T_DnsMat::value_type,T_DnsMat>&)
instantiate_op_linsol(cla3p::csc::RdMatrix,cla3p::dns::RdMatrix);
instantiate_op_linsol(cla3p::csc::RfMatrix,cla3p::dns::RfMatrix);
instantiate_op_linsol(cla3p::csc::CdMatrix,cla3p::dns::CdMatrix);
instantiate_op_linsol(cla3p::csc::CfMatrix,cla3p::dns::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void operator/=(
		cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A)
{
	T_Vector& sol = B.self();
	T_Vector rhs = sol;
	cla3p::PardisoAuto<T_Matrix> autoSolver;
	autoSolver.analysis(A.self());
	autoSolver.decompose(A.self());
	autoSolver.solve(rhs,sol);
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_Vec, T_Mat) \
template void operator/=( \
		cla3p::dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
		const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_op_linsol(cla3p::dns::RdVector, cla3p::csc::RdMatrix);
instantiate_op_linsol(cla3p::dns::RfVector, cla3p::csc::RfMatrix);
instantiate_op_linsol(cla3p::dns::CdVector, cla3p::csc::CdMatrix);
instantiate_op_linsol(cla3p::dns::CfVector, cla3p::csc::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
template <typename T_DnsMatrix, typename T_CscMatrix>
void operator/=(
		cla3p::dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B,
		const cla3p::csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A)
{
	T_DnsMatrix& sol = B.self();
	T_DnsMatrix rhs = sol;
	cla3p::PardisoAuto<T_CscMatrix> autoSolver;
	autoSolver.analysis(A.self());
	autoSolver.decompose(A.self());
	autoSolver.solve(rhs,sol);
}
/*-------------------------------------------------*/
#define instantiate_op_linsol(T_DnsMat,T_CscMat) \
template void operator/=( \
		cla3p::dns::XxMatrix<typename T_DnsMat::value_type,T_DnsMat>&, \
		const cla3p::csc::XxMatrix<typename T_CscMat::index_type,typename T_CscMat::value_type,T_CscMat>&)
instantiate_op_linsol(cla3p::dns::RdMatrix,cla3p::csc::RdMatrix);
instantiate_op_linsol(cla3p::dns::RfMatrix,cla3p::csc::RfMatrix);
instantiate_op_linsol(cla3p::dns::CdMatrix,cla3p::csc::CdMatrix);
instantiate_op_linsol(cla3p::dns::CfMatrix,cla3p::csc::CfMatrix);
#undef instantiate_op_linsol
/*-------------------------------------------------*/
