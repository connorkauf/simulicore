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
#include "cla3p/sparse/csc_xxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/csc.hpp"
#include "cla3p/bulk/csc_math.hpp"
#include "cla3p/support/imalloc.hpp"
#include "cla3p/support/utils.hpp"

#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/checks/csc_checks.hpp"
#include "cla3p/checks/block_ops_checks.hpp"
#include "cla3p/checks/transp_checks.hpp"
#include "cla3p/checks/perm_checks.hpp"
#include "cla3p/checks/hermitian_coeff_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace csc {
/*-------------------------------------------------*/
#define XxMatrixTmpl XxMatrix<T_Int,T_Scalar,T_Matrix>
#define XxMatrixTlst template <typename T_Int, typename T_Scalar, typename T_Matrix>
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix()
{
	defaults();
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
	: MatrixMeta(nr, nc, sanitizeProperty<T_Scalar>(pr))
{
	if(nr && nc) {

		setColptr(i_malloc<T_Int>(nc + 1));
		setRowidx(i_malloc<T_Int>(nz));
		setValues(i_malloc<T_Scalar>(nz));

		colptr()[nc] = nz;

		setOwner(true);

		checker();

	} else {

		clear();

	} // nr/nc
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::~XxMatrix()
{
	clear();
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(const XxMatrixTmpl& other)
	: XxMatrix(other.nrows(), other.ncols(), other.nnz(), other.prop())
{
	other.copyToExisting(*this);
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl& XxMatrixTmpl::operator=(const XxMatrixTmpl& other)
{
	if(!(*this)) {
		*this = init(other.nrows(), other.ncols(), other.nnz(), other.prop());
	}
	other.copyToExisting(*this);
	return *this;
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(XxMatrixTmpl&& other)
{
	other.moveTo(*this);
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl& XxMatrixTmpl::operator=(XxMatrixTmpl&& other)
{
	other.moveTo(*this);
	return (*this);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::defaults()
{
	setColptr(nullptr);
	setRowidx(nullptr);
	setValues(nullptr);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::clear()
{
	if(owner()) {
		i_free(colptr());
		i_free(rowidx());
		i_free(values());
	} // owner

	MatrixMeta::clear();
	Ownership::clear();

	defaults();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setColptr(T_Int* colptr)
{
	m_colptr = colptr;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setRowidx(T_Int* rowidx)
{
	m_rowidx = rowidx;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::setValues(T_Scalar* values)
{
	m_values = values;
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::operator-() const
{
	return VirtualMatrix<T_Matrix>(self()).scale(-1);
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::nnz() const
{
	if(!empty()) {
		return colptr()[ncols()];
	}
	return 0;
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Int* XxMatrixTmpl::colptr() const
{
	return m_colptr;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Int* XxMatrixTmpl::colptr()
{
	return m_colptr;
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Int* XxMatrixTmpl::rowidx() const
{
	return m_rowidx;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Int* XxMatrixTmpl::rowidx()
{
	return m_rowidx;
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Scalar* XxMatrixTmpl::values() const
{
	return m_values;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Scalar* XxMatrixTmpl::values()
{
	return m_values;
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
	ss << "  Colptr............... " << colptr() << "\n";
	ss << "  Rowidx............... " << rowidx() << "\n";
	ss << "  Values............... " << values() << "\n";
	ss << "  Property............. " << prop() << "\n";
	ss << "  Owner................ " << bool2yn(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::copyToExisting(XxMatrixTmpl& trg) const
{
	if(this != &trg) {

		similarity_check(prop(), nrows(), ncols(), trg.prop(), trg.nrows(), trg.ncols());
		similarity_dim_check(nnz(), trg.nnz());

		uint_t nc = ncols() + 1;
		uint_t nz = nnz();

		// 
		// TODO: perhaps use a copy for 1D arrays
		//
		bulk::dns::copy(uplo_t::Full, nc, 1, colptr(), nc, trg.colptr(), nc);
		bulk::dns::copy(uplo_t::Full, nz, 1, rowidx(), nz, trg.rowidx(), nz);
		bulk::dns::copy(uplo_t::Full, nz, 1, values(), nz, trg.values(), nz);

	} // do not apply on self
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::moveTo(XxMatrixTmpl& trg)
{
	trg.wrapper(nrows(), ncols(), colptr(), rowidx(), values(), owner(), prop());

	unbind();
	clear();
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::toString(uint_t nsd) const
{
	return bulk::csc::print_to_string(ncols(), colptr(), rowidx(), values(), nsd);
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::copy() const
{
	T_Matrix ret(nrows(), ncols(), nnz(), prop());
	copyToExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::rcopy()
{
	return T_Matrix::wrap(nrows(), ncols(), colptr(), rowidx(), values(), false, prop());
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::rcopy() const
{
	return T_Matrix::wrap(nrows(), ncols(), colptr(), rowidx(), values(), prop());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::move()
{
	T_Matrix ret;
	moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::iscale(T_Scalar val)
{
	hermitian_coeff_check(prop(), val);
	bulk::dns::scale(uplo_t::Full, nnz(), 1, values(), nnz(), val);
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::transpose() const
{
  return VirtualMatrix<T_Matrix>(self()).transpose();
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::ctranspose() const
{
  return VirtualMatrix<T_Matrix>(self()).ctranspose();
}
/*-------------------------------------------------*/
XxMatrixTlst
VirtualMatrix<T_Matrix> XxMatrixTmpl::conjugate() const
{
  return VirtualMatrix<T_Matrix>(self()).conjugate();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::iconjugate()
{
	//
	// TODO: perhaps use a conjugate for 1D arrays
	//
	bulk::dns::conjugate(uplo_t::Full, nnz(), 1, values(), nnz());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::general() const
{
	T_Matrix ret;

	T_Int    *colptr_ge = nullptr;
	T_Int    *rowidx_ge = nullptr;
	T_Scalar *values_ge = nullptr;

	if(prop().isGeneral()) {

		ret = copy();

	} else if(prop().isSymmetric()) {

		colptr_ge = i_malloc<T_Int>(ncols() + 1);
		bulk::csc::uplo2ge_colptr(prop().uplo(), ncols(), colptr(), rowidx(), colptr_ge);
		T_Int nz = colptr_ge[ncols()];
		rowidx_ge = i_malloc<T_Int>(nz);
		values_ge = i_malloc<T_Scalar>(nz);
		bulk::csc::sy2ge(prop().uplo(), ncols(), colptr(), rowidx(), values(), colptr_ge, rowidx_ge, values_ge);
		ret = T_Matrix::wrap(nrows(), ncols(), colptr_ge, rowidx_ge, values_ge, true);

	} else if(prop().isHermitian()) {

		colptr_ge = i_malloc<T_Int>(ncols() + 1);
		bulk::csc::uplo2ge_colptr(prop().uplo(), ncols(), colptr(), rowidx(), colptr_ge);
		T_Int nz = colptr_ge[ncols()];
		rowidx_ge = i_malloc<T_Int>(nz);
		values_ge = i_malloc<T_Scalar>(nz);
		bulk::csc::he2ge(prop().uplo(), ncols(), colptr(), rowidx(), values(), colptr_ge, rowidx_ge, values_ge);
		ret = T_Matrix::wrap(nrows(), ncols(), colptr_ge, rowidx_ge, values_ge, true);

	} else if(prop().isTriangular()) {

		ret = copy();
		ret.setProp(Property::General());

	} else {

		throw err::Exception();

	} // property 

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
typename XxMatrixTmpl::T_DnsMatrix XxMatrixTmpl::toDns() const
{
	T_DnsMatrix ret(nrows(), ncols(), prop());
	ret = 0;
	for(uint_t j = 0; j < ncols(); j++) {
		for(T_Int irow = colptr()[j]; irow < colptr()[j+1]; irow++) {
			ret(rowidx()[irow],j) = values()[irow];
		} // irow
	} // j

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeftRight(const prm::PiMatrix& P, const prm::PiMatrix& Q) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), Q.size());

	T_Matrix ret(nrows(), ncols(), nnz(), prop());
	bulk::csc::permute(prop().type(), prop().uplo(), nrows(), ncols(), 
			colptr(), rowidx(), values(), 
			ret.colptr(), ret.rowidx(), ret.values(), 
			P.values(), Q.values());

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteLeft(const prm::PiMatrix& P) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), ncols());

	T_Matrix ret(nrows(), ncols(), nnz(), prop());
	bulk::csc::permute(prop().type(), prop().uplo(), nrows(), ncols(), 
			colptr(), rowidx(), values(), 
			ret.colptr(), ret.rowidx(), ret.values(), 
			P.values(), nullptr);

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteRight(const prm::PiMatrix& Q) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), nrows(), Q.size());

	T_Matrix ret(nrows(), ncols(), nnz(), prop());
	bulk::csc::permute(prop().type(), prop().uplo(), nrows(), ncols(), 
			colptr(), rowidx(), values(), 
			ret.colptr(), ret.rowidx(), ret.values(), 
			nullptr, Q.values());

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::permuteMirror(const prm::PiMatrix& P) const
{
	perm_op_consistency_check(nrows(), ncols(), P.size(), P.size());

	T_Matrix ret(nrows(), ncols(), nnz(), prop());
	bulk::csc::permute(prop().type(), prop().uplo(), nrows(), ncols(), 
			colptr(), rowidx(), values(), 
			ret.colptr(), ret.rowidx(), ret.values(), 
			P.values(), nullptr);

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Property pr = block_op_consistency_check(prop(), nrows(), ncols(), ibgn, jbgn, ni, nj);

	if(!ni || !nj) return T_Matrix();

	T_Int *cptr = i_calloc<T_Int>(nj + 1);

	uint_t iend = ibgn + ni;
	uint_t jend = jbgn + nj;

	for(uint_t j = jbgn; j < jend; j++) {
		uint_t jlocal = j - jbgn;
		for(T_Int irow = colptr()[j]; irow < colptr()[j+1]; irow++) {
			T_Int i = rowidx()[irow];
			if(static_cast<T_Int>(ibgn) <= i && i < static_cast<T_Int>(iend)) {
				cptr[jlocal+1]++;
			} // i in range
		} // irow
	} // j

	bulk::csc::roll(nj, cptr);

	T_Int     nnz  = cptr[nj];
	T_Int    *ridx = nullptr;
	T_Scalar *vals = nullptr;

	if(nnz) {

		ridx = i_malloc<T_Int>(nnz);
		vals = i_malloc<T_Scalar>(nnz);

		for(uint_t j = jbgn; j < jend; j++) {
			uint_t jlocal = j - jbgn;
			for(T_Int irow = colptr()[j]; irow < colptr()[j+1]; irow++) {
				T_Int i = rowidx()[irow];
				T_Int ilocal = i - ibgn;
				T_Scalar v = values()[irow];
				if(static_cast<T_Int>(ibgn) <= i && i < static_cast<T_Int>(iend)) {
					ridx[cptr[jlocal]] = ilocal;
					vals[cptr[jlocal]] = v;
					cptr[jlocal]++;
				} // i in range
			} // irow
		} // j

		bulk::csc::unroll(nj, cptr);

	} // nnz

	T_Matrix ret = T_Matrix::wrap(ni, nj, cptr, ridx, vals, true, pr);

	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::wrapper(uint_t nr, uint_t nc, T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind, const Property& pr)
{
	clear();

	MatrixMeta::wrapper(nr, nc, sanitizeProperty<T_Scalar>(pr));
	setOwner(bind);

	setColptr(cptr);
	setRowidx(ridx);
	setValues(vals);

	checker();
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::checker() const
{
	csc_consistency_check(prop(), nrows(), ncols(), nnz(), colptr(), rowidx(), values());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::init(uint_t nr, uint_t nc, uint_t nz, const Property& pr)
{
	T_Matrix ret(nr, nc, nz, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Matrix XxMatrixTmpl::wrap(uint_t nr, uint_t nc, T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind, const Property& pr)
{
	T_Matrix ret;
	ret.wrapper(nr, nc, cptr, ridx, vals, bind, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_Matrix> XxMatrixTmpl::wrap(uint_t nr, uint_t nc, const T_Int *cptr, const T_Int *ridx, const T_Scalar *vals, const Property& pr)
{
	Guard<T_Matrix> ret(wrap(nr, nc, 
				const_cast<T_Int   *>(cptr),
				const_cast<T_Int   *>(ridx),
				const_cast<T_Scalar*>(vals), false, pr));
	return ret;
}
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
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/
