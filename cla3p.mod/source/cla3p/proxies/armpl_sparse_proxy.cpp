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
#include "cla3p/proxies/armpl_sparse_proxy.hpp"

// system

// 3rd
#include <armpl.h>

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/csc.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace armpl {
/*-------------------------------------------------*/
static void armpl_status_check(armpl_status_t info)
{
	if(info == ARMPL_STATUS_INPUT_PARAMETER_ERROR) { 

		throw err::NoConsistency("ArmPL input parameter error"); 

	} else if(info == ARMPL_STATUS_EXECUTION_FAILURE) { 

		throw err::NoConsistency("ArmPL error during execution"); 

	} else if(info != ARMPL_STATUS_SUCCESS) { 

		throw err::NoConsistency("ArmPL unknown error");

	}
}
/*-------------------------------------------------*/
#define armpl_sparse_create_dns_macro(T_Scl, suffix) \
static void armpl_sparse_create_dns(armpl_spmat_t* mat, uint_t m, uint_t n, const T_Scl *a, uint_t lda) \
{ \
	armpl_status_t info = armpl_spmat_create_dense_##suffix(mat, ARMPL_COL_MAJOR, m, n, lda, a, ARMPL_SPARSE_CREATE_NOCOPY); \
	armpl_status_check(info); \
}
armpl_sparse_create_dns_macro(real_t, d)
armpl_sparse_create_dns_macro(real4_t, s)
armpl_sparse_create_dns_macro(complex_t, z)
armpl_sparse_create_dns_macro(complex8_t, c)
#undef armpl_sparse_create_dns_macro
/*-------------------------------------------------*/
#define armpl_sparse_create_csc_macro(T_Scl, suffix) \
static void armpl_sparse_create_csc(armpl_spmat_t* mat, uint_t m, uint_t n, const int_t *colptr, const int_t *rowidx, const T_Scl *values) \
{ \
	armpl_status_t info = armpl_spmat_create_csc_##suffix(mat, m, n, rowidx, colptr, values, ARMPL_SPARSE_CREATE_NOCOPY); \
	armpl_status_check(info); \
}
armpl_sparse_create_csc_macro(real_t, d)
armpl_sparse_create_csc_macro(real4_t, s)
armpl_sparse_create_csc_macro(complex_t, z)
armpl_sparse_create_csc_macro(complex8_t, c)
#undef armpl_sparse_create_csc_macro
/*-------------------------------------------------*/
#define armpl_sparse_create_csr_macro(T_Scl, suffix) \
static void armpl_sparse_create_csr(armpl_spmat_t* mat, uint_t m, uint_t n, const int_t *rowptr, const int_t *colidx, const T_Scl *values) \
{ \
	armpl_status_t info = armpl_spmat_create_csr_##suffix(mat, m, n, rowptr, colidx, values, ARMPL_SPARSE_CREATE_NOCOPY); \
	armpl_status_check(info); \
}
armpl_sparse_create_csr_macro(real_t, d)
armpl_sparse_create_csr_macro(real4_t, s)
armpl_sparse_create_csr_macro(complex_t, z)
armpl_sparse_create_csr_macro(complex8_t, c)
#undef armpl_sparse_create_csr_macro
/*-------------------------------------------------*/
#define armpl_sparse_export_dns_macro(T_Scl, suffix) \
static void armpl_sparse_export_dns(const armpl_spmat_t mat, int_t *m, int_t *n, T_Scl **a) \
{ \
	armpl_status_t info = armpl_spmat_export_dense_##suffix(mat, ARMPL_COL_MAJOR, m, n, a); \
	armpl_status_check(info); \
}
armpl_sparse_export_dns_macro(real_t, d)
armpl_sparse_export_dns_macro(real4_t, s)
armpl_sparse_export_dns_macro(complex_t, z)
armpl_sparse_export_dns_macro(complex8_t, c)
#undef armpl_sparse_export_dns_macro
/*-------------------------------------------------*/
#define armpl_sparse_export_csc_macro(T_Scl, suffix) \
static void armpl_sparse_export_csc(const armpl_spmat_t mat, int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scl **values) \
{ \
	armpl_status_t info = armpl_spmat_export_csc_##suffix(mat, 0, m, n, rowidx, colptr, values); \
	armpl_status_check(info); \
}
armpl_sparse_export_csc_macro(real_t, d)
armpl_sparse_export_csc_macro(real4_t, s)
armpl_sparse_export_csc_macro(complex_t, z)
armpl_sparse_export_csc_macro(complex8_t, c)
#undef armpl_sparse_export_csc_macro
/*-------------------------------------------------*/
#define armpl_sparse_export_csr_macro(T_Scl, suffix) \
static void armpl_sparse_export_csr(const armpl_spmat_t mat, int_t *m, int_t *n, int_t **rowptr, int_t **colidx, T_Scl **values) \
{ \
	armpl_status_t info = armpl_spmat_export_csr_##suffix(mat, 0, m, n, rowptr, colidx, values); \
	armpl_status_check(info); \
}
armpl_sparse_export_csr_macro(real_t, d)
armpl_sparse_export_csr_macro(real4_t, s)
armpl_sparse_export_csr_macro(complex_t, z)
armpl_sparse_export_csr_macro(complex8_t, c)
#undef armpl_sparse_export_csr_macro
/*-------------------------------------------------*/
static enum armpl_sparse_hint_value opToHint(op_t op)
{
	if(op == op_t::N) return ARMPL_SPARSE_OPERATION_NOTRANS;
	if(op == op_t::T) return ARMPL_SPARSE_OPERATION_TRANS;
	if(op == op_t::C) return ARMPL_SPARSE_OPERATION_CONJTRANS;

	throw err::NoConsistency("Could not convert op_t to sparse hint");

	return ARMPL_SPARSE_OPERATION_NOTRANS;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static enum armpl_sparse_hint_value scalarToHint(T_Scalar alpha)
{
	if(alpha == T_Scalar(0)) return ARMPL_SPARSE_SCALAR_ZERO;
	if(alpha == T_Scalar(1)) return ARMPL_SPARSE_SCALAR_ONE;

	return ARMPL_SPARSE_SCALAR_ANY;
}
/*-------------------------------------------------*/
#if 0
typedef struct ArmplSparseMatrixHint {

	enum armpl_sparse_hint_type type;
	enum armpl_sparse_hint_value value;

} ArmplSparseMatrixHints;
/*-------------------------------------------------*/
static ArmplSparseMatrixHint propToHint(prop_t prop)
{
	ArmplSparseMatrixHint ret = {ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_UNSTRUCTURED};

	/**/ if(prop == prop_t::General   ) ret.value = ARMPL_SPARSE_STRUCTURE_UNSTRUCTURED;
	else if(prop == prop_t::Symmetric ) ret.value = ARMPL_SPARSE_STRUCTURE_SYMMETRIC;
	else if(prop == prop_t::Hermitian ) ret.value = ARMPL_SPARSE_STRUCTURE_HERMITIAN;
	else if(prop == prop_t::Triangular) ret.value = ARMPL_SPARSE_STRUCTURE_TRIANGULAR;
	else throw err::NoConsistency("Could not convert prop_t to sprse matrix hint");

	return ret;
}
#endif
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
class ArmPlMatrix {

	public:
		ArmPlMatrix() {}

		ArmPlMatrix(uint_t m, uint_t n)
		{
			mat() = armpl_spmat_create_null(m, n);
		}

		~ArmPlMatrix()
		{
			armpl_status_t info = ARMPL_STATUS_SUCCESS;
			info = armpl_spmat_destroy(mat()); armpl_status_check(info);
		}

		armpl_spmat_t& mat() { return m_mat; };
		const armpl_spmat_t& mat() const { return m_mat; };

	private:
		armpl_spmat_t m_mat;
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class DnsMatrix : public ArmPlMatrix {

	public:
		DnsMatrix() = default;
		~DnsMatrix() = default;

		DnsMatrix(uint_t m, uint_t n)
			: ArmPlMatrix(m, n)
		{
			armpl_status_t info = ARMPL_STATUS_SUCCESS;
			info = armpl_spmat_hint(mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_DENSE); armpl_status_check(info);
			//info = armpl_spmat_hint(mat(), ARMPL_SPARSE_HINT_MEMORY, ARMPL_SPARSE_MEMORY_NOALLOCS); armpl_status_check(info);
		}

		DnsMatrix(uint_t m, uint_t n, const T_Scalar *a, uint_t lda)
		{
			armpl_sparse_create_dns(&mat(), m, n, a, lda);
		}

		void exportd(T_Scalar *c, uint_t ldc)
		{
			// This is stupid...
			int_t m = 0;
			int_t n = 0;
			T_Scalar *res = nullptr;
			armpl_sparse_export_dns(mat(), &m, &n, &res);
			blk::dns::copy(uplo_t::Full, m, n, res, m, c, ldc);
			std::free(res);
		}

		void exportd(uint_t *m, uint_t *n, T_Scalar *c, uint_t ldc)
		{
			// This is stupid...
			T_Scalar *res = nullptr;
			armpl_sparse_export_dns(mat(), m, n, &res);

			blk::dns::copy(uplo_t::Full, *m, *n, res, *m, c, ldc);
			std::free(res);
		}
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
class CsxMatrix : public ArmPlMatrix {

	public:
		CsxMatrix() = default;
		~CsxMatrix() = default;

		CsxMatrix(uint_t m, uint_t n)
			: ArmPlMatrix(m, n)
		{
			armpl_status_t info = ARMPL_STATUS_SUCCESS;
			info = armpl_spmat_hint(mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_UNSTRUCTURED); armpl_status_check(info);
		}

		// Use this class to separate from dense cases
		// Perhaps some sparse-only options will be added in the future
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class CsrMatrix : public CsxMatrix {

	public:
		CsrMatrix() = default;
		~CsrMatrix() = default;

		CsrMatrix(uint_t m, uint_t n) : CsxMatrix(m, n) {}

		CsrMatrix(uint_t m, uint_t n, const int_t *rowptr, const int_t *colidx, const T_Scalar *values)
		{
			armpl_sparse_create_csr(&mat(), m, n, rowptr, colidx, values);
		}

		void export3(int_t *m, int_t *n, int_t **rowptr, int_t **colidx, T_Scalar **values) const
		{
			armpl_sparse_export_csr(mat(), m, n, rowptr, colidx, values);
		}

		void export3(int_t **rowptr, int_t **colidx, T_Scalar **values) const
		{
			int_t m = 0;
			int_t n = 0;
			export3(&m, &n, rowptr, colidx, values);
		}
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class CscMatrix : public CsxMatrix {

	public:
		CscMatrix() = default;
		~CscMatrix() = default;

		CscMatrix(uint_t m, uint_t n) : CsxMatrix(m, n) {}

		CscMatrix(uint_t m, uint_t n, const int_t *colptr, const int_t *rowidx, const T_Scalar *values)
		{
			armpl_sparse_create_csc(&mat(), m, n, colptr, rowidx, values);
		}

		void export3(int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scalar **values) const
		{
			armpl_sparse_export_csc(mat(), m, n, colptr, rowidx, values);
		}

		void export3(int_t **colptr, int_t **rowidx, T_Scalar **values) const
		{
			int_t m = 0;
			int_t n = 0;
			export3(&m, &n, colptr, rowidx, values);
		}
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#define armpl_sparse_add_macro(T_Scl, suffix) \
static void armpl_sparse_add( \
		const T_Scl                  alpha, \
		enum armpl_sparse_hint_value opA  , \
		const armpl_spmat_t          A    , \
		const T_Scl                  beta , \
		enum armpl_sparse_hint_value opB  , \
		const armpl_spmat_t          B    , \
		armpl_spmat_t                C    ) \
{ \
	armpl_status_t info = armpl_spadd_exec_##suffix(opA, opB, alpha, A, beta, B, C); \
	armpl_status_check(info); \
}
armpl_sparse_add_macro(real_t, d)
armpl_sparse_add_macro(real4_t, s)
armpl_sparse_add_macro(complex_t, z)
armpl_sparse_add_macro(complex8_t, c)
#undef armpl_sparse_add_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_add(uint_t m, uint_t n,
		T_Scalar alpha, op_t opA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		T_Scalar beta, op_t opB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	int_t mA = (opA == op_t::N ? m : n);
	int_t nA = (opA == op_t::N ? n : m);
	int_t mB = (opB == op_t::N ? m : n);
	int_t nB = (opB == op_t::N ? n : m);

	CscMatrix<T_Scalar> A(mA, nA, colptrA, rowidxA, valuesA);
	CscMatrix<T_Scalar> B(mB, nB, colptrB, rowidxB, valuesB);
	CscMatrix<T_Scalar> C(m, n);

	enum armpl_sparse_hint_value transA = opToHint(opA);
	enum armpl_sparse_hint_value transB = opToHint(opB);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;

	// hints for A
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPADD_OPERATION, transA); armpl_status_check(info);
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPADD_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	// hints for B
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPADD_OPERATION, transB); armpl_status_check(info);
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPADD_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	info = armpl_spadd_optimize(transA, transB, scalarToHint(alpha), A.mat(), scalarToHint(beta), B.mat(), C.mat()); armpl_status_check(info);

	armpl_sparse_add(alpha, transA, A.mat(), beta, transB, B.mat(), C.mat());

	C.export3(colptrC, rowidxC, valuesC);
}
/*-------------------------------------------------*/
#define instantiate_csc_add(T_Scl) \
template void csc_add(uint_t, uint_t, \
		T_Scl, op_t, const int_t*, const int_t*, const T_Scl*, \
		T_Scl, op_t, const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_csc_add(real_t);
instantiate_csc_add(real4_t);
instantiate_csc_add(complex_t);
instantiate_csc_add(complex8_t);
#undef instantiate_csc_add
/*-------------------------------------------------*/
template <typename T_Scalar>
static void revert_duplicated_diagonal(bool conjop, uint_t n, T_Scalar alpha,
	const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
	uint_t k, const T_Scalar *b, uint_t ldb, T_Scalar *c, uint_t ldc)
{
	for (int_t j = 0; j < static_cast<int_t>(n); j++) {
		for (int_t irow = colptr[j]; irow < colptr[j + 1]; irow++) {
			if (rowidx[irow] == j) {
				T_Scalar Ajj = conjop ? T_Scalar(arith::getRe(values[irow])): values[irow];
				for (uint_t l = 0; l < k; l++) {
					blk::dns::entry(ldc, c, j, l) -= alpha * Ajj * blk::dns::entry(ldb, b, j, l);
				} // l
			} // diag
		} // irow
	} // j
}
/*-------------------------------------------------*/
#define armpl_sparse_mv_macro(T_Scl, suffix) \
static void armpl_sparse_mv( \
	enum armpl_sparse_hint_value op   , \
	const T_Scl                  alpha, \
	armpl_spmat_t                A    , \
	const T_Scl*                 x    , \
	const T_Scl                  beta , \
	T_Scl*                       y    ) \
{ \
	armpl_status_t info = armpl_spmv_exec_##suffix(op, alpha, A, x, beta, y); \
	armpl_status_check(info); \
}
armpl_sparse_mv_macro(real_t, d)
armpl_sparse_mv_macro(real4_t, s)
armpl_sparse_mv_macro(complex_t, z)
armpl_sparse_mv_macro(complex8_t, c)
#undef armpl_sparse_mv_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mv(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
	const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
	const T_Scalar* x, T_Scalar beta, T_Scalar *y)
{
	CscMatrix<T_Scalar> A(m, n, colptrA, rowidxA, valuesA);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;
	enum armpl_sparse_hint_value trans;

	Property prA(propA, uploA);

	if(prA.isGeneral() || prA.isTriangular()) {

		trans = opToHint(opA);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, trans); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		armpl_sparse_mv(trans, alpha, A.mat(), x, beta, y);

	} else if(prA.isSymmetric()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta * y + alpha * tri(A) * x
		trans = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, trans); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		armpl_sparse_mv(trans, alpha, A.mat(), x, beta, y);

		// y := y + alpha * tri(A)' * x
		trans = opToHint(op_t::T);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, trans); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		armpl_sparse_mv(trans, alpha, A.mat(), x, T_Scalar(1), y);

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(false, n, alpha, colptrA, rowidxA, valuesA, 1, x, n, y, m); // m = n

	} else if(prA.isHermitian()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta * y + alpha * tri(A) * x
		trans = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, trans); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		armpl_sparse_mv(trans, alpha, A.mat(), x, beta, y);

		// y := y + alpha * tri(A)' * x
		trans = opToHint(op_t::C);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, trans); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		armpl_sparse_mv(trans, alpha, A.mat(), x, T_Scalar(1), y);

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(true, n, alpha, colptrA, rowidxA, valuesA, 1, x, n, y, m); // m = n

	} else {

		throw err::NoConsistency(prA.name() + " matrices are not supported in sparse algebra");

	} // prop
}
/*-------------------------------------------------*/
#define instantiate_csc_mv(T_Scl) \
template void csc_mv(prop_t, uplo_t, uint_t, uint_t, T_Scl, op_t, \
		const int_t*, const int_t*, const T_Scl*, \
		const T_Scl*, T_Scl, T_Scl*)
