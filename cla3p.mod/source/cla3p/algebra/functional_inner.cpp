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
#include "cla3p/algebra/functional_inner.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/checks/dot_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Vector>
typename T_Vector::value_type dot(const T_Vector& X, const T_Vector& Y)
{
	dot_product_consistency_check(X.size(), Y.size());
	return blas::dot(X.size(), X.values(), 1, Y.values(), 1);
}
/*-------------------------------------------------*/
template dns::RdVector::value_type dot(const dns::RdVector&, const dns::RdVector&);
template dns::RfVector::value_type dot(const dns::RfVector&, const dns::RfVector&);
template dns::CdVector::value_type dot(const dns::CdVector&, const dns::CdVector&);
template dns::CfVector::value_type dot(const dns::CfVector&, const dns::CfVector&);
/*-------------------------------------------------*/
template <typename T_Vector>
typename T_Vector::value_type dotc(const T_Vector& X, const T_Vector& Y)
{
	dot_product_consistency_check(X.size(), Y.size());
	return blas::dotc(X.size(), X.values(), 1, Y.values(), 1);
}
/*-------------------------------------------------*/
template dns::RdVector::value_type dotc(const dns::RdVector&, const dns::RdVector&);
template dns::RfVector::value_type dotc(const dns::RfVector&, const dns::RfVector&);
template dns::CdVector::value_type dotc(const dns::CdVector&, const dns::CdVector&);
template dns::CfVector::value_type dotc(const dns::CfVector&, const dns::CfVector&);
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
