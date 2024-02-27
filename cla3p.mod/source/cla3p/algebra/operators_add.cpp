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
#include "cla3p/algebra/operators_add.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra/functional_add.hpp"

/*-------------------------------------------------*/
template <typename T_Object>
T_Object operator+(
    const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
    const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	using T_Scalar = typename T_Object::value_type;
  return cla3p::ops::add(T_Scalar(1), A.self(), T_Scalar(1), B.self());
}
/*-------------------------------------------------*/
#define instantiate_op_add(T_Obj) \
template T_Obj operator+( \
    const cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&, \
    const cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&)
instantiate_op_add(cla3p::dns::RdVector);
instantiate_op_add(cla3p::dns::RfVector);
instantiate_op_add(cla3p::dns::CdVector);
instantiate_op_add(cla3p::dns::CfVector);
instantiate_op_add(cla3p::dns::RdMatrix);
instantiate_op_add(cla3p::dns::RfMatrix);
instantiate_op_add(cla3p::dns::CdMatrix);
instantiate_op_add(cla3p::dns::CfMatrix);
#undef instantiate_op_add
/*-------------------------------------------------*/
template <typename T_Object>
T_Object operator-(
    const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
    const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	using T_Scalar = typename T_Object::value_type;
  return cla3p::ops::add(T_Scalar(1), A.self(), T_Scalar(-1), B.self());
}
/*-------------------------------------------------*/
#define instantiate_op_sub(T_Obj) \
template T_Obj operator-( \
    const cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&, \
    const cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&)
instantiate_op_sub(cla3p::dns::RdVector);
instantiate_op_sub(cla3p::dns::RfVector);
instantiate_op_sub(cla3p::dns::CdVector);
instantiate_op_sub(cla3p::dns::CfVector);
instantiate_op_sub(cla3p::dns::RdMatrix);
instantiate_op_sub(cla3p::dns::RfMatrix);
instantiate_op_sub(cla3p::dns::CdMatrix);
instantiate_op_sub(cla3p::dns::CfMatrix);
#undef instantiate_op_sub
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix operator+(
    const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
  using T_Scalar = typename T_Matrix::value_type;
  return cla3p::ops::add(T_Scalar(1), A, B);
}
/*-------------------------------------------------*/
#define instantiate_op_add(T_Mat) \
template T_Mat operator+( \
    const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
    const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_op_add(cla3p::csc::RdMatrix);
instantiate_op_add(cla3p::csc::RfMatrix);
instantiate_op_add(cla3p::csc::CdMatrix);
instantiate_op_add(cla3p::csc::CfMatrix);
#undef instantiate_op_add
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix operator-(
    const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
  using T_Scalar = typename T_Matrix::value_type;
  return cla3p::ops::add(T_Scalar(-1), B, A);
}
/*-------------------------------------------------*/
#define instantiate_op_sub(T_Mat) \
template T_Mat operator-( \
    const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
    const cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&)
instantiate_op_sub(cla3p::csc::RdMatrix);
instantiate_op_sub(cla3p::csc::RfMatrix);
instantiate_op_sub(cla3p::csc::CdMatrix);
instantiate_op_sub(cla3p::csc::CfMatrix);
#undef instantiate_op_sub
/*-------------------------------------------------*/