instantiate_csc_mv(real_t);
instantiate_csc_mv(real4_t);
instantiate_csc_mv(complex_t);
instantiate_csc_mv(complex8_t);
#undef instantiate_csc_mv
/*-------------------------------------------------*/
#define armpl_sparse_spmm_macro(T_Scl, suffix) \
static void armpl_sparse_spmm( \
				T_Scl                        alpha, \
				enum armpl_sparse_hint_value opA  , \
				armpl_spmat_t                A    , \
				enum armpl_sparse_hint_value opB  , \
				armpl_spmat_t                B    , \
				T_Scl                        beta , \
				armpl_spmat_t                C    ) \
{ \
	armpl_status_t info = armpl_spmm_exec_##suffix(opA, opB, alpha, A, B, beta, C); \
	armpl_status_check(info); \
}
armpl_sparse_spmm_macro(real_t, d)
armpl_sparse_spmm_macro(real4_t, s)
armpl_sparse_spmm_macro(complex_t, z)
armpl_sparse_spmm_macro(complex8_t, c)
#undef armpl_sparse_spmm_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mm(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		uint_t k, const T_Scalar* b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
#if 0 // USE_SPMM using spmm forces copying back to c, also SYM/HEM flags do not semm to work...
                                                     
	uint_t mB = (opA == op_t::N ? n : m);                   
	uint_t mC = (opA == op_t::N ? m : n);               
                                                         
	blk::dns::scale(uplo_t::Full, mC, k, c, ldc, beta);
	beta = T_Scalar(1);                                     
                                                         
	CscMatrix<T_Scalar> A(m, n, colptrA, rowidxA, valuesA);
	DnsMatrix<T_Scalar> B(mB, k, b, ldb);
	DnsMatrix<T_Scalar> C(mC, k, c, ldc);
	enum armpl_sparse_hint_value transB = opToHint(op_t::N);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;
	enum armpl_sparse_hint_value transA;

	Property prA(propA, uploA);

	if (prA.isGeneral() || prA.isTriangular()) {

		transA = opToHint(opA);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transB); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);
		info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);		
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());
		C.exportd(c, ldc);

	} else if (prA.isSymmetric()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);
		info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);
		info = armpl_spmat_hint(C.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta (=1) * y + alpha * tri(A) * x
		transA = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());

		// y := beta (=1) * y + alpha * tri(A)' * x
		transA = opToHint(op_t::T);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());

		C.exportd(c, ldc);

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(false, n, alpha, colptrA, rowidxA, valuesA, k, b, ldb, c, ldc);

	} else if (prA.isHermitian()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);
		info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);
		info = armpl_spmat_hint(C.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta * y + alpha * tri(A) * x
		transA = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());

		// y := y + alpha * tri(A)' * x
		beta = T_Scalar(1);
		transA = opToHint(op_t::C);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());

		C.exportd(c, ldc);

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(true, n, alpha, colptrA, rowidxA, valuesA, k, b, ldb, c, ldc);

	} else {

		throw err::NoConsistency(prA.name() + " matrices are not supported in sparse algebra");

	} // prop

