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
#include "cla3p/algebra/functional_update.hpp"

// system

// 3rd

// cla3p
#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/algebra/functional_add.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Vector>
void update(typename T_Vector::value_type alpha,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	similarity_check(
			defaultProperty(), X.size(), 1,
			defaultProperty(), Y.size(), 1);

	blas::axpy(X.size(), alpha, X.values(), 1, Y.values(), 1);
}
/*-------------------------------------------------*/
#define instantiate_update(T_Vec) \
template void update(typename T_Vec::value_type, \
		const dns::XxVector<typename T_Vec::value_type,T_Vec>&, \
		dns::XxVector<typename T_Vec::value_type,T_Vec>&)
instantiate_update(dns::RdVector);
instantiate_update(dns::RfVector);
instantiate_update(dns::CdVector);
instantiate_update(dns::CfVector);
#undef instantiate_update
/*-------------------------------------------------*/
template <typename T_Matrix>
void update(typename T_Matrix::value_type alpha,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	similarity_check(
			A.prop(), A.nrows(), A.ncols(),
			B.prop(), B.nrows(), B.ncols());

	bulk::dns::update(A.prop().uplo(), A.nrows(), A.ncols(), alpha, 
			A.values(), A.ld(),
			B.values(), B.ld());
}
/*-------------------------------------------------*/
#define instantiate_update(T_Mat) \
template void update(typename T_Mat::value_type, \
		const dns::XxMatrix<typename T_Mat::value_type,T_Mat>&, \
		dns::XxMatrix<typename T_Mat::value_type,T_Mat>&)
instantiate_update(dns::RdMatrix);
instantiate_update(dns::RfMatrix);
instantiate_update(dns::CdMatrix);
instantiate_update(dns::CfMatrix);
#undef instantiate_update
/*-------------------------------------------------*/
template <typename T_Matrix>
void update(typename T_Matrix::value_type alpha,
    const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	similarity_check(
			A.prop(), A.nrows(), A.ncols(),
			B.prop(), B.nrows(), B.ncols());

	T_Matrix tmp = add(alpha, A, B);
	B = tmp.move();
}
/*-------------------------------------------------*/
#define instantiate_update(T_Mat) \
template void update(typename T_Mat::value_type, \
		const csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_update(csc::RdMatrix);
instantiate_update(csc::RfMatrix);
instantiate_update(csc::CdMatrix);
instantiate_update(csc::CfMatrix);
#undef instantiate_update
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
