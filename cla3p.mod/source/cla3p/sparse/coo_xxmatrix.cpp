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
#include "cla3p/sparse/coo_xxmatrix.hpp"

// system
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/error.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/bulk/csc.hpp"
#include "cla3p/support/imalloc.hpp"
#include "cla3p/support/utils.hpp"

#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/checks/coo_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace coo {
/*-------------------------------------------------*/
#define XxMatrixTmpl XxMatrix<T_Int,T_Scalar,T_Matrix>
#define XxMatrixTlst template <typename T_Int, typename T_Scalar, typename T_Matrix>
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix()
{
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: MatrixMeta(nr, nc, sanitizeProperty<T_Scalar>(pr))
{
	coo_consistency_check(prop(), nrows(), ncols());
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::~XxMatrix()
{
	clear();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::clear()
{
	MatrixMeta::clear();
	tupleVec().clear();
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::nnz() const
{
	return static_cast<uint_t>(tupleVec().size());
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::TupleVec& XxMatrixTmpl::tupleVec()
{
	return m_tuples;
}
/*-------------------------------------------------*/
XxMatrixTlst
const typename XxMatrixTmpl::TupleVec& XxMatrixTmpl::tupleVec() const
{
	return m_tuples;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::reserve(uint_t nz)
{
	tupleVec().reserve(nz);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::insert(const Tuple<T_Int,T_Scalar>& tuple)
{
	coo_check_triplet(nrows(), ncols(), prop(), tuple.row(), tuple.col(), tuple.val());

	tupleVec().push_back(tuple);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::insert(T_Int i, T_Int j, T_Scalar v)
{
	Tuple<T_Int,T_Scalar> tuple(i, j, v);
	insert(tuple);
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::info(const std::string& msg) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::ostringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << TypeTraits<T_Matrix>::type_name() << "\n";
	ss << "  Datatype............. " << TypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << TypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Number of rows....... " << nrows() << "\n";
	ss << "  Number of columns.... " << ncols() << "\n";
	ss << "  Number of non zeros.. " << nnz() << "\n";
	ss << "  Property............. " << prop() << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::toString(uint_t nsd) const
{
	if(empty() || !nnz()) return "";

	ListPrinter listPrinter(nsd, nrows(), ncols(), nnz());

	std::string ret = listPrinter.header();
	std::string entry;

	for(uint_t cnt = 0; cnt < nnz(); cnt++) {

			T_Int    i = tupleVec()[cnt].row();
			T_Int    j = tupleVec()[cnt].col();
			T_Scalar v = tupleVec()[cnt].val();

			entry = listPrinter.tuple(cnt, i, j, v);
			ret.append(entry);

	} // cnt

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::operator typename XxMatrixTmpl::T_CscMatrix() const
{ 
	return toCsc(); 
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_CscMatrix XxMatrixTmpl::toCsc(dup_t duplicatePolicy) const
{
	T_Int *colptr = i_calloc<T_Int>(ncols() + 1);

	std::for_each(tupleVec().begin(), tupleVec().end(), 
			[&](const Tuple<T_Int,T_Scalar> &tuple) 
			{ 
			colptr[tuple.col() + 1]++;
			});

	bulk::csc::roll(ncols(), colptr);

	T_Int nnz = colptr[ncols()];

	T_Int    *rowidx = nullptr;
	T_Scalar *values = nullptr;

	if(nnz) {

		rowidx = i_malloc<T_Int>(nnz);
		values = i_malloc<T_Scalar>(nnz);

		std::for_each(tupleVec().begin(), tupleVec().end(), 
				[&](const Tuple<T_Int,T_Scalar> &tuple) 
				{ 
				rowidx[colptr[tuple.col()]] = tuple.row();
				values[colptr[tuple.col()]] = tuple.val();
				colptr[tuple.col()]++;
				});

		bulk::csc::unroll(ncols(), colptr);
		bulk::csc::sort(ncols(), colptr, rowidx, values);
		bulk::csc::remove_duplicates(ncols(), colptr, rowidx, values, duplicatePolicy);

		rowidx = static_cast<T_Int   *>(i_realloc(rowidx, colptr[ncols()] * sizeof(T_Int   )));
		values = static_cast<T_Scalar*>(i_realloc(values, colptr[ncols()] * sizeof(T_Scalar)));

	} // nnz

	T_CscMatrix ret = T_CscMatrix::wrap(nrows(), ncols(), colptr, rowidx, values, true, prop());

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::init(uint_t nr, uint_t nc, const Property& pr)
{
	T_Matrix ret(nr, nc, pr);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxMatrixTmpl
#undef XxMatrixTlst
/*-------------------------------------------------*/
template class XxMatrix<int_t,real_t,RdMatrix>;
template class XxMatrix<int_t,real4_t,RfMatrix>;
template class XxMatrix<int_t,complex_t,CdMatrix>;
template class XxMatrix<int_t,complex8_t,CfMatrix>;
/*-------------------------------------------------*/
} // namespace coo
} // namespace cla3p
/*-------------------------------------------------*/
