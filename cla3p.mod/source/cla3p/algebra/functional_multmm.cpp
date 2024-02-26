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
#include "cla3p/algebra/functional_multmm.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/checks/matrix_math_checks.hpp"
#include "cla3p/checks/hermitian_coeff_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/algebra/functional_update.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Matrix>
void mult(typename T_Matrix::value_type alpha,
    op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    op_t opB, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& C)
{
	using T_Scalar = typename T_Matrix::value_type;

	if(A.prop().isSymmetric() || A.prop().isHermitian()) opA = op_t::N;
	if(B.prop().isSymmetric() || B.prop().isHermitian()) opB = op_t::N;

	opA = (TypeTraits<T_Matrix>::is_real() && opA == op_t::C ? op_t::T : opA);
	opB = (TypeTraits<T_Matrix>::is_real() && opB == op_t::C ? op_t::T : opB);

	Operation _opA(opA);
	Operation _opB(opB);

	mat_x_mat_mult_check(
			A.prop(), A.nrows(), A.ncols(), _opA,
			B.prop(), B.nrows(), B.ncols(), _opB,
			C.prop(), 
			C.nrows(), 
			C.ncols());

	hermitian_coeff_check(A.prop(), alpha);

	if(A.prop().isGeneral() && B.prop().isGeneral()) {

		uint_t k = (_opA.isTranspose() ? A.nrows() : A.ncols());

		if(C.prop().isGeneral()) {
			bulk::dns::gem_x_gem(
					C.nrows(), 
					C.ncols(), 
					k, alpha, 
					opA, A.values(), A.ld(), 
					opB, B.values(), B.ld(), 
					T_Scalar(1), 
					C.values(), C.ld());
		} else {
			blas::gemmt(C.prop().cuplo(), 
					_opA.ctype(), 
					_opB.ctype(), 
					C.nrows(), C.ncols(), alpha, 
					A.values(), A.ld(), 
					B.values(), B.ld(), 
					1, C.values(), C.ld());
		}

	} else if(A.prop().isSymmetric() && B.prop().isGeneral()) {

		bulk::dns::sym_x_gem(A.prop().uplo(), 
				C.nrows(), 
				C.ncols(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				T_Scalar(1), 
				C.values(), C.ld());

	} else if(A.prop().isHermitian() && B.prop().isGeneral()) {

		bulk::dns::hem_x_gem(
				A.prop().uplo(), 
				C.nrows(), 
				C.ncols(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				T_Scalar(1), 
				C.values(), C.ld());

	} else if(A.prop().isGeneral() && B.prop().isSymmetric()) {

		bulk::dns::gem_x_sym(B.prop().uplo(), 
				C.nrows(), 
				C.ncols(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				T_Scalar(1), 
				C.values(), C.ld());

	} else if(A.prop().isGeneral() && B.prop().isHermitian()) {

		bulk::dns::gem_x_hem(B.prop().uplo(), 
				C.nrows(), 
				C.ncols(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				T_Scalar(1), 
				C.values(), C.ld());

	} else if(A.prop().isTriangular() && B.prop().isGeneral()) {

		T_Matrix tmp(C.nrows(), C.ncols(), defaultProperty());

		bulk::dns::trm_x_gem(A.prop().uplo(), opA, 
				C.nrows(), 
				C.ncols(), 
				B.nrows(), 
				alpha, 
				A.values(), A.ld(), 
				B.values(), B.ld(), 
				tmp.values(), tmp.ld());

		ops::update(1, tmp, C);

	} else if(A.prop().isGeneral() && B.prop().isTriangular()) {

		T_Matrix tmp(C.nrows(), C.ncols(), defaultProperty());

		bulk::dns::gem_x_trm(B.prop().uplo(), opB, 
				C.nrows(), 
				C.ncols(), 
				A.nrows(), 
				alpha, 
				B.values(), B.ld(), 
				A.values(), A.ld(), 
				tmp.values(), tmp.ld());

		ops::update(1, tmp, C);

	} else {

		throw err::Exception();

	} // property combos
}
/*-------------------------------------------------*/
#define instantiate_mult(T_Mat) \
template void mult(typename T_Mat::value_type, \
		op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_mult(dns::RdMatrix);
instantiate_mult(dns::RfMatrix);
instantiate_mult(dns::CdMatrix);
instantiate_mult(dns::CfMatrix);
#undef instantiate_mult
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix mult(typename T_Matrix::value_type alpha,
    op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    op_t opB, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
    const Property& pr)
{
	Operation _opA(opA);
	Operation _opB(opB);
	T_Matrix ret(
			_opA.isTranspose() ? A.ncols() : A.nrows(),
			_opB.isTranspose() ? B.nrows() : B.ncols(), pr);
	ret = 0;
	mult(alpha, opA, A, opB, B, ret);
	return ret;
}
/*-------------------------------------------------*/
#define instantiate_mult(T_Mat) \
template T_Mat mult(typename T_Mat::value_type, \
		op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    const Property&)
instantiate_mult(dns::RdMatrix);
instantiate_mult(dns::RfMatrix);
instantiate_mult(dns::CdMatrix);
instantiate_mult(dns::CfMatrix);
#undef instantiate_mult
/*-------------------------------------------------*/
template <typename T_Matrix>
static void trimult(typename T_Matrix::value_type alpha, side_t sideA, 
		op_t opA, const  dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
  Operation _opA(opA);

  trimat_mult_replace_check(sideA,
      A.prop(), A.nrows(), A.ncols(), _opA,
      B.prop(), B.nrows(), B.ncols());

  blas::trmm(
      static_cast<char>(sideA), A.prop().cuplo(), _opA.ctype(), 'N',
      B.nrows(), B.ncols(), alpha, A.values(), A.ld(),
      B.values(),
      B.ld());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha, op_t opA,
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	trimult(alpha, side_t::Left, opA, A, B);
}
/*-------------------------------------------------*/
#define instantiate_trimult(T_Mat) \
template void trimult(typename T_Mat::value_type, op_t, \
		const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_trimult(dns::RdMatrix);
instantiate_trimult(dns::RfMatrix);
instantiate_trimult(dns::CdMatrix);
instantiate_trimult(dns::CfMatrix);
#undef instantiate_trimult
/*-------------------------------------------------*/
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	trimult(alpha, side_t::Right, opA, A, B);
}
/*-------------------------------------------------*/
#define instantiate_trimult(T_Mat) \
template void trimult(typename T_Mat::value_type, \
		dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_trimult(dns::RdMatrix);
instantiate_trimult(dns::RfMatrix);
instantiate_trimult(dns::CdMatrix);
instantiate_trimult(dns::CfMatrix);
#undef instantiate_trimult
/*-------------------------------------------------*/
template <typename T_Matrix>
static void trisol(typename T_Matrix::value_type alpha, side_t sideA, 
		op_t opA, const  dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	Operation _opA(opA);

	trimat_mult_replace_check(sideA,
			A.prop(), A.nrows(), A.ncols(), _opA,
			B.prop(), B.nrows(), B.ncols());

	blas::trsm(
			static_cast<char>(sideA), A.prop().cuplo(), _opA.ctype(), 'N',
			B.nrows(), B.ncols(), alpha, A.values(), A.ld(),
			B.values(),
			B.ld());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha, op_t opA,
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	trisol(alpha, side_t::Left, opA, A, B);
}
/*-------------------------------------------------*/
#define instantiate_trisol(T_Mat) \
template void trisol(typename T_Mat::value_type, op_t, \
		const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_trisol(dns::RdMatrix);
instantiate_trisol(dns::RfMatrix);
instantiate_trisol(dns::CdMatrix);
instantiate_trisol(dns::CfMatrix);
#undef instantiate_trisol
/*-------------------------------------------------*/
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
    op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	trisol(alpha, side_t::Right, opA, A, B);
}
/*-------------------------------------------------*/
#define instantiate_trisol(T_Mat) \
template void trisol(typename T_Mat::value_type, \
		dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
    op_t, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_trisol(dns::RdMatrix);
instantiate_trisol(dns::RfMatrix);
instantiate_trisol(dns::CdMatrix);
instantiate_trisol(dns::CfMatrix);
#undef instantiate_trisol
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
