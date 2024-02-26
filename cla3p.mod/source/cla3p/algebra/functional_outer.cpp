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
#include "cla3p/algebra/functional_outer.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/checks/outer_checks.hpp"
#include "cla3p/checks/hermitian_coeff_checks.hpp"
#include "cla3p/proxies/blas_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
static void outerx(bool conjop, typename T_Vector::value_type alpha, const T_Vector& X, const T_Vector& Y, T_Matrix& A)
{
	conjop = (TypeTraits<T_Matrix>::is_real() ? false : true);

	outer_product_consistency_check(conjop, A.nrows(), A.ncols(), A.prop(), X.size(), Y.size());
	hermitian_coeff_check(A.prop(), alpha);

	if(A.prop().isGeneral()) {

		if(conjop) blas::gerc(X.size(), Y.size(), alpha, X.values(), 1, Y.values(), 1, A.values(), A.ld());
		else       blas::ger (X.size(), Y.size(), alpha, X.values(), 1, Y.values(), 1, A.values(), A.ld());

	} else if(A.prop().isSymmetric()) {

		if(X.values() == Y.values()) {
			blas::syr(A.prop().cuplo(), X.size(), alpha, X.values(), 1, A.values(), A.ld());
		} else {
			blas::gemmt(A.prop().cuplo(), 'N', 'T', X.size(), 1, alpha, X.values(), X.size(), Y.values(), Y.size(), 1, A.values(), A.ld());
		}

	} else if(A.prop().isHermitian()) {

		if(X.values() == Y.values()) {
			blas::her(A.prop().cuplo(), X.size(), arith::getRe(alpha), X.values(), 1, A.values(), A.ld());
		} else {
			blas::gemmt(A.prop().cuplo(), 'N', 'C', X.size(), 1, alpha, X.values(), X.size(), Y.values(), Y.size(), 1, A.values(), A.ld());
		}

	} else {

		throw err::Exception();

	} // valid props
}
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void outer(typename T_Vector::value_type alpha, const T_Vector& X, const T_Vector& Y, T_Matrix& A)
{
	outerx(false, alpha, X, Y, A);
}
/*-------------------------------------------------*/
template void outer(dns::RdVector::value_type, const dns::RdVector&, const dns::RdVector&, dns::RdMatrix&);
template void outer(dns::RfVector::value_type, const dns::RfVector&, const dns::RfVector&, dns::RfMatrix&);
template void outer(dns::CdVector::value_type, const dns::CdVector&, const dns::CdVector&, dns::CdMatrix&);
template void outer(dns::CfVector::value_type, const dns::CfVector&, const dns::CfVector&, dns::CfMatrix&);
/*-------------------------------------------------*/
template <typename T_Vector, typename T_Matrix>
void outerc(typename T_Vector::value_type alpha, const T_Vector& X, const T_Vector& Y, T_Matrix& A)
{
	outerx(true, alpha, X, Y, A);
}
/*-------------------------------------------------*/
template void outerc(dns::RdVector::value_type, const dns::RdVector&, const dns::RdVector&, dns::RdMatrix&);
template void outerc(dns::RfVector::value_type, const dns::RfVector&, const dns::RfVector&, dns::RfMatrix&);
template void outerc(dns::CdVector::value_type, const dns::CdVector&, const dns::CdVector&, dns::CdMatrix&);
template void outerc(dns::CfVector::value_type, const dns::CfVector&, const dns::CfVector&, dns::CfMatrix&);
/*-------------------------------------------------*/
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type outer(const T_Vector& X, const T_Vector& Y, const Property& pr)
{
	typename T_Vector::value_type alpha = 1;
  typename TypeTraits<T_Vector>::matrix_type ret(X.size(), Y.size(), pr);
  ret = 0;
  outer(alpha, X, Y, ret);
  return ret;
}
/*-------------------------------------------------*/
template typename TypeTraits<dns::RdVector>::matrix_type outer(const dns::RdVector&, const dns::RdVector&, const Property&);
template typename TypeTraits<dns::RfVector>::matrix_type outer(const dns::RfVector&, const dns::RfVector&, const Property&);
template typename TypeTraits<dns::CdVector>::matrix_type outer(const dns::CdVector&, const dns::CdVector&, const Property&);
template typename TypeTraits<dns::CfVector>::matrix_type outer(const dns::CfVector&, const dns::CfVector&, const Property&);
/*-------------------------------------------------*/
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type outerc(const T_Vector& X, const T_Vector& Y, const Property& pr)
{
	typename T_Vector::value_type alpha = 1;
  typename TypeTraits<T_Vector>::matrix_type ret(X.size(), Y.size(), pr);
  ret = 0;
  outerc(alpha, X, Y, ret);
  return ret;
}
/*-------------------------------------------------*/
template typename TypeTraits<dns::RdVector>::matrix_type outerc(const dns::RdVector&, const dns::RdVector&, const Property&);
template typename TypeTraits<dns::RfVector>::matrix_type outerc(const dns::RfVector&, const dns::RfVector&, const Property&);
template typename TypeTraits<dns::CdVector>::matrix_type outerc(const dns::CdVector&, const dns::CdVector&, const Property&);
template typename TypeTraits<dns::CfVector>::matrix_type outerc(const dns::CfVector&, const dns::CfVector&, const Property&);
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/
