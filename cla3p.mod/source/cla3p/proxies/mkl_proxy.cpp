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
#include "cla3p/proxies/mkl_proxy.hpp"

// system
#include <algorithm>

// 3rd
#include <mkl.h>

// cla3p
#include "cla3p/bulk/csc.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/support/imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace mkl {
/*-------------------------------------------------*/
std::string version()
{
	const nint_t len = 256;
	char buffer[len];
	mkl_get_version_string(buffer, len);
	return buffer;
}
/*-------------------------------------------------*/
#define omatcopy_macro(typeout, typein, prefix) \
typeout omatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, \
		const typein *a, bulk_t lda, \
		      typein *b, bulk_t ldb) \
{ \
	mkl_##prefix##omatcopy(ordering, trans, rows, cols, alpha, a, lda, b, ldb); \
}
omatcopy_macro(void, real_t    , d)
omatcopy_macro(void, real4_t   , s)
omatcopy_macro(void, complex_t , z)
omatcopy_macro(void, complex8_t, c)
#undef omatcopy_macro
/*-------------------------------------------------*/
#define omatcopy_macro(typeout, typein, prefix) \
typeout omatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, \
		const typein *a, bulk_t lda, bulk_t stridea, \
		      typein *b, bulk_t ldb, bulk_t strideb) \
{ \
	mkl_##prefix##omatcopy2(ordering, trans, rows, cols, alpha, a, lda, stridea, b, ldb, strideb); \
}
omatcopy_macro(void, real_t    , d)
omatcopy_macro(void, real4_t   , s)
omatcopy_macro(void, complex_t , z)
omatcopy_macro(void, complex8_t, c)
#undef omatcopy_macro
/*-------------------------------------------------*/
#define imatcopy_macro(typeout, typein, prefix) \
typeout imatcopy(char ordering, char trans, bulk_t rows, bulk_t cols, typein alpha, typein *a, bulk_t lda, bulk_t ldb) \
{ \
	mkl_##prefix##imatcopy(ordering, trans, rows, cols, alpha, a, lda, ldb); \
}
imatcopy_macro(void, real_t    , d)
imatcopy_macro(void, real4_t   , s)
imatcopy_macro(void, complex_t , z)
imatcopy_macro(void, complex8_t, c)
#undef imatcopy_macro
/*-------------------------------------------------*/
#define omatadd_macro(typeout, typein, prefix) \
typeout omatadd(char ordering, char transa, char transb, bulk_t rows, bulk_t cols, \
    typein alpha, const typein *A, bulk_t lda, \
    typein beta , const typein *B, bulk_t ldb, typein *C, bulk_t ldc) \
{ \
	mkl_##prefix##omatadd(ordering, transa, transb, rows, cols, alpha, A, lda, beta , B, ldb, C, ldc); \
}
omatadd_macro(void, real_t    , d)
omatadd_macro(void, real4_t   , s)
omatadd_macro(void, complex_t , z)
omatadd_macro(void, complex8_t, c)
#undef omatadd_macro
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
static void spcheck(sparse_status_t ierr)
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
#define sparse_create_csc_macro(typein, prefix) \
static void sparse_create_csc(sparse_matrix_t* mat, uint_t m, uint_t n, int_t *colptr, int_t *rowidx, typein *values) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_create_csc(mat, SPARSE_INDEX_BASE_ZERO, m, n, colptr, colptr + 1, rowidx, values); \
	spcheck(ierr); \
}
sparse_create_csc_macro(real_t, d)
sparse_create_csc_macro(real4_t, s)
sparse_create_csc_macro(complex_t, z)
sparse_create_csc_macro(complex8_t, c)
#undef sparse_create_csc_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
static void copy_csc4_to_csc3(uint_t n, sparse_index_base_t indexing,
		const int_t    *colbgn4, 
		const int_t    *colend4, 
		const int_t    *rowidx4, 
		const T_Scalar *values4,
		int_t    **colptr, 
		int_t    **rowidx, 
		T_Scalar **values)
{
	int_t *colptr3 = i_malloc<int_t>(n+1);

	colptr3[0] = 0;
	for(uint_t j = 0; j < n; j++) {
		colptr3[j+1] = colptr3[j] + (colend4[j] - colbgn4[j]);
	} // j

	int_t nnz = colptr3[n];

	int_t    *rowidx3 = i_malloc<int_t>(nnz);
	T_Scalar *values3 = i_malloc<T_Scalar>(nnz);

	for(uint_t j = 0; j < n; j++) {
		int_t ibgn4 = colbgn4[j] - colbgn4[0];
		int_t iend4 = colend4[j] - colbgn4[0];
		int_t ibgn3 = colptr3[j];
		std::copy(rowidx4 + ibgn4, rowidx4 + iend4, rowidx3 + ibgn3);
		std::copy(values4 + ibgn4, values4 + iend4, values3 + ibgn3);
	} // j
	
	if(indexing == SPARSE_INDEX_BASE_ONE) {
		std::for_each(rowidx3, rowidx3 + nnz, [](int_t& i) { i--; });
	} // indexing

	*colptr = colptr3;
	*rowidx = rowidx3;
	*values = values3;
}
/*-------------------------------------------------*/
#define sparse_export_csc_macro(typein, prefix) \
static void sparse_export_csc(const sparse_matrix_t mat, int_t *m, int_t *n, int_t **colptr, int_t **rowidx, typein **values) \
{ \
	sparse_index_base_t indexing; \
	int_t *colbgn4 = nullptr; \
	int_t *colend4 = nullptr; \
	int_t *rowidx4 = nullptr;\
	typein  *values4 = nullptr;\
	sparse_status_t ierr = mkl_sparse_##prefix##_export_csc(mat, &indexing, m, n, &colbgn4, &colend4, &rowidx4, &values4); \
	spcheck(ierr); \
	copy_csc4_to_csc3(*n, indexing, colbgn4, colend4, rowidx4, values4, colptr, rowidx, values); \
}
sparse_export_csc_macro(real_t, d)
sparse_export_csc_macro(real4_t, s)
sparse_export_csc_macro(complex_t, z)
sparse_export_csc_macro(complex8_t, c)
#undef sparse_export_csc_macro
/*-------------------------------------------------*/
static sparse_operation_t op2sparseop(op_t op)
{
	if(op == op_t::N) return SPARSE_OPERATION_NON_TRANSPOSE;
	if(op == op_t::T) return SPARSE_OPERATION_TRANSPOSE;
	if(op == op_t::C) return SPARSE_OPERATION_CONJUGATE_TRANSPOSE;

	throw err::NoConsistency("Could not convert op_t to sparse operation");

	return SPARSE_OPERATION_NON_TRANSPOSE;
}
/*-------------------------------------------------*/
static sparse_matrix_type_t prop2desrctype(prop_t prop)
{
	if(prop == prop_t::General   ) return SPARSE_MATRIX_TYPE_GENERAL   ;
	if(prop == prop_t::Symmetric ) return SPARSE_MATRIX_TYPE_SYMMETRIC ;
	if(prop == prop_t::Hermitian ) return SPARSE_MATRIX_TYPE_HERMITIAN ;
	if(prop == prop_t::Triangular) return SPARSE_MATRIX_TYPE_TRIANGULAR;

	throw err::NoConsistency("Could not convert prop_t to matrix descriptor");

	return SPARSE_MATRIX_TYPE_GENERAL;
}
/*-------------------------------------------------*/
static sparse_fill_mode_t uplo2desrcmode(uplo_t uplo)
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
	ret.type = prop2desrctype(pr.type());
	ret.mode = uplo2desrcmode(pr.uplo());
	ret.diag = SPARSE_DIAG_NON_UNIT;

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
class CscMatrix {

