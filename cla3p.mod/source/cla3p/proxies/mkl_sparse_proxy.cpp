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
#include "cla3p/proxies/mkl_sparse_proxy.hpp"

// system
#include <algorithm>

// 3rd
#include <mkl_spblas.h>

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/csc.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/
static void mkl_sparse_status_check(sparse_status_t ierr)
{
	if(ierr == SPARSE_STATUS_NOT_INITIALIZED) { 

		throw err::NoConsistency("MKL sparse handle is empty"); 

	} else if(ierr == SPARSE_STATUS_ALLOC_FAILED) { 

		throw err::OutOfMemory("MKL sparse handle not enough memory"); 

	} else if(ierr == SPARSE_STATUS_INVALID_VALUE) { 

		throw err::NoConsistency("MKL sparse handle input error"); 

	} else if(ierr == SPARSE_STATUS_EXECUTION_FAILED) { 

		throw err::NoConsistency("MKL sparse handle numerical error"); 

	} else if(ierr == SPARSE_STATUS_INTERNAL_ERROR) { 

		throw err::NoConsistency("MKL sparse handle internal error"); 

	} else if(ierr == SPARSE_STATUS_NOT_SUPPORTED) { 

		throw err::NoConsistency("MKL sparse handle operation not supported"); 

	} else if(ierr != SPARSE_STATUS_SUCCESS) { 

		throw err::NoConsistency("MKL sparse handle unknown error");

	}
}
/*-------------------------------------------------*/
#define mkl_sparse_create_csc_macro(T_Scl, prefix) \
static void mkl_sparse_create_csc(sparse_matrix_t* mat, uint_t m, uint_t n, int_t *colptr, int_t *rowidx, T_Scl *values) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_create_csc(mat, SPARSE_INDEX_BASE_ZERO, m, n, colptr, colptr + 1, rowidx, values); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_create_csc_macro(real_t, d)
mkl_sparse_create_csc_macro(real4_t, s)
mkl_sparse_create_csc_macro(complex_t, z)
mkl_sparse_create_csc_macro(complex8_t, c)
#undef mkl_sparse_create_csc_macro
/*-------------------------------------------------*/
#define mkl_sparse_create_csr_macro(T_Scl, prefix) \
static void mkl_sparse_create_csr(sparse_matrix_t* mat, uint_t m, uint_t n, int_t *rowptr, int_t *colidx, T_Scl *values) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_create_csr(mat, SPARSE_INDEX_BASE_ZERO, m, n, rowptr, rowptr + 1, colidx, values); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_create_csr_macro(real_t, d)
mkl_sparse_create_csr_macro(real4_t, s)
mkl_sparse_create_csr_macro(complex_t, z)
mkl_sparse_create_csr_macro(complex8_t, c)
#undef mkl_sparse_create_csr_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
static void copy_csx4_to_csx3(uint_t n, sparse_index_base_t indexing,
		const int_t    *csxbgn4, 
		const int_t    *csxend4, 
		const int_t    *csxidx4, 
		const T_Scalar *values4,
		int_t    **csxptr, 
		int_t    **csxidx, 
		T_Scalar **values)
{
	int_t *csxptr3 = i_malloc<int_t>(n+1);

	csxptr3[0] = 0;
	for(uint_t j = 0; j < n; j++) {
		csxptr3[j+1] = csxptr3[j] + (csxend4[j] - csxbgn4[j]);
	} // j

	int_t nnz = csxptr3[n];

	int_t    *csxidx3 = i_malloc<int_t>(nnz);
	T_Scalar *values3 = i_malloc<T_Scalar>(nnz);

	for(uint_t j = 0; j < n; j++) {
		int_t ibgn4 = csxbgn4[j] - csxbgn4[0];
		int_t iend4 = csxend4[j] - csxbgn4[0];
		int_t ibgn3 = csxptr3[j];
		std::copy(csxidx4 + ibgn4, csxidx4 + iend4, csxidx3 + ibgn3);
		std::copy(values4 + ibgn4, values4 + iend4, values3 + ibgn3);
	} // j
	
	if(indexing == SPARSE_INDEX_BASE_ONE) {
		std::for_each(csxidx3, csxidx3 + nnz, [](int_t& i) { i--; });
	} // indexing

	*csxptr = csxptr3;
	*csxidx = csxidx3;
	*values = values3;
}
/*-------------------------------------------------*/
#define mkl_sparse_export_csc_macro(T_Scl, prefix) \
static void mkl_sparse_export_csc(const sparse_matrix_t mat, int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scl **values) \
{ \
	sparse_index_base_t indexing; \
	int_t *colbgn4 = nullptr; \
	int_t *colend4 = nullptr; \
	int_t *rowidx4 = nullptr;\
	T_Scl *values4 = nullptr;\
	sparse_status_t ierr = mkl_sparse_##prefix##_export_csc(mat, &indexing, m, n, &colbgn4, &colend4, &rowidx4, &values4); \
	mkl_sparse_status_check(ierr); \
	copy_csx4_to_csx3(*n, indexing, colbgn4, colend4, rowidx4, values4, colptr, rowidx, values); \
}
mkl_sparse_export_csc_macro(real_t, d)
mkl_sparse_export_csc_macro(real4_t, s)
mkl_sparse_export_csc_macro(complex_t, z)
mkl_sparse_export_csc_macro(complex8_t, c)
#undef mkl_sparse_export_csc_macro
/*-------------------------------------------------*/
#define mkl_sparse_export_csr_macro(T_Scl, prefix) \
static void mkl_sparse_export_csr(const sparse_matrix_t mat, int_t *m, int_t *n, int_t **rowptr, int_t **colidx, T_Scl **values) \
{ \
	sparse_index_base_t indexing; \
	int_t *rowbgn4 = nullptr; \
	int_t *rowend4 = nullptr; \
	int_t *colidx4 = nullptr;\
	T_Scl *values4 = nullptr;\
	sparse_status_t ierr = mkl_sparse_##prefix##_export_csr(mat, &indexing, m, n, &rowbgn4, &rowend4, &colidx4, &values4); \
	mkl_sparse_status_check(ierr); \
	copy_csx4_to_csx3(*m, indexing, rowbgn4, rowend4, colidx4, values4, rowptr, colidx, values); \
}
mkl_sparse_export_csr_macro(real_t, d)
mkl_sparse_export_csr_macro(real4_t, s)
mkl_sparse_export_csr_macro(complex_t, z)
mkl_sparse_export_csr_macro(complex8_t, c)
#undef mkl_sparse_export_csr_macro
/*-------------------------------------------------*/
static sparse_operation_t opToSparseTrans(op_t op)
{
	if(op == op_t::N) return SPARSE_OPERATION_NON_TRANSPOSE;
	if(op == op_t::T) return SPARSE_OPERATION_TRANSPOSE;
	if(op == op_t::C) return SPARSE_OPERATION_CONJUGATE_TRANSPOSE;

	throw err::NoConsistency("Could not convert op_t to sparse operation");

	return SPARSE_OPERATION_NON_TRANSPOSE;
}
/*-------------------------------------------------*/
static sparse_matrix_type_t propToDescrType(prop_t prop)
{
	if(prop == prop_t::General   ) return SPARSE_MATRIX_TYPE_GENERAL   ;
	if(prop == prop_t::Symmetric ) return SPARSE_MATRIX_TYPE_SYMMETRIC ;
	if(prop == prop_t::Hermitian ) return SPARSE_MATRIX_TYPE_HERMITIAN ;
	if(prop == prop_t::Triangular) return SPARSE_MATRIX_TYPE_TRIANGULAR;

	throw err::NoConsistency("Could not convert prop_t to matrix descriptor");

	return SPARSE_MATRIX_TYPE_GENERAL;
}
/*-------------------------------------------------*/
static sparse_fill_mode_t uploToDescrMode(uplo_t uplo)
{
	if(uplo == uplo_t::Full ) return SPARSE_FILL_MODE_FULL ;
	if(uplo == uplo_t::Upper) return SPARSE_FILL_MODE_UPPER;
	if(uplo == uplo_t::Lower) return SPARSE_FILL_MODE_LOWER;

	throw err::NoConsistency("Could not convert uplo_t to matrix descriptor");

	return SPARSE_FILL_MODE_FULL;
}
/*-------------------------------------------------*/
static struct matrix_descr create_descriptor(const Property& pr)
{
	matrix_descr ret;
	ret.type = propToDescrType(pr.type());
	ret.mode = uploToDescrMode(pr.uplo());
	ret.diag = SPARSE_DIAG_NON_UNIT;

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class CsxMatrix {

	public:
		CsxMatrix();
		~CsxMatrix();

		sparse_matrix_t& mat();
		const sparse_matrix_t& mat() const;

		struct matrix_descr& descr();
		const struct matrix_descr& descr() const;

	private:
		sparse_matrix_t     m_mat;
		struct matrix_descr m_descr;
};
/*-------------------------------------------------*/
template <typename T_Scalar>
CsxMatrix<T_Scalar>::CsxMatrix() 
{
}
/*-------------------------------------------------*/
template <typename T_Scalar>
CsxMatrix<T_Scalar>::~CsxMatrix() 
{
	mkl_sparse_status_check(mkl_sparse_destroy(mat()));
}
/*-------------------------------------------------*/
template <typename T_Scalar>
sparse_matrix_t& CsxMatrix<T_Scalar>::mat()
{ 
	return m_mat; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const sparse_matrix_t& CsxMatrix<T_Scalar>::mat() const 
{
	return m_mat; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
struct matrix_descr& CsxMatrix<T_Scalar>::descr()
{ 
	return m_descr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const struct matrix_descr& CsxMatrix<T_Scalar>::descr() const 
{
	return m_descr; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class CsrMatrix : public CsxMatrix<T_Scalar> {

	public:
		CsrMatrix() = default;
		~CsrMatrix() = default;

		CsrMatrix(uint_t m, uint_t n, int_t *rowptr, int_t *colidx, T_Scalar *values, const Property& pr = Property::General());

		void export3(int_t *m, int_t *n, int_t **rowptr, int_t **colidx, T_Scalar **values) const;
};
/*-------------------------------------------------*/
template <typename T_Scalar>
CsrMatrix<T_Scalar>::CsrMatrix(uint_t m, uint_t n, int_t *rowptr, int_t *colidx, T_Scalar *values, const Property& pr)
{
	mkl_sparse_create_csr(&this->mat(), m, n, rowptr, colidx, values);
	this->descr() = create_descriptor(pr);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void CsrMatrix<T_Scalar>::export3(int_t *m, int_t *n, int_t **rowptr, int_t **colidx, T_Scalar **values) const
{
	mkl_sparse_export_csr(this->mat(), m, n, rowptr, colidx, values);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
class CscMatrix : public CsxMatrix<T_Scalar> {

	public:
		CscMatrix() = default;
		~CscMatrix() = default;

		CscMatrix(uint_t m, uint_t n, int_t *colptr, int_t *rowidx, T_Scalar *values, const Property& pr = Property::General());

		void export3(int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scalar **values) const;
};
/*-------------------------------------------------*/
template <typename T_Scalar>
CscMatrix<T_Scalar>::CscMatrix(uint_t m, uint_t n, int_t *colptr, int_t *rowidx, T_Scalar *values, const Property& pr)
{
	mkl_sparse_create_csc(&this->mat(), m, n, colptr, rowidx, values);
	this->descr() = create_descriptor(pr);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void CscMatrix<T_Scalar>::export3(int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scalar **values) const
{
	mkl_sparse_export_csc(this->mat(), m, n, colptr, rowidx, values);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#define mkl_sparse_add_macro(T_Scl, prefix) \
static void mkl_sparse_add( \
		const sparse_operation_t op   , \
		const sparse_matrix_t    A    , \
		T_Scl                    alpha, \
		const sparse_matrix_t    B    , \
		sparse_matrix_t*         C    ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_add(op, A, alpha, B, C); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_add_macro(real_t, d)
mkl_sparse_add_macro(real4_t, s)
mkl_sparse_add_macro(complex_t, z)
mkl_sparse_add_macro(complex8_t, c)
#undef mkl_sparse_add_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_add(uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	// 
	// Csr/Csc operations are the same, only csr is supported (like working with the transposes)
	//
	CsrMatrix<T_Scalar> A(n, m, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CsrMatrix<T_Scalar> B(n, m, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));
	CsrMatrix<T_Scalar> C;

	sparse_operation_t transA = opToSparseTrans(opA);

	mkl_sparse_add(transA, A.mat(), alpha, B.mat(), &C.mat());

	int_t mC = 0;
	int_t nC = 0;
	C.export3(&mC, &nC, colptrC, rowidxC, valuesC);
}
/*-------------------------------------------------*/
#define instantiate_csc_add(T_Scl) \
template void csc_add(uint_t, uint_t, T_Scl, op_t, \
		const int_t*, const int_t*, const T_Scl*, \
		const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_csc_add(real_t);
instantiate_csc_add(real4_t);
instantiate_csc_add(complex_t);
instantiate_csc_add(complex8_t);
#undef instantiate_csc_add
/*-------------------------------------------------*/
#define mkl_sparse_mv_macro(T_Scl, prefix) \
static void mkl_sparse_mv( \
				const sparse_operation_t  op   , \
				T_Scl                     alpha, \
				const sparse_matrix_t     A    , \
				const struct matrix_descr descr, \
				const T_Scl*              x    , \
				T_Scl                     beta , \
				T_Scl*                    y    ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_mv(op, alpha, A, descr, x, beta, y); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_mv_macro(real_t, d)
mkl_sparse_mv_macro(real4_t, s)
mkl_sparse_mv_macro(complex_t, z)
mkl_sparse_mv_macro(complex8_t, c)
#undef mkl_sparse_mv_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mv(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		const T_Scalar* x, T_Scalar beta, T_Scalar *y)
{
	Property prA(propA, uploA);
	CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
	sparse_operation_t op = opToSparseTrans(opA);

	mkl_sparse_mv(op, alpha, A.mat(), A.descr(), x, beta, y);
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
#define mkl_sparse_mm_macro(T_Scl, prefix) \
static void mkl_sparse_mm( \
		const sparse_operation_t  op    , \
		T_Scl                     alpha , \
		const sparse_matrix_t     A     , \
		const struct matrix_descr descr , \
		const T_Scl*              b     , \
		const int_t               cols  , \
		const int_t               ldb   , \
		T_Scl                     beta  , \
		T_Scl*                    c     , \
		const int_t               ldc   ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_mm(op, alpha, A, descr, SPARSE_LAYOUT_COLUMN_MAJOR, b, cols, ldb, beta, c, ldc); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_mm_macro(real_t, d)
mkl_sparse_mm_macro(real4_t, s)
mkl_sparse_mm_macro(complex_t, z)
mkl_sparse_mm_macro(complex8_t, c)
#undef mkl_sparse_mm_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mm(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		uint_t k, const T_Scalar* b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	//
	// Have to work with Csr (dense column ordering dependency)
	//

	Property prA(propA, uploA);

	if((prA.isGeneral() || prA.isTriangular()) && opA == op_t::N) {

		prA.switchUplo();
		CsrMatrix<T_Scalar> A(n, m, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
		sparse_operation_t op = opToSparseTrans(op_t::T);
		mkl_sparse_mm(op, alpha, A.mat(), A.descr(), b, k, ldb, beta, c, ldc);

	} else if((prA.isGeneral() || prA.isTriangular()) && opA == op_t::T) {

		prA.switchUplo();
		CsrMatrix<T_Scalar> A(n, m, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
		sparse_operation_t op = opToSparseTrans(op_t::N);
		mkl_sparse_mm(op, alpha, A.mat(), A.descr(), b, k, ldb, beta, c, ldc);

	} else if((prA.isGeneral() || prA.isTriangular()) && opA == op_t::C) {

		CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
		sparse_operation_t op = opToSparseTrans(opA);

		// TODO: use openMP for this loop
		for(uint_t l = 0; l < k; l++) {
			mkl_sparse_mv(op, alpha, A.mat(), A.descr(), blk::dns::ptrmv(ldb,b,0,l), beta, blk::dns::ptrmv(ldc,c,0,l));
		} // l

	} else if(prA.isHermitian()) {
	
		CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
		sparse_operation_t op = opToSparseTrans(opA);
	
		// TODO: use openMP for this loop
		for(uint_t l = 0; l < k; l++) {
			mkl_sparse_mv(op, alpha, A.mat(), A.descr(), blk::dns::ptrmv(ldb,b,0,l), beta, blk::dns::ptrmv(ldc,c,0,l));
		} // l

	} else {

		prA.switchUplo();
		CsrMatrix<T_Scalar> A(n, m, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);

		sparse_operation_t op = opToSparseTrans(opA);
		mkl_sparse_mm(op, alpha, A.mat(), A.descr(), b, k, ldb, beta, c, ldc);

	} // prop / uplo
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
#if 0
template <typename T_Scalar>
void csc_spmm(op_t opA,
		uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t** colptrC, int_t** rowidxC, T_Scalar** valuesC)
{
	CscMatrix<T_Scalar> A(mA, nA, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CscMatrix<T_Scalar> B(mB, nB, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));
	CscMatrix<T_Scalar> C;

	sparse_operation_t op = opToSparseTrans(opA);

	sparse_status_t ierr = mkl_sparse_spmm(op, A.mat(), B.mat(), &C.mat());
	mkl_sparse_status_check(ierr);

	int_t mC = 0;
	int_t nC = 0;
	C.export3(&mC, &nC, colptrC, rowidxC, valuesC);

	blk::csc::sort(nC, *colptrC, *rowidxC, *valuesC);
}
/*-------------------------------------------------*/
#define instantiate_spmm(T_Scl) \
template void csc_spmm(op_t, \
		uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_spmm(real_t);
instantiate_spmm(real4_t);
instantiate_spmm(complex_t);
instantiate_spmm(complex8_t);
#undef instantiate_spmm
#endif
/*-------------------------------------------------*/
#define mkl_sparse_sp2md_macro(T_Scl, prefix) \
static void mkl_sparse_sp2md( \
		const sparse_operation_t  opA   , \
		const struct matrix_descr descrA, \
		const sparse_matrix_t     A     , \
		const sparse_operation_t  opB   , \
		const struct matrix_descr descrB, \
		const sparse_matrix_t     B     , \
		T_Scl                     alpha , \
		T_Scl                     beta  , \
		T_Scl*                    C     , \
		const int_t               ldc   ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_sp2md( \
			opA, descrA, A, \
			opB, descrB, B, \
			alpha, beta, C, SPARSE_LAYOUT_COLUMN_MAJOR, ldc); \
	mkl_sparse_status_check(ierr); \
}
mkl_sparse_sp2md_macro(real_t, d)
mkl_sparse_sp2md_macro(real4_t, s)
mkl_sparse_sp2md_macro(complex_t, z)
mkl_sparse_sp2md_macro(complex8_t, c)
#undef mkl_sparse_sp2md_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_sp2md(T_Scalar alpha, 
		op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		T_Scalar beta, T_Scalar* c, uint_t ldc)
{
	CscMatrix<T_Scalar> A(mA, nA, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CscMatrix<T_Scalar> B(mB, nB, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));

	mkl_sparse_sp2md(
			opToSparseTrans(opA), A.descr(), A.mat(), 
			opToSparseTrans(opB), B.descr(), B.mat(), 
			alpha, beta, c, ldc);
}
/*-------------------------------------------------*/
#define instantiate_sp2md(T_Scl) \
template void csc_sp2md(T_Scl, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		T_Scl, T_Scl*, uint_t)
instantiate_sp2md(real_t);
instantiate_sp2md(real4_t);
instantiate_sp2md(complex_t);
instantiate_sp2md(complex8_t);
#undef instantiate_sp2md
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_sp2m(
    op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
    op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
    int_t** colptrC, int_t** rowidxC, T_Scalar** valuesC)
{
	CscMatrix<T_Scalar> A(mA, nA, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CscMatrix<T_Scalar> B(mB, nB, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));
	CscMatrix<T_Scalar> C;

	sparse_status_t ierr = mkl_sparse_sp2m(
			opToSparseTrans(opA), A.descr(), A.mat(),
			opToSparseTrans(opB), B.descr(), B.mat(),
			SPARSE_STAGE_FULL_MULT,
			&C.mat());
	mkl_sparse_status_check(ierr);

	int_t mC = 0;
	int_t nC = 0;
	C.export3(&mC, &nC, colptrC, rowidxC, valuesC);

	blk::csc::sort(nC, *colptrC, *rowidxC, *valuesC);
}
/*-------------------------------------------------*/
#define instantiate_sp2m(T_Scl) \
template void csc_sp2m( \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		op_t, uint_t, uint_t, const int_t*, const int_t*, const T_Scl*, \
		int_t**, int_t**, T_Scl**)
instantiate_sp2m(real_t);
instantiate_sp2m(real4_t);
instantiate_sp2m(complex_t);
instantiate_sp2m(complex8_t);
#undef instantiate_sp2m
/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/
