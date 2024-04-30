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
#include "cla3p/virtuals/virtual_prod.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error.hpp"
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra/functional_update.hpp"
#include "cla3p/algebra/functional_multmv.hpp"
#include "cla3p/algebra/functional_multmm.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix, typename T_Vector>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>& vA,
		const VirtualVector<T_Vector>& vX,
		typename T_Vector::value_type beta, 
		dns::XxVector<typename T_Vector::value_type, T_Vector>& Y)
{
	using T_Scalar = typename T_Vector::value_type;

	if(beta == T_Scalar(0) && !Y) {
		Y = T_Vector::init(vA.size1());
	} // alloc if needed

	T_Scalar coeff =
		(vA.needsEvaluation() ? T_Scalar(1) : vA.coeff())*
		(vX.needsEvaluation() ? T_Scalar(1) : vX.coeff());

	ops::mult(
			coeff,
			vA.needsEvaluation() ? op_t::N : vA.transOp(),
			vA.needsEvaluation() ? vA.evaluate() : vA.obj(),
			vX.needsEvaluation() ? vX.evaluate() : vX.obj(),
			beta, Y.self());
}
/*-------------------------------------------------*/
#define instantiate_virtual_mult(T_Mat, T_Vec) \
template void performVirtualMult( \
		const VirtualMatrix<T_Mat>&, \
		const VirtualVector<T_Vec>&, \
		typename T_Vec::value_type, \
		dns::XxVector<typename T_Vec::value_type, T_Vec>&)
instantiate_virtual_mult(dns::RdMatrix, dns::RdVector);
instantiate_virtual_mult(dns::RfMatrix, dns::RfVector);
instantiate_virtual_mult(dns::CdMatrix, dns::CdVector);
instantiate_virtual_mult(dns::CfMatrix, dns::CfVector);
instantiate_virtual_mult(csc::RdMatrix, dns::RdVector);
instantiate_virtual_mult(csc::RfMatrix, dns::RfVector);
instantiate_virtual_mult(csc::CdMatrix, dns::CdVector);
instantiate_virtual_mult(csc::CfMatrix, dns::CfVector);
#undef instantiate_virtual_mult
/*-------------------------------------------------*/
template <typename T_LhsMatrix, typename T_RhsMatrix>
static void performVirtualMultSpecialization(
		typename T_RhsMatrix::value_type alpha,
		op_t opA, const dns::XxMatrix<typename T_LhsMatrix::value_type,T_LhsMatrix>& A,
		op_t opB, const dns::XxMatrix<typename T_RhsMatrix::value_type,T_RhsMatrix>& B,
		typename T_RhsMatrix::value_type beta, 
		dns::XxMatrix<typename T_RhsMatrix::value_type,T_RhsMatrix>& C)
{
	ops::mult(alpha, opA, A.self(), opB, B.self(), beta, C.self());
}
/*-------------------------------------------------*/
template <typename T_LhsMatrix, typename T_RhsMatrix>
static void performVirtualMultSpecialization(
		typename T_RhsMatrix::value_type alpha,
		op_t opA, const csc::XxMatrix<typename T_LhsMatrix::index_type,typename T_LhsMatrix::value_type,T_LhsMatrix>& A,
		op_t opB, const dns::XxMatrix<typename T_RhsMatrix::value_type,T_RhsMatrix>& B,
		typename T_RhsMatrix::value_type beta, 
		dns::XxMatrix<typename T_RhsMatrix::value_type,T_RhsMatrix>& C)
{
	// Only No-Operation for B is supported

	if(opB == op_t::N) {

		ops::mult(alpha, opA, A.self(), B.self(), beta, C.self());

	} else if(opB == op_t::T) {

		T_RhsMatrix Bt = B.transpose();
		ops::mult(alpha, opA, A.self(), Bt, beta, C.self());

	} else if(opB == op_t::C) {

		T_RhsMatrix Bc = B.ctranspose();
		ops::mult(alpha, opA, A.self(), Bc, beta, C.self());

	} // opB
}
/*-------------------------------------------------*/
template <typename T_LhsMatrix, typename T_RhsMatrix>
void performVirtualMult(
		const VirtualMatrix<T_LhsMatrix>& vA,
		const VirtualMatrix<T_RhsMatrix>& vB,
		typename T_RhsMatrix::value_type beta,
		dns::XxMatrix<typename T_RhsMatrix::value_type, T_RhsMatrix>& C)
{
	using T_Scalar = typename T_RhsMatrix::value_type;

	if(beta == T_Scalar(0) && !C) {
		C = T_RhsMatrix::init(vA.size1(), vB.size2());
	} // alloc if needed

	T_Scalar coeff =
		(vA.needsEvaluation() ? T_Scalar(1) : vA.coeff())*
		(vB.needsEvaluation() ? T_Scalar(1) : vB.coeff());

	performVirtualMultSpecialization(
			coeff,
			vA.needsEvaluation() ? op_t::N : vA.transOp(),
			vA.needsEvaluation() ? vA.evaluate() : vA.obj(),
			vB.needsEvaluation() ? op_t::N : vB.transOp(),
			vB.needsEvaluation() ? vB.evaluate() : vB.obj(),
			beta, C.self());
}
/*-------------------------------------------------*/
#define instantiate_virtual_mult(T_LMat,T_RMat) \
template void performVirtualMult( \
		const VirtualMatrix<T_LMat>&, \
		const VirtualMatrix<T_RMat>&, \
		typename T_RMat::value_type, \
		dns::XxMatrix<typename T_RMat::value_type, T_RMat>&)