	public:
		CscMatrix();
		CscMatrix(uint_t m, uint_t n, int_t *colptr, int_t *rowidx, T_Scalar *values, const Property& pr = defaultProperty());
		~CscMatrix();

		sparse_matrix_t& mat();
		const sparse_matrix_t& mat() const;

		struct matrix_descr& descr();
		const struct matrix_descr& descr() const;

		void exportCsc3(int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scalar **values) const;

	private:
		sparse_matrix_t     m_mat;
		struct matrix_descr m_descr;
};
/*-------------------------------------------------*/
template <typename T_Scalar>
CscMatrix<T_Scalar>::CscMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar>
CscMatrix<T_Scalar>::CscMatrix(uint_t m, uint_t n, int_t *colptr, int_t *rowidx, T_Scalar *values, const Property& pr)
{
	sparse_create_csc(&mat(), m, n, colptr, rowidx, values);
	descr() = create_descriptor(pr);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
CscMatrix<T_Scalar>::~CscMatrix() 
{
	spcheck(mkl_sparse_destroy(mat()));
}
/*-------------------------------------------------*/
template <typename T_Scalar>
sparse_matrix_t& CscMatrix<T_Scalar>::mat()
{ 
	return m_mat; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const sparse_matrix_t& CscMatrix<T_Scalar>::mat() const 
{
	return m_mat; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
struct matrix_descr& CscMatrix<T_Scalar>::descr()
{ 
	return m_descr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const struct matrix_descr& CscMatrix<T_Scalar>::descr() const 
{
	return m_descr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void CscMatrix<T_Scalar>::exportCsc3(int_t *m, int_t *n, int_t **colptr, int_t **rowidx, T_Scalar **values) const
{
	sparse_export_csc(mat(), m, n, colptr, rowidx, values);
}
/*-------------------------------------------------*/
#define sparse_add_macro(typein, prefix) \
static void sparse_add( \
		const sparse_operation_t op   , \
		const sparse_matrix_t    A    , \
		const typein             alpha, \
		const sparse_matrix_t    B    , \
		sparse_matrix_t*         C    ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_add(op, A, alpha, B, C); \
	spcheck(ierr); \
}
sparse_add_macro(real_t, d)
sparse_add_macro(real4_t, s)
sparse_add_macro(complex_t, z)
sparse_add_macro(complex8_t, c)
#undef sparse_add_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_add(uint_t m, uint_t n, T_Scalar alpha,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CscMatrix<T_Scalar> B(m, n, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));
	CscMatrix<T_Scalar> C;

	sparse_operation_t opA = SPARSE_OPERATION_NON_TRANSPOSE;

	sparse_add(opA, A.mat(), alpha, B.mat(), &C.mat());

	int_t mC = 0;
	int_t nC = 0;
	C.exportCsc3(&mC, &nC, colptrC, rowidxC, valuesC);
}
/*-------------------------------------------------*/
template void csc_add(uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const int_t*, const int_t*, const real_t    *, int_t**, int_t**, real_t    **);
template void csc_add(uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const int_t*, const int_t*, const real4_t   *, int_t**, int_t**, real4_t   **);
template void csc_add(uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const int_t*, const int_t*, const complex_t *, int_t**, int_t**, complex_t **);
template void csc_add(uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const int_t*, const int_t*, const complex8_t*, int_t**, int_t**, complex8_t**);
/*-------------------------------------------------*/
#define sparse_mv_macro(typein, prefix) \
static void sparse_mv( \
				const sparse_operation_t  op   , \
				const typein              alpha, \
				const sparse_matrix_t     A    , \
				const struct matrix_descr descr, \
				const typein*             x    , \
				const typein              beta , \
				typein*                   y    ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_mv(op, alpha, A, descr, x, beta, y); \
	spcheck(ierr); \
}
sparse_mv_macro(real_t, d)
sparse_mv_macro(real4_t, s)
sparse_mv_macro(complex_t, z)
sparse_mv_macro(complex8_t, c)
#undef sparse_mv_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mv(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		const T_Scalar* x, T_Scalar beta, T_Scalar *y)
{
	Property prA(propA, uploA);
	CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
	sparse_operation_t op = op2sparseop(opA);

	sparse_mv(op, alpha, A.mat(), A.descr(), x, beta, y);
}
/*-------------------------------------------------*/
template void csc_mv(prop_t, uplo_t, uint_t, uint_t, real_t    , op_t, const int_t*, const int_t*, const real_t    *, const real_t    *, real_t    , real_t    *);
template void csc_mv(prop_t, uplo_t, uint_t, uint_t, real4_t   , op_t, const int_t*, const int_t*, const real4_t   *, const real4_t   *, real4_t   , real4_t   *);
template void csc_mv(prop_t, uplo_t, uint_t, uint_t, complex_t , op_t, const int_t*, const int_t*, const complex_t *, const complex_t *, complex_t , complex_t *);
template void csc_mv(prop_t, uplo_t, uint_t, uint_t, complex8_t, op_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, complex8_t, complex8_t*);
/*-------------------------------------------------*/
#define sparse_mm_macro(typein, prefix) \
static void sparse_mm( \
		const sparse_operation_t  op    , \
		const typein              alpha , \
		const sparse_matrix_t     A     , \
		const struct matrix_descr descr , \
		const typein*             b     , \
		const int_t               cols  , \
		const int_t               ldb   , \
		const typein              beta  , \
		typein*                   c     , \
		const int_t               ldc   ) \
{ \
	sparse_status_t ierr = mkl_sparse_##prefix##_mm(op, alpha, A, descr, SPARSE_LAYOUT_COLUMN_MAJOR, b, cols, ldb, beta, c, ldc); \
	spcheck(ierr); \
}
sparse_mm_macro(real_t, d)
sparse_mm_macro(real4_t, s)
sparse_mm_macro(complex_t, z)
sparse_mm_macro(complex8_t, c)
#undef sparse_mm_macro
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_mm(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		uint_t k, const T_Scalar* b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	Property prA(propA, uploA);
	CscMatrix<T_Scalar> A(m, n, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA), prA);
	sparse_operation_t op = op2sparseop(opA);

	sparse_mm(op, alpha, A.mat(), A.descr(), b, k, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
template void csc_mm(prop_t, uplo_t, uint_t, uint_t, real_t    , op_t, const int_t*, const int_t*, const real_t    *, uint_t, const real_t    *, uint_t, real_t    , real_t    *, uint_t);
template void csc_mm(prop_t, uplo_t, uint_t, uint_t, real4_t   , op_t, const int_t*, const int_t*, const real4_t   *, uint_t, const real4_t   *, uint_t, real4_t   , real4_t   *, uint_t);
template void csc_mm(prop_t, uplo_t, uint_t, uint_t, complex_t , op_t, const int_t*, const int_t*, const complex_t *, uint_t, const complex_t *, uint_t, complex_t , complex_t *, uint_t);
template void csc_mm(prop_t, uplo_t, uint_t, uint_t, complex8_t, op_t, const int_t*, const int_t*, const complex8_t*, uint_t, const complex8_t*, uint_t, complex8_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void csc_spmm(op_t opA,
		uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
		uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		uint_t* mC, uint_t* nC, int_t** colptrC, int_t** rowidxC, T_Scalar** valuesC)
{
	CscMatrix<T_Scalar> A(mA, nA, const_cast<int_t*>(colptrA), const_cast<int_t*>(rowidxA), const_cast<T_Scalar*>(valuesA));
	CscMatrix<T_Scalar> B(mB, nB, const_cast<int_t*>(colptrB), const_cast<int_t*>(rowidxB), const_cast<T_Scalar*>(valuesB));
	CscMatrix<T_Scalar> C;

	sparse_operation_t op = op2sparseop(opA);

	sparse_status_t ierr = mkl_sparse_spmm(op, A.mat(), B.mat(), &C.mat());
	spcheck(ierr);

	C.exportCsc3(mC, nC, colptrC, rowidxC, valuesC);

	bulk::csc::sort(*nC, *colptrC, *rowidxC, *valuesC);
}
/*-------------------------------------------------*/
} // namespace mkl
} // namespace cla3p
/*-------------------------------------------------*/