#else // USE_SPMM

	CscMatrix<T_Scalar> A(m, n, colptrA, rowidxA, valuesA);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;
	enum armpl_sparse_hint_value transA;

	Property prA(propA, uploA);

	if (prA.isGeneral() || prA.isTriangular()) {

		transA = opToHint(opA);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMV_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_MANY); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		// TODO: omp
		for (uint_t l = 0; l < k; l++) {
			armpl_sparse_mv(transA, alpha, A.mat(), blk::dns::ptrmv(ldb, b, 0, l), beta, blk::dns::ptrmv(ldc, c, 0, l));
		} // l

	} else if (prA.isSymmetric()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta * y + alpha * tri(A) * x
		transA = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		// TODO: omp
		for (uint_t l = 0; l < k; l++) {
			armpl_sparse_mv(transA, alpha, A.mat(), blk::dns::ptrmv(ldb, b, 0, l), beta, blk::dns::ptrmv(ldc, c, 0, l));
		} // l

		// y := y + alpha * tri(A)' * x
		transA = opToHint(op_t::T);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		// TODO: omp
		for (uint_t l = 0; l < k; l++) {
			armpl_sparse_mv(transA, alpha, A.mat(), blk::dns::ptrmv(ldb, b, 0, l), T_Scalar(1), blk::dns::ptrmv(ldc, c, 0, l));
		} // l

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(false, n, alpha, colptrA, rowidxA, valuesA, k, b, ldb, c, ldc);

	} else if (prA.isHermitian()) {

		//info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_STRUCTURE, ARMPL_SPARSE_STRUCTURE_TRIANGULAR); armpl_status_check(info);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_FEW); armpl_status_check(info);

		// y := beta * y + alpha * tri(A) * x
		transA = opToHint(op_t::N);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		// TODO: omp
		for (uint_t l = 0; l < k; l++) {
			armpl_sparse_mv(transA, alpha, A.mat(), blk::dns::ptrmv(ldb, b, 0, l), beta, blk::dns::ptrmv(ldc, c, 0, l));
		} // l

		// y := y + alpha * tri(A)' * x
		transA = opToHint(op_t::C);
		info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
		info = armpl_spmv_optimize(A.mat()); armpl_status_check(info);
		// TODO: omp
		for (uint_t l = 0; l < k; l++) {
			armpl_sparse_mv(transA, alpha, A.mat(), blk::dns::ptrmv(ldb, b, 0, l), T_Scalar(1), blk::dns::ptrmv(ldc, c, 0, l));
		} // l

		// y := y - alpha * diag(A) * x
		revert_duplicated_diagonal(true, n, alpha, colptrA, rowidxA, valuesA, k, b, ldb, c, ldc);

	} else {

		throw err::NoConsistency(prA.name() + " matrices are not supported in sparse algebra");

	} // prop