instantiate_virtual_mult(dns::RdMatrix,dns::RdMatrix);
instantiate_virtual_mult(dns::RfMatrix,dns::RfMatrix);
instantiate_virtual_mult(dns::CdMatrix,dns::CdMatrix);
instantiate_virtual_mult(dns::CfMatrix,dns::CfMatrix);
instantiate_virtual_mult(csc::RdMatrix,dns::RdMatrix);
instantiate_virtual_mult(csc::RfMatrix,dns::RfMatrix);
instantiate_virtual_mult(csc::CdMatrix,dns::CdMatrix);
instantiate_virtual_mult(csc::CfMatrix,dns::CfMatrix);
#undef instantiate_virtual_mult
/*-------------------------------------------------*/
template <typename T_Matrix>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>& vA,
		const VirtualMatrix<T_Matrix>& vB,
		typename T_Matrix::value_type beta,
		csc::XxMatrix<typename T_Matrix::index_type, typename T_Matrix::value_type, T_Matrix>& C)
{
	using T_Scalar = typename T_Matrix::value_type;

	T_Scalar coeff =
		(vA.needsEvaluation() ? T_Scalar(1) : vA.coeff())*
		(vB.needsEvaluation() ? T_Scalar(1) : vB.coeff());

	T_Matrix tmp = ops::mult(
			coeff,
			vA.needsEvaluation() ? op_t::N : vA.transOp(),
			vA.needsEvaluation() ? vA.evaluate() : vA.obj(),
			vB.needsEvaluation() ? op_t::N : vB.transOp(),
			vB.needsEvaluation() ? vB.evaluate() : vB.obj());

	if(beta == T_Scalar(0)) {
		C.clear();
		C.self() = tmp.move();
	} else {
		C.iscale(beta);
		ops::update(T_Scalar(1), tmp, C);
	} // beta
}
/*-------------------------------------------------*/
#define instantiate_virtual_mult(T_Mat) \
template void performVirtualMult( \
		const VirtualMatrix<T_Mat>&, \
		const VirtualMatrix<T_Mat>&, \
		typename T_Mat::value_type, \
		csc::XxMatrix<typename T_Mat::index_type, typename T_Mat::value_type, T_Mat>&)
instantiate_virtual_mult(csc::RdMatrix);
instantiate_virtual_mult(csc::RfMatrix);
instantiate_virtual_mult(csc::CdMatrix);
instantiate_virtual_mult(csc::CfMatrix);
#undef instantiate_virtual_mult
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
