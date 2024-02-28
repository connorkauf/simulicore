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
#include "cla3p/algebra/operators_scale.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"

/*-------------------------------------------------*/
template <typename T_Object>
void operator*=(
    cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& src,
    typename T_Object::value_type val)
{
  src.iscale(val);
}
/*-------------------------------------------------*/
#define instantiate_scale(T_Obj) \
template void operator*=( \
		cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&, \
		typename T_Obj::value_type)
instantiate_scale(cla3p::dns::RdVector);
instantiate_scale(cla3p::dns::RfVector);
instantiate_scale(cla3p::dns::CdVector);
instantiate_scale(cla3p::dns::CfVector);
instantiate_scale(cla3p::dns::RdMatrix);
instantiate_scale(cla3p::dns::RfMatrix);
instantiate_scale(cla3p::dns::CdMatrix);
instantiate_scale(cla3p::dns::CfMatrix);
#undef instantiate_scale
/*-------------------------------------------------*/
template <typename T_Matrix>
void operator*=(
    cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    typename T_Matrix::value_type val)
{
  A.iscale(val);
}
/*-------------------------------------------------*/
#define instantiate_scale(T_Mat) \
template void operator*=( \
    cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		typename T_Mat::value_type)
instantiate_scale(cla3p::csc::RdMatrix);
instantiate_scale(cla3p::csc::RfMatrix);
instantiate_scale(cla3p::csc::CdMatrix);
instantiate_scale(cla3p::csc::CfMatrix);
#undef instantiate_scale
/*-------------------------------------------------*/
template <typename T_Object>
void operator/=(
    cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& src,
    typename T_Object::value_type val)
{
  src.iscale(cla3p::arith::inv(val));
}
/*-------------------------------------------------*/
#define instantiate_scale(T_Obj) \
template void operator/=( \
		cla3p::dns::XxObject<typename T_Obj::value_type,T_Obj>&, \
		typename T_Obj::value_type)
instantiate_scale(cla3p::dns::RdVector);
instantiate_scale(cla3p::dns::RfVector);
instantiate_scale(cla3p::dns::CdVector);
instantiate_scale(cla3p::dns::CfVector);
instantiate_scale(cla3p::dns::RdMatrix);
instantiate_scale(cla3p::dns::RfMatrix);
instantiate_scale(cla3p::dns::CdMatrix);
instantiate_scale(cla3p::dns::CfMatrix);
#undef instantiate_scale
/*-------------------------------------------------*/
template <typename T_Matrix>
void operator/=(
    cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    typename T_Matrix::value_type val)
{
  A.iscale(cla3p::arith::inv(val));
}
/*-------------------------------------------------*/
#define instantiate_scale(T_Mat) \
template void operator/=( \
    cla3p::csc::XxMatrix<typename T_Mat::index_type,typename T_Mat::value_type,T_Mat>&, \
		typename T_Mat::value_type)
instantiate_scale(cla3p::csc::RdMatrix);
instantiate_scale(cla3p::csc::RfMatrix);
instantiate_scale(cla3p::csc::CdMatrix);
instantiate_scale(cla3p::csc::CfMatrix);
#undef instantiate_scale
/*-------------------------------------------------*/
