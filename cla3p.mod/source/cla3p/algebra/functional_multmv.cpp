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
#include "cla3p/algebra/functional_multmv.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/bulk/csc_math.hpp"
#include "cla3p/algebra/functional_update.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void mult(typename T_Vector::value_type alpha, op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	Operation _opA(opA);
	mat_x_vec_mult_check(_opA, A.prop(), A.nrows(), A.ncols(), X.size(), Y.size());

	typename T_Vector::value_type beta = 1;

	if(A.prop().isGeneral()) {

		bulk::dns::gem_x_vec(opA, A.nrows(), A.ncols(), alpha, A.values(), A.ld(), X.values(), beta, Y.values());

	} else if(A.prop().isSymmetric()) {

		bulk::dns::sym_x_vec(A.prop().uplo(), A.ncols(), alpha, A.values(), A.ld(), X.values(), beta, Y.values());

	} else if(A.prop().isHermitian()) {

		bulk::dns::hem_x_vec(A.prop().uplo(), A.ncols(), alpha, A.values(), A.ld(), X.values(), beta, Y.values());

	} else if(A.prop().isTriangular()) {

		T_Vector tmp(Y.size());
		bulk::dns::trm_x_vec(A.prop().uplo(), opA, A.nrows(), A.ncols(), alpha, A.values(), A.ld(), X.values(), tmp.values());
		ops::update(1, tmp, Y);

	} else {

		throw err::Exception();

	} // property 
}
/*-------------------------------------------------*/
#define instantiate_mult(T_Vec, T_Mat) \
template void mult(typename T_Vec::value_type, op_t, \
    const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    const dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
    dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_mult(dns::RdVector, dns::RdMatrix);
instantiate_mult(dns::RfVector, dns::RfMatrix);
instantiate_mult(dns::CdVector, dns::CdMatrix);
instantiate_mult(dns::CfVector, dns::CfMatrix);
#undef instantiate_mult
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void trimult(op_t opA,
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
	Operation _opA(opA);
	trivec_mult_replace_check(A.prop(), A.nrows(), A.ncols(), _opA, X.size());

	blas::trmv(A.prop().cuplo(), _opA.ctype(), 'N', A.ncols(), A.values(), A.ld(), X.values(), 1);
}
/*-------------------------------------------------*/
#define instantiate_trimult(T_Vec, T_Mat) \
template void trimult(op_t, \
    const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_trimult(dns::RdVector, dns::RdMatrix);
instantiate_trimult(dns::RfVector, dns::RfMatrix);
instantiate_trimult(dns::CdVector, dns::CdMatrix);
instantiate_trimult(dns::CfVector, dns::CfMatrix);
#undef instantiate_trimult
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void trisol(op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& B)
{
	Operation _opA(opA);
	trivec_mult_replace_check(A.prop(), A.nrows(), A.ncols(), _opA, B.size());

	blas::trsv(A.prop().cuplo(), _opA.ctype(), 'N', A.ncols(), A.values(), A.ld(), B.values(), 1);
}
/*-------------------------------------------------*/
#define instantiate_trisol(T_Vec, T_Mat) \
template void trisol(op_t, \
    const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_trisol(dns::RdVector, dns::RdMatrix);
instantiate_trisol(dns::RfVector, dns::RfMatrix);
instantiate_trisol(dns::CdVector, dns::CdMatrix);
instantiate_trisol(dns::CfVector, dns::CfMatrix);
#undef instantiate_trisol
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void mult(typename T_Vector::value_type alpha, op_t opA,
    const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	Operation _opA(opA);
	mat_x_vec_mult_check(_opA, A.prop(), A.nrows(), A.ncols(), X.size(), Y.size());

	typename T_Vector::value_type beta = 1;

	if(A.prop().isGeneral() || A.prop().isTriangular()) {

		bulk::csc::gem_x_vec(opA, A.nrows(), A.ncols(), alpha, 
				A.colptr(), A.rowidx(), A.values(), 
				X.values(), beta, Y.values());

	} else if(A.prop().isSymmetric()) {

		bulk::csc::sym_x_vec(A.prop().uplo(), A.ncols(), alpha, 
				A.colptr(), A.rowidx(), A.values(), 
				X.values(), beta, Y.values());

	} else if(A.prop().isHermitian()) {

		bulk::csc::hem_x_vec(A.prop().uplo(), A.ncols(), alpha, 
				A.colptr(), A.rowidx(), A.values(), 
				X.values(), beta, Y.values());

	} else {

		throw err::Exception();

	} // property 
}
/*-------------------------------------------------*/
#define instantiate_mult(T_Vec, T_Mat) \
template void mult(typename T_Vec::value_type, op_t, \
    const csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
    const dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
    dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_mult(dns::RdVector, csc::RdMatrix);
instantiate_mult(dns::RfVector, csc::RfMatrix);
instantiate_mult(dns::CdVector, csc::CdMatrix);
instantiate_mult(dns::CfVector, csc::CfMatrix);
#undef instantiate_mult
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
