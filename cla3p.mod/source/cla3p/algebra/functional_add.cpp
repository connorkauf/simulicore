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
#include "cla3p/algebra/functional_add.hpp"

// system

// 3rd

// cla3p
#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/bulk/csc_math.hpp"
#include "cla3p/algebra/functional_update.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Vector>
T_Vector add(
		typename T_Vector::value_type alpha, const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		typename T_Vector::value_type beta , const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	similarity_dim_check(X.size(), Y.size());

	T_Vector ret(X.size());

	blk::dns::add(uplo_t::Full, X.size(), 1, 
		alpha, X.values(), X.size(),
		beta , Y.values(), Y.size(), 
		ret.values(), ret.size());

	return ret;
}
/*-------------------------------------------------*/
#define instantiate_add(T_Vec) \
template T_Vec add( \
		typename T_Vec::value_type, const dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
		typename T_Vec::value_type, const dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_add(dns::RdVector);
instantiate_add(dns::RfVector);
instantiate_add(dns::CdVector);
instantiate_add(dns::CfVector);
#undef instantiate_add
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix add(
		typename T_Matrix::value_type alpha, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		typename T_Matrix::value_type beta , const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	similarity_check(
			A.prop(), A.nrows(), A.ncols(),
			B.prop(), B.nrows(), B.ncols());

	uint_t m = A.nrows();
	uint_t n = A.ncols();
	Property pr = A.prop();

	T_Matrix ret(m, n, pr);

	blk::dns::add(pr.uplo(), m, n, 
			alpha, A.values(), A.ld(),
			beta, B.values(), B.ld(), 
			ret.values(), ret.ld());

	return ret;
}
/*-------------------------------------------------*/
#define instantiate_add(T_Mat) \
template T_Mat add( \
		typename T_Mat::value_type, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
		typename T_Mat::value_type, const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_add(dns::RdMatrix);
instantiate_add(dns::RfMatrix);
instantiate_add(dns::CdMatrix);
instantiate_add(dns::CfMatrix);
#undef instantiate_add
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix add(typename T_Matrix::value_type alpha,
		const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	similarity_check(
			A.prop(), A.nrows(), A.ncols(),
			B.prop(), B.nrows(), B.ncols());

	using T_Scalar = typename T_Matrix::value_type;

	uint_t    nrowsC  = A.nrows();
	uint_t    ncolsC  = A.ncols();
	Property  propC   = A.prop();
	int_t*    colptrC = nullptr;
	int_t*    rowidxC = nullptr;
	T_Scalar* valuesC = nullptr;

	blk::csc::add(nrowsC, ncolsC, alpha,
			A.colptr(), A.rowidx(), A.values(),
			B.colptr(), B.rowidx(), B.values(),
			&colptrC, &rowidxC, &valuesC);

	return T_Matrix::wrap(nrowsC, ncolsC, colptrC, rowidxC, valuesC, true, propC);
}
/*-------------------------------------------------*/
#define instantiate_add(T_Mat) \
template T_Mat add(typename T_Mat::value_type, \
		const csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		const csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_add(csc::RdMatrix);
instantiate_add(csc::RfMatrix);
instantiate_add(csc::CdMatrix);
instantiate_add(csc::CfMatrix);
#undef instantiate_add
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