#endif // USE_SPMM
}
/*-------------------------------------------------*/
#define instantiate_csc_mm(T_Scl) \
template void csc_mm(prop_t, uplo_t, uint_t, uint_t, T_Scl, op_t, \
		const int_t*, const int_t*, const T_Scl*, \
		uint_t, const T_Scl*, uint_t, T_Scl, T_Scl*, uint_t)
instantiate_csc_mm(real_t);
instantiate_csc_mm(real4_t);
instantiate_csc_mm(complex_t);
instantiate_csc_mm(complex8_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_spmm(T_Scalar alpha,
    op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
    op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
    int_t** colptrC, int_t** rowidxC, T_Scalar** valuesC)
{
	int_t mC = (opA == op_t::N ? mA : nA);
	int_t nC = (opB == op_t::N ? nB : mB);

	CscMatrix<T_Scalar> A(mA, nA, colptrA, rowidxA, valuesA);
	CscMatrix<T_Scalar> B(mB, nB, colptrB, rowidxB, valuesB);
	CscMatrix<T_Scalar> C(mC, nC);

	T_Scalar beta = T_Scalar(0);

	enum armpl_sparse_hint_value transA = opToHint(opA);
	enum armpl_sparse_hint_value transB = opToHint(opB);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;

	// hints for A
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	// hints for B
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transB); armpl_status_check(info);
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);

	armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());

	C.export3(colptrC, rowidxC, valuesC);

	blk::csc::sort(nC, *colptrC, *rowidxC, *valuesC);
}
/*-------------------------------------------------*/
#define instantiate_spmm(T_Scl) \
template void csc_spmm( T_Scl, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_spmm(real_t);
instantiate_spmm(real4_t);
instantiate_spmm(complex_t);
instantiate_spmm(complex8_t);
#undef instantiate_spmm
/*-------------------------------------------------*/
template <typename T_Scalar>
static void add_to_zero_dense(const CscMatrix<T_Scalar>& C, T_Scalar *c, uint_t ldc)
{
	int_t m = 0;
	int_t n = 0;
	int_t *colptr = nullptr;
	int_t *rowidx = nullptr;
	T_Scalar* values = nullptr;
	C.export3(&m, &n, &colptr, &rowidx, &values);

	blk::dns::zero(uplo_t::Full, m, n, c, ldc);

	for (int_t j = 0; j < static_cast<int_t>(n); j++) {
		for (int_t irow = colptr[j]; irow < colptr[j + 1]; irow++) {
			int_t i = rowidx[irow];
			T_Scalar v = values[irow];
			blk::dns::entry(ldc,c,i,j) += v;
		} // irow
	} // j

	std::free(colptr);
	std::free(rowidx);
	std::free(values);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_spmm(T_Scalar alpha,
    op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
    op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
    T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	uint_t mC = (opA == op_t::N ? mA : nA);
	uint_t nC = (opB == op_t::N ? nB : mB);

	CscMatrix<T_Scalar> A(mA, nA, colptrA, rowidxA, valuesA);
	CscMatrix<T_Scalar> B(mB, nB, colptrB, rowidxB, valuesB);

	enum armpl_sparse_hint_value transA = opToHint(opA);
	enum armpl_sparse_hint_value transB = opToHint(opB);

	armpl_status_t info = ARMPL_STATUS_SUCCESS;

	// hints for A
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transA); armpl_status_check(info);
	info = armpl_spmat_hint(A.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	// hints for B
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_OPERATION, transB); armpl_status_check(info);
	info = armpl_spmat_hint(B.mat(), ARMPL_SPARSE_HINT_SPMM_INVOCATIONS, ARMPL_SPARSE_INVOCATIONS_SINGLE); armpl_status_check(info);

	if(beta == T_Scalar(0)) {
#if 0
		// For some reason this does not work
		// Also does not work for beta = 1 & c = 0
		DnsMatrix<T_Scalar> C(mC, nC);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());
		C.exportd(c, ldc);
#else
		CscMatrix<T_Scalar> C(mC, nC);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(T_Scalar(0)), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), T_Scalar(0), C.mat());
		add_to_zero_dense(C, c, ldc);
#endif
	} else {
		DnsMatrix<T_Scalar> C(mC, nC, c, ldc);
		info = armpl_spmm_optimize(transA, transB, scalarToHint(alpha), A.mat(), B.mat(), scalarToHint(beta), C.mat()); armpl_status_check(info);
		armpl_sparse_spmm(alpha, transA, A.mat(), transB, B.mat(), beta, C.mat());
		C.exportd(c, ldc);
	} // beta
}
/*-------------------------------------------------*/
#define instantiate_spmm(T_Scl) \
template void csc_spmm(T_Scl, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		T_Scl, T_Scl*, uint_t)
instantiate_spmm(real_t);
instantiate_spmm(real4_t);
instantiate_spmm(complex_t);
instantiate_spmm(complex8_t);
#undef instantiate_spmm
/*-------------------------------------------------*/
} // namespace armpl
} // namespace cla3p
/*-------------------------------------------------*/
