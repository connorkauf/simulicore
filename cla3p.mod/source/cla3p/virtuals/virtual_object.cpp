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
#include "cla3p/error/exceptions.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/checks/transp_checks.hpp"
#include "cla3p/algebra/functional_inner.hpp"
#include "cla3p/algebra/functional_outer.hpp"
#include "cla3p/algebra/functional_update.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
VirtualObject<T_Object,T_Virtual>::VirtualObject()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
VirtualObject<T_Object,T_Virtual>::VirtualObject(const T_Object& obj)
{
	defaults();

	Guard<T_Object> guard(obj);
	setGuard(guard);
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
VirtualObject<T_Object,T_Virtual>::~VirtualObject()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::defaults()
{
	setTransOp(op_t::N);
	setConjOp(false);
	setCoeff(1);
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
void VirtualObject<T_Object,T_Virtual>::setTransOp(op_t transop)
{
	m_transop = transop;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
void VirtualObject<T_Object,T_Virtual>::setConjOp(bool conjop)
{
	m_conjop = conjop;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
void VirtualObject<T_Object,T_Virtual>::setCoeff(T_Scalar c)
{
	m_coeff = c;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
void VirtualObject<T_Object,T_Virtual>::setGuard(const Guard<T_Object>& guard)
{
	m_guard = guard;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
op_t VirtualObject<T_Object,T_Virtual>::transOp() const 
{ 
	return m_transop; 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
bool VirtualObject<T_Object,T_Virtual>::conjOp() const 
{ 
	return m_conjop; 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
typename T_Object::value_type VirtualObject<T_Object,T_Virtual>::coeff() const 
{ 
	return m_coeff; 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
const Guard<T_Object>& VirtualObject<T_Object,T_Virtual>::guard() const 
{ 
	return m_guard; 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual> 
const T_Object& VirtualObject<T_Object,T_Virtual>::obj() const 
{ 
	return m_guard.get(); 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::clear()
{
	m_guard.clear();
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::simplify()
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
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::iscale(T_Scalar val)
{
	setCoeff(coeff() * val);
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::iconjugate()
{
	if(TypeTraits<T_Object>::is_complex()) {
		setConjOp(!conjOp());
		setCoeff(arith::conj(coeff()));
		simplify();
	} // only for complex objects
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::itranspose()
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
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualObject<T_Object,T_Virtual>::transpose() const 
{ 
	T_Virtual ret = this->self(); 
	ret.itranspose(); 
	return ret; 
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
void VirtualObject<T_Object,T_Virtual>::ictranspose()
{
	iconjugate();
	itranspose();
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualObject<T_Object,T_Virtual>::ctranspose() const 
{ 
	T_Virtual ret = this->self(); 
	ret.ictranspose(); 
	return ret; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualVector<T_Vector>::VirtualVector()
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualVector<T_Vector>::VirtualVector(const T_Vector& vec)
	: VirtualObject<T_Vector,VirtualVector<T_Vector>>(vec)
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualVector<T_Vector>::~VirtualVector()
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
T_Vector VirtualVector<T_Vector>::evaluate() const
{
	T_Vector ret(this->obj().size());
	evaluateOnExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Vector>
void VirtualVector<T_Vector>::evaluateOnExisting(T_Vector& Y) const
{
	if(this->transOp() != op_t::N) {
		throw err::InvalidOp(
				std::string("Cannot") + 
				std::string(this->transOp() == op_t::C ? " conjugate " : " ") + 
				std::string("transpose a vector"));
	} // op

	Y = this->obj();

	Y.iscale(this->coeff());

	if(this->conjOp()) {
		Y.iconjugate();
	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Vector>
void VirtualVector<T_Vector>::addToExisting(T_Vector& Y) const
{
	if(this->transOp() != op_t::N) {
		throw err::InvalidOp("Cannot update");
	}

	if(!this->conjOp()) {
		ops::update(this->coeff(), this->obj(), Y);
	} else {
		ops::update(T_Scalar(1), evaluate(), Y);
	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Vector>
typename T_Vector::value_type VirtualVector<T_Vector>::evaluateInner(const T_Vector& Y) const
{
	T_Scalar ret = 0;

	if(this->transOp() == op_t::T || this->transOp() == op_t::C) {

		if(this->conjOp()) throw err::Exception(); // should have been simplified

		if(this->transOp() == op_t::T) ret = ops::dot (this->obj(), Y);
		if(this->transOp() == op_t::C) ret = ops::dotc(this->obj(), Y);

		ret *= this->coeff();

	} else {

		throw err::InvalidOp("Cannot multiply");

	} // op combo

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type VirtualVector<T_Vector>::evaluateOuter(const T_Vector& X) const
{
	T_Matrix ret;

	if(this->transOp() == op_t::T || this->transOp() == op_t::C) {

		if(this->conjOp()) throw err::Exception(); // should have been simplified

		if(this->transOp() == op_t::T) ret = ops::outer (X, this->obj());
		if(this->transOp() == op_t::C) ret = ops::outerc(X, this->obj());

		ret.iscale(this->coeff());

	} else {

		throw err::InvalidOp("Cannot multiply");

	} // op combo

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix>::VirtualMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix>::VirtualMatrix(const T_Matrix& mat)
	: VirtualObject<T_Matrix,VirtualMatrix<T_Matrix>>(mat)
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix>::VirtualMatrix(const VirtualVector<T_Vector>& v)
{
	this->setTransOp(v.transOp());
	this->setConjOp(v.conjOp());
	this->setCoeff(v.coeff());
	this->setGuard(v.obj().rmatrix());
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualMatrix<T_Matrix>::~VirtualMatrix()
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
T_Matrix VirtualMatrix<T_Matrix>::evaluate() const
{
	uint_t m = (this->transOp() == op_t::N ? this->obj().nrows() : this->obj().ncols());
	uint_t n = (this->transOp() == op_t::N ? this->obj().ncols() : this->obj().nrows());

	T_Matrix ret(m, n, this->obj().prop());
	evaluateOnExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void VirtualMatrix<T_Matrix>::evaluateOnExisting(T_Matrix& trg) const
{
	const T_Matrix& src = this->obj();

	if(this->transOp() == op_t::N) {

		bulk::dns::copy(src.prop().uplo(), src.nrows(), src.ncols(), src.values(), src.ld(), trg.values(), trg.ld(), this->coeff());

	} else if (this->transOp() == op_t::T) {

		transp_op_consistency_check(src.prop().type(), false);
		bulk::dns::transpose(src.nrows(), src.ncols(), src.values(), src.ld(), trg.values(), trg.ld(), this->coeff());

	} else if(this->transOp() == op_t::C) {

		transp_op_consistency_check(src.prop().type(), true);
		bulk::dns::conjugate_transpose(src.nrows(), src.ncols(), src.values(), src.ld(), trg.values(), trg.ld(), this->coeff());

	} // op

	if(this->conjOp()) {
		trg.iconjugate();
	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void VirtualMatrix<T_Matrix>::addToExisting(T_Matrix& B) const
{
	// FIXME: add transpose without evaluation

	if(this->transOp() == op_t::N && !this->conjOp()) {
		ops::update(this->coeff(), this->obj(), B);
	} else {
		ops::update(T_Scalar(1), evaluate(), B);
	} // conjop
}
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
} // namespace cla3p
/*-------------------------------------------------*/
