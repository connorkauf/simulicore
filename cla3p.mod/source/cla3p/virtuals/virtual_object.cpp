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
#include "cla3p/virtuals/virtual_object.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"

#include "cla3p/error/exceptions.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/csc.hpp"
#include "cla3p/checks/transp_checks.hpp"

#include "cla3p/algebra/functional_inner.hpp"
#include "cla3p/algebra/functional_outer.hpp"
#include "cla3p/algebra/functional_update.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Object>
VirtualParams<T_Object>::VirtualParams(const T_Object& obj)
	: m_obj(obj)
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Object>
VirtualParams<T_Object>::VirtualParams(const VirtualParams<T_Object>& v) :
	m_transop(v.transOp()),
	m_conjop(v.conjOp()),
	m_coeff(v.coeff()),
	m_obj(v.obj())
{
}

/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::defaults()
{
	setTransOp(op_t::N);
	setConjOp(false);
	setCoeff(1);
}
/*-------------------------------------------------*/
template <typename T_Object> 
void VirtualParams<T_Object>::setTransOp(op_t transop)
{
	m_transop = transop;
}
/*-------------------------------------------------*/
template <typename T_Object> 
void VirtualParams<T_Object>::setConjOp(bool conjop)
{
	m_conjop = conjop;
}
/*-------------------------------------------------*/
template <typename T_Object> 
void VirtualParams<T_Object>::setCoeff(T_Scalar c)
{
	m_coeff = c;
}
/*-------------------------------------------------*/
template <typename T_Object> 
op_t VirtualParams<T_Object>::transOp() const 
{ 
	return m_transop; 
}
/*-------------------------------------------------*/
template <typename T_Object> 
bool VirtualParams<T_Object>::conjOp() const 
{ 
	return m_conjop; 
}
/*-------------------------------------------------*/
template <typename T_Object> 
typename T_Object::value_type VirtualParams<T_Object>::coeff() const 
{ 
	return m_coeff; 
}
/*-------------------------------------------------*/
template <typename T_Object> 
const T_Object& VirtualParams<T_Object>::obj() const 
{ 
	return m_obj;
}
/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::simplify()
{
	if(transOp() == op_t::T && conjOp()) { 
		setTransOp(op_t::C); 
		setConjOp(false); 
		return; 
	}

	if(transOp() == op_t::C && conjOp()) { 
		setTransOp(op_t::T); 
		setConjOp(false); 
		return; 
	}
}
/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::iscale(T_Scalar val)
{
	setCoeff(coeff() * val);
}
/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::iconjugate()
{
	if(TypeTraits<T_Object>::is_complex()) {
		setConjOp(!conjOp());
		setCoeff(arith::conj(coeff()));
		simplify();
	} // only for complex objects
}
/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::itranspose()
{
	if(transOp() == op_t::N) {
		setTransOp(op_t::T);
	} else if(transOp() == op_t::T) {
		setTransOp(op_t::N);
	} else if(transOp() == op_t::C) { 
		setTransOp(op_t::N); 
		setConjOp(!conjOp()); 
	}
	simplify();
}
/*-------------------------------------------------*/
template <typename T_Object>
void VirtualParams<T_Object>::ictranspose()
{
	iconjugate();
	itranspose();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualRowVec<T_Vector>::VirtualRowVec(const T_Vector& vec, bool conjop)
	: VirtualRowVec<T_Vector>::VirtualParams(vec) 
{
	if(conjop) this->ictranspose();
	else       this->itranspose();
}
/*-------------------------------------------------*/
template <typename T_Vector>
typename T_Vector::value_type
VirtualRowVec<T_Vector>::evaluateInner(const VirtualVector<T_Vector>& vY) const
{
	T_Scalar ret = 0;

	if(vY.needsEvaluation()) {

		T_Vector Y = vY.evaluate();
		VirtualVector<T_Vector> tmp(Y);
		ret = evaluateInner(tmp);

	} else {

		if(this->conjOp()) throw err::Exception(); // should have been simplified
		if(this->transOp() == op_t::T) ret = ops::dot (this->obj(), vY.obj());
		if(this->transOp() == op_t::C) ret = ops::dotc(this->obj(), vY.obj());

		ret *= (this->coeff() * vY.coeff());

	} // needs eval

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type
VirtualRowVec<T_Vector>::evaluateOuter(const VirtualVector<T_Vector>& vX) const
{
	T_Matrix ret;

	if(vX.needsEvaluation()) {

		T_Vector X = vX.evaluate();
		VirtualVector<T_Vector> tmp(X);
		ret = evaluateOuter(tmp);

	} else {

		if(this->conjOp()) throw err::Exception(); // should have been simplified

		ret = T_Matrix::init(vX.size1(), this->obj().size());
		ret = 0;

		T_Scalar coeff = vX.coeff() * this->coeff();

		if(this->transOp() == op_t::T) ops::outer (coeff, vX.obj(), this->obj(), ret);
		if(this->transOp() == op_t::C) ops::outerc(coeff, vX.obj(), this->obj(), ret);

	} // needs eval

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
VirtualObject<T_Object,T_Virtual>::VirtualObject(const T_Object& obj)
	: VirtualParams<T_Object>(obj)
{
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
bool VirtualObject<T_Object,T_Virtual>::needsEvaluation() const 
{ 
	return this->conjOp(); 
}
/*-------------------------------------------------*/
#if 0
template <typename T_Vector>
static uint_t determineSize1(op_t op, const dns::XxVector<typename T_Vector::value_type,T_Vector>& vec)
{
	return (op == op_t::N ? vec.size() : 1);
}
/*-------------------------------------------------*/
template <typename T_Vector>
static uint_t determineSize2(op_t op, const dns::XxVector<typename T_Vector::value_type,T_Vector>& vec)
{
	return (op == op_t::N ? 1 : vec.size());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static uint_t determineSize1(op_t op, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& mat)
{
	return (op == op_t::N ? mat.nrows() : mat.ncols());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static uint_t determineSize2(op_t op, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& mat)
{
	return (op == op_t::N ? mat.ncols() : mat.nrows());
}
#endif
/*-------------------------------------------------*/
static uint_t determineSize1(op_t op, const Meta1D& m)
{
	return (op == op_t::N ? m.size() : 1);
}
/*-------------------------------------------------*/
static uint_t determineSize2(op_t op, const Meta1D& m)
{
	return (op == op_t::N ? 1 : m.size());
}
/*-------------------------------------------------*/
static uint_t determineSize1(op_t op, const Meta2D& m)
{
	return (op == op_t::N ? m.nrows() : m.ncols());
}
/*-------------------------------------------------*/
static uint_t determineSize2(op_t op, const Meta2D& m)
{
	return (op == op_t::N ? m.ncols() : m.nrows());
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
uint_t VirtualObject<T_Object,T_Virtual>::size1() const 
{
	return determineSize1(this->transOp(), this->obj());
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
uint_t VirtualObject<T_Object,T_Virtual>::size2() const 
{
	return determineSize2(this->transOp(), this->obj());
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualObject<T_Object,T_Virtual>::scale(T_Scalar val) const
{
	T_Virtual ret = this->self(); 
	ret.iscale(val);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualObject<T_Object,T_Virtual>::conjugate() const 
{ 
	T_Virtual ret = this->self(); 
	ret.iconjugate(); 
	return ret; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualVector<T_Vector>::VirtualVector(const T_Vector& vec)
	: VirtualObject<T_Vector,VirtualVector<T_Vector>>(vec)
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
const VirtualVector<T_Vector>& VirtualVector<T_Vector>::self() const
{
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Vector>
void VirtualVector<T_Vector>::addToTarget(T_Scalar beta, T_Vector& trg) const
{
	if(this->transOp() != op_t::N) {
		throw err::NoConsistency("Virtually transposed vectors cannot be evaluated");
	} // op

	if(beta == T_Scalar(0)) {

		if(!trg) {
			trg = T_Vector::init(this->size1());
		} // alloc if needed

		trg = this->obj();

		if(this->conjOp()) {
			trg.iconjugate();
		} // conjop

		trg.iscale(this->coeff()); // coeff has aready been conjugated

	} else {

		trg.iscale(beta);

		if(this->needsEvaluation()) {
			ops::update(T_Scalar(1), this->evaluate(), trg);
		} else {
			ops::update(this->coeff(), this->obj(), trg);
		} // conjop

	} // beta
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualRowVec<T_Vector> VirtualVector<T_Vector>::transpose() const 
{ 
	return VirtualRowVec<T_Vector>(this->self(), false);
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualRowVec<T_Vector> VirtualVector<T_Vector>::ctranspose() const 
{ 
	return VirtualRowVec<T_Vector>(this->self(), true);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix>::VirtualMatrix(const T_Matrix& mat)
	: VirtualObject<T_Matrix,VirtualMatrix<T_Matrix>>(mat)
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const VirtualMatrix<T_Matrix>& VirtualMatrix<T_Matrix>::self() const
{
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static void addToTargetSpecialization(
		const VirtualMatrix<T_Matrix>& v, 
		typename T_Matrix::value_type beta, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& trg)
{
	using T_Scalar = typename T_Matrix::value_type;

	if(beta == T_Scalar(0)) {

		if(!trg) {
			trg.self() = T_Matrix::init(v.size1(), v.size2());
		} // alloc if needed

		if(v.transOp() == op_t::N) {

			bulk::dns::copy(
					v.obj().prop().uplo(), 
					v.obj().nrows(), 
					v.obj().ncols(), 
					v.obj().values(), 
					v.obj().ld(), 
					trg.values(), trg.ld());

		} else if (v.transOp() == op_t::T) {

			transp_op_consistency_check(v.obj().prop().type(), false);

			bulk::dns::transpose(
					v.obj().nrows(), 
					v.obj().ncols(), 
					v.obj().values(), 
					v.obj().ld(), 
					trg.values(), trg.ld());

		} else if(v.transOp() == op_t::C) {

			transp_op_consistency_check(v.obj().prop().type(), true);

			bulk::dns::conjugate_transpose(
					v.obj().nrows(), 
					v.obj().ncols(), 
					v.obj().values(), 
					v.obj().ld(), 
					trg.values(), trg.ld());

		} // op

		if(v.conjOp()) {
			trg.iconjugate();
		} // conjop

		trg.iscale(v.coeff()); // coeff has aready been conjugated

	} else {

		trg.iscale(beta);

		// TODO: add transpose without evaluation

		if(v.needsEvaluation() || v.transOp() != op_t::N) {
			ops::update(T_Scalar(1), v.evaluate(), trg);
		} else {
			ops::update(v.coeff(), v.obj(), trg);
		}

	} // beta
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static void addToTargetSpecialization(
		const VirtualMatrix<T_Matrix>& v, 
		typename T_Matrix::value_type beta, 
		csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& trg)
{
	using T_Scalar = typename T_Matrix::value_type;

	if(beta == T_Scalar(0)) {

		trg.clear();

		if(v.transOp() == op_t::N) {

			trg = v.obj();

		} else if (v.transOp() == op_t::T) {

			transp_op_consistency_check(v.obj().prop().type(), false);

			trg.self() = T_Matrix::init(v.size1(), v.size2(), v.obj().nnz(), v.obj().prop());

			bulk::csc::transpose(
					v.obj().nrows(), 
					v.obj().ncols(), 
					v.obj().colptr(), 
					v.obj().rowidx(), 
					v.obj().values(), 
					trg.colptr(), 
					trg.rowidx(), 
					trg.values());

		} else if(v.transOp() == op_t::C) {

			transp_op_consistency_check(v.obj().prop().type(), true);

			trg.self() = T_Matrix::init(v.size1(), v.size2(), v.obj().nnz(), v.obj().prop());

			bulk::csc::conjugate_transpose(
					v.obj().nrows(), 
					v.obj().ncols(), 
					v.obj().colptr(), 
					v.obj().rowidx(), 
					v.obj().values(), 
					trg.colptr(), 
					trg.rowidx(), 
					trg.values());

		} // op

		if(v.conjOp()) {
			trg.iconjugate();
		} // conjop

		trg.iscale(v.coeff()); // coeff has aready been conjugated

	} else {

		trg.iscale(beta);

		// TODO: add transpose without evaluation

		if(v.needsEvaluation() || v.transOp() != op_t::N) {
			T_Matrix tmp;
			addToTargetSpecialization(v, T_Scalar(0), tmp);
			ops::update(T_Scalar(1), tmp, trg);
		} else {
			ops::update(v.coeff(), v.obj(), trg);
		}

	} // beta
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void VirtualMatrix<T_Matrix>::addToTarget(T_Scalar beta, T_Matrix& trg) const
{
	addToTargetSpecialization(*this, beta, trg);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix> VirtualMatrix<T_Matrix>::transpose() const 
{ 
	VirtualMatrix<T_Matrix> ret = *this; 
	ret.itranspose(); 
	return ret; 
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix> VirtualMatrix<T_Matrix>::ctranspose() const 
{ 
	VirtualMatrix<T_Matrix> ret = *this; 
	ret.ictranspose(); 
	return ret; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualParams<dns::RdVector>;
template class VirtualParams<dns::RfVector>;
template class VirtualParams<dns::CdVector>;
template class VirtualParams<dns::CfVector>;
/*-------------------------------------------------*/
template class VirtualParams<dns::RdMatrix>;
template class VirtualParams<dns::RfMatrix>;
template class VirtualParams<dns::CdMatrix>;
template class VirtualParams<dns::CfMatrix>;
/*-------------------------------------------------*/
template class VirtualParams<csc::RdMatrix>;
template class VirtualParams<csc::RfMatrix>;
template class VirtualParams<csc::CdMatrix>;
template class VirtualParams<csc::CfMatrix>;
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualRowVec<dns::RdVector>;
template class VirtualRowVec<dns::RfVector>;
template class VirtualRowVec<dns::CdVector>;
template class VirtualRowVec<dns::CfVector>;
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualObject<dns::RdVector, VirtualVector<dns::RdVector>>;
template class VirtualObject<dns::RfVector, VirtualVector<dns::RfVector>>;
template class VirtualObject<dns::CdVector, VirtualVector<dns::CdVector>>;
template class VirtualObject<dns::CfVector, VirtualVector<dns::CfVector>>;
/*-------------------------------------------------*/
template class VirtualObject<dns::RdMatrix, VirtualMatrix<dns::RdMatrix>>;
template class VirtualObject<dns::RfMatrix, VirtualMatrix<dns::RfMatrix>>;
template class VirtualObject<dns::CdMatrix, VirtualMatrix<dns::CdMatrix>>;
template class VirtualObject<dns::CfMatrix, VirtualMatrix<dns::CfMatrix>>;
/*-------------------------------------------------*/
template class VirtualObject<csc::RdMatrix, VirtualMatrix<csc::RdMatrix>>;
template class VirtualObject<csc::RfMatrix, VirtualMatrix<csc::RfMatrix>>;
template class VirtualObject<csc::CdMatrix, VirtualMatrix<csc::CdMatrix>>;
template class VirtualObject<csc::CfMatrix, VirtualMatrix<csc::CfMatrix>>;
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualVector<dns::RdVector>;
template class VirtualVector<dns::RfVector>;
template class VirtualVector<dns::CdVector>;
template class VirtualVector<dns::CfVector>;
/*-------------------------------------------------*/
template class VirtualMatrix<dns::RdMatrix>;
template class VirtualMatrix<dns::RfMatrix>;
template class VirtualMatrix<dns::CdMatrix>;
template class VirtualMatrix<dns::CfMatrix>;
/*-------------------------------------------------*/
template class VirtualMatrix<csc::RdMatrix>;
template class VirtualMatrix<csc::RfMatrix>;
template class VirtualMatrix<csc::CdMatrix>;
template class VirtualMatrix<csc::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
