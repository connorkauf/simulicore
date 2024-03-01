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
#include "cla3p/algebra/operators_perm.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/perms.hpp"

/*-------------------------------------------------*/
template <typename T_Int, typename T_Vector>
T_Vector operator*(
    const cla3p::prm::PxMatrix<T_Int>& P,
    const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
  return X.permuteLeft(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm, T_Vec) \
template T_Vec operator*( \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&, \
		const cla3p::dns::XxVector<T_Vec::value_type,T_Vec>&)
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RdVector);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RfVector);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CdVector);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CfVector);
#undef instantiate_perm
/*-------------------------------------------------*/
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
    const cla3p::prm::PxMatrix<T_Int>& P,
    const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
  return A.permuteLeft(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm, T_Mat) \
template T_Mat operator*( \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&, \
		const cla3p::dns::XxMatrix<T_Mat::value_type,T_Mat>&)
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RfMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CfMatrix);
#undef instantiate_perm
/*-------------------------------------------------*/
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::prm::PxMatrix<T_Int>& P,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A)
{
	return A.permuteLeft(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm, T_Mat) \
template T_Mat operator*( \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&, \
		const cla3p::csc::XxMatrix<T_Mat::index_type,T_Mat::value_type,T_Mat>&)
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::RdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::RfMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::CdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::CfMatrix);
#undef instantiate_perm
/*-------------------------------------------------*/
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::prm::PxMatrix<T_Int>& P)
{
	return A.permuteRight(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm, T_Mat) \
template T_Mat operator*( \
		const cla3p::dns::XxMatrix<T_Mat::value_type,T_Mat>&, \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&)
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::RfMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::dns::CfMatrix);
#undef instantiate_perm
/*-------------------------------------------------*/
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::prm::PxMatrix<T_Int>& P)
{
	return A.permuteRight(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm, T_Mat) \
template T_Mat operator*( \
		const cla3p::csc::XxMatrix<T_Mat::index_type,T_Mat::value_type,T_Mat>&, \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&)
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::RdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::RfMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::CdMatrix);
instantiate_perm(cla3p::prm::PiMatrix, cla3p::csc::CfMatrix);
#undef instantiate_perm
/*-------------------------------------------------*/
template <typename T_Int>
cla3p::prm::PxMatrix<T_Int> operator*(
    const cla3p::prm::PxMatrix<T_Int>& P,
    const cla3p::prm::PxMatrix<T_Int>& Q)
{
  return Q.permuteLeft(P);
}
/*-------------------------------------------------*/
#define instantiate_perm(T_Prm) \
template T_Prm operator*( \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&, \
		const cla3p::prm::PxMatrix<T_Prm::value_type>&)
instantiate_perm(cla3p::prm::PiMatrix);
#undef instantiate_perm
/*-------------------------------------------------*/
