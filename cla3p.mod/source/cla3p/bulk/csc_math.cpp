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
#include "cla3p/bulk/csc_math.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#if defined(CLA3P_INTEL_MKL)
#include "cla3p/proxies/mkl_sparse_proxy.hpp"
#elif defined(CLA3P_ARMPL)
#include "cla3p/proxies/armpl_sparse_proxy.hpp"
#endif

/*-------------------------------------------------*/
namespace cla3p {
namespace blk {
namespace csc {
/*-------------------------------------------------*/
template <typename T_Scalar>
void add(uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
		const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
#if defined(CLA3P_INTEL_MKL)
	mkl::csc_add(m, n, alpha, op_t::N,
			colptrA, rowidxA, valuesA,
			colptrB, rowidxB, valuesB,
			colptrC, rowidxC, valuesC);
#elif defined(CLA3P_ARMPL)
	T_Scalar beta = T_Scalar(1);
	armpl::csc_add(m, n,
			alpha, op_t::N, colptrA, rowidxA, valuesA,
			beta, op_t::N, colptrB, rowidxB, valuesB,
			colptrC, rowidxC, valuesC);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_add(T_Scl) \
template void add(uint_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_add(real_t);
instantiate_add(real4_t);
instantiate_add(complex_t);
instantiate_add(complex8_t);
#undef instantiate_add
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_vec(op_t opA, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
#if defined(CLA3P_INTEL_MKL)
	Property pr = Property::General();
	mkl::csc_mv(pr.type(), pr.uplo(), m, n, alpha, opA, colptr, rowidx, values, x, beta, y);
#elif defined(CLA3P_ARMPL)
	Property pr = Property::General();
	armpl::csc_mv(pr.type(), pr.uplo(), m, n, alpha, opA, colptr, rowidx, values, x, beta, y);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_gem_x_vec(T_Scl) \
template void gem_x_vec(op_t, uint_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, T_Scl, T_Scl*)
instantiate_gem_x_vec(real_t);
instantiate_gem_x_vec(real4_t);
instantiate_gem_x_vec(complex_t);
instantiate_gem_x_vec(complex8_t);
#undef instantiate_gem_x_vec
/*-------------------------------------------------*/
template <typename T_Scalar>
void sym_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
#if defined(CLA3P_INTEL_MKL)
	Property pr = Property(prop_t::Symmetric, uplo);
	mkl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
#elif defined(CLA3P_ARMPL)
	Property pr = Property(prop_t::Symmetric, uplo);
	armpl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_sym_x_vec(T_Scl) \
template void sym_x_vec(uplo_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, T_Scl, T_Scl*)
instantiate_sym_x_vec(real_t);
instantiate_sym_x_vec(real4_t);
instantiate_sym_x_vec(complex_t);
instantiate_sym_x_vec(complex8_t);
#undef instantiate_sym_x_vec
/*-------------------------------------------------*/
template <typename T_Scalar>
void hem_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
#if defined(CLA3P_INTEL_MKL)
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	mkl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
#elif defined(CLA3P_ARMPL)
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	armpl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_hem_x_vec(T_Scl) \
template void hem_x_vec(uplo_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, T_Scl, T_Scl*)
instantiate_hem_x_vec(real_t);
instantiate_hem_x_vec(real4_t);
instantiate_hem_x_vec(complex_t);
instantiate_hem_x_vec(complex8_t);
#undef instantiate_hem_x_vec
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_gem(op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
#if defined(CLA3P_INTEL_MKL)
	uint_t mA = (opA == op_t::N ? m : k);
	uint_t nA = (opA == op_t::N ? k : m);
	Property pr = Property::General();
	mkl::csc_mm(pr.type(), pr.uplo(), mA, nA, alpha, opA, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#elif defined(CLA3P_ARMPL)
	uint_t mA = (opA == op_t::N ? m : k);
	uint_t nA = (opA == op_t::N ? k : m);
	Property pr = Property::General();
	armpl::csc_mm(pr.type(), pr.uplo(), mA, nA, alpha, opA, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_gem_x_gem(T_Scl) \
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, uint_t, T_Scl, T_Scl*, uint_t )
instantiate_gem_x_gem(real_t);
instantiate_gem_x_gem(real4_t);
instantiate_gem_x_gem(complex_t);
instantiate_gem_x_gem(complex8_t);
#undef instantiate_gem_x_gem
/*-------------------------------------------------*/
template <typename T_Scalar>
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
#if defined(CLA3P_INTEL_MKL)
	Property pr = Property(prop_t::Symmetric, uplo);
	mkl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#elif defined(CLA3P_ARMPL)
	Property pr = Property(prop_t::Symmetric, uplo);
	armpl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_sym_x_gem(T_Scl) \
	template void sym_x_gem(uplo_t, uint_t, uint_t, T_Scl, \
			const int_t*, const int_t*, const T_Scl*, \
			const T_Scl*, uint_t, T_Scl, T_Scl*, uint_t)
instantiate_sym_x_gem(real_t);
instantiate_sym_x_gem(real4_t);
instantiate_sym_x_gem(complex_t);
instantiate_sym_x_gem(complex8_t);
#undef instantiate_sym_x_gem
/*-------------------------------------------------*/
template <typename T_Scalar>
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
#if defined(CLA3P_INTEL_MKL)
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	mkl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#elif defined(CLA3P_ARMPL)
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	armpl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_hem_x_gem(T_Scl) \
template void hem_x_gem(uplo_t, uint_t, uint_t, T_Scl, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, uint_t, T_Scl, T_Scl*, uint_t)
instantiate_hem_x_gem(real_t);
instantiate_hem_x_gem(real4_t);
instantiate_hem_x_gem(complex_t);
instantiate_hem_x_gem(complex8_t);
#undef instantiate_hem_x_gem
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_gem(uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		op_t opA, const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
		op_t opB, const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
		T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	uint_t mA = (opA == op_t::N ? m : k);
	uint_t nA = (opA == op_t::N ? k : m);
	uint_t mB = (opB == op_t::N ? k : n);
	uint_t nB = (opB == op_t::N ? n : k);

#if defined(CLA3P_INTEL_MKL)
	mkl::csc_sp2md(alpha,
			opA, mA, nA, colptrA, rowidxA, valuesA,
			opB, mB, nB, colptrB, rowidxB, valuesB,
			beta, c, ldc);
#elif defined(CLA3P_ARMPL)
	armpl::csc_spmm(alpha,
			opA, mA, nA, colptrA, rowidxA, valuesA,
			opB, mB, nB, colptrB, rowidxB, valuesB,
			beta, c, ldc);
#else
	throw err::InvalidOp(msg::MissingIntelMKL());
#endif
}
/*-------------------------------------------------*/
#define instantiate_gem_x_gem(T_Scl) \
template void gem_x_gem(uint_t, uint_t, uint_t, T_Scl, \
		op_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, const int_t*, const int_t*, const T_Scl*, \
		T_Scl, T_Scl*, uint_t)
instantiate_gem_x_gem(real_t);
instantiate_gem_x_gem(real4_t);
instantiate_gem_x_gem(complex_t);
instantiate_gem_x_gem(complex8_t);
#undef instantiate_gem_x_gem
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_gem(uint_t m, uint_t n, uint_t k,
		op_t opA, const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
		op_t opB, const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	uint_t mA = (opA == op_t::N ? m : k);
	uint_t nA = (opA == op_t::N ? k : m);
	uint_t mB = (opB == op_t::N ? k : n);
	uint_t nB = (opB == op_t::N ? n : k);

#if defined(CLA3P_INTEL_MKL)
	mkl::csc_sp2m(
			opA, mA, nA, colptrA, rowidxA, valuesA,
			opB, mB, nB, colptrB, rowidxB, valuesB,
			colptrC, rowidxC, valuesC);
#elif defined(CLA3P_ARMPL)
	armpl::csc_spmm(T_Scalar(1),
			opA, mA, nA, colptrA, rowidxA, valuesA,
			opB, mB, nB, colptrB, rowidxB, valuesB,
			colptrC, rowidxC, valuesC);
#else
	throw err::InvalidOp(msg::MissingThirdParty());
#endif
}
/*-------------------------------------------------*/
#define instantiate_gem_x_gem(T_Scl) \
template void gem_x_gem(uint_t, uint_t, uint_t, \
		op_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_gem_x_gem(real_t);
instantiate_gem_x_gem(real4_t);
instantiate_gem_x_gem(complex_t);
instantiate_gem_x_gem(complex8_t);
#undef instantiate_gem_x_gem
/*-------------------------------------------------*/
} // namespace csc
} // namespace blk
} // namespace cla3p
/*-------------------------------------------------*/
