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
#include "cla3p/virtuals/virtual_pair.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/algebra/functional.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::VirtualPairXx()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::VirtualPairXx(const T_Lhs& lhs, const T_Rhs& rhs)
{
	m_lhs = lhs;
	m_rhs = rhs;
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::~VirtualPairXx()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
const T_Lhs& VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::lhs() const
{ 
	return m_lhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
T_Lhs& VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::lhs()
{ 
	return m_lhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
const T_Rhs& VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::rhs() const
{ 
	return m_rhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
T_Rhs& VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::rhs()
{ 
	return m_rhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::clear()
{
	lhs().clear();
	rhs().clear();
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::iscale(T_Scalar val)
{
	lhs().iscale(val);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualPairXx<T_Lhs,T_Rhs,T_Virtual>::iconjugate()
{
	lhs().iconjugate();
	rhs().iconjugate();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualPairMv<T_Vector>::VirtualPairMv()
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualPairMv<T_Vector>::VirtualPairMv(const VirtualMatrix<T_Matrix>& lhs, const VirtualVector<T_Vector>& rhs)
	: VirtualPairXx<VirtualMatrix<T_Matrix>, VirtualVector<T_Vector>, VirtualPairMv<T_Vector>>(lhs, rhs)
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualPairMv<T_Vector>::~VirtualPairMv()
{
}
/*-------------------------------------------------*/
template <typename T_Vector>
const VirtualPairMv<T_Vector>& VirtualPairMv<T_Vector>::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
template <typename T_Vector>
T_Vector VirtualPairMv<T_Vector>::evaluate() const
{
	if(this->rhs().transOp() != op_t::N) {
		throw err::InvalidOp("Cannot multiply");
	}

	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

		return ops::mult(this->rhs().coeff() * this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), this->rhs().obj());

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		T_Matrix lhs = this->lhs().evaluate();
		return ops::mult(this->rhs().coeff(), op_t::N, lhs, this->rhs().obj());

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		T_Vector rhs = this->rhs().evaluate();
		return ops::mult(this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), rhs);

	} else {

		T_Matrix lhs = this->lhs().evaluate();
		T_Vector rhs = this->rhs().evaluate();
		return ops::mult(T_Scalar(1), op_t::N, lhs, rhs);

	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Vector>
void VirtualPairMv<T_Vector>::update(T_Scalar c, T_Vector& Y) const
{
	if(this->rhs().transOp() != op_t::N) {
		throw err::InvalidOp("Cannot multiply");
	}

	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

		ops::mult(c * this->rhs().coeff() * this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), this->rhs().obj(), Y);

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		T_Matrix lhs = this->lhs().evaluate();
		ops::mult(c * this->rhs().coeff(), op_t::N, lhs, this->rhs().obj(), Y);

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		T_Vector rhs = this->rhs().evaluate();
		ops::mult(c * this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), rhs, Y);

	} else {

		T_Matrix lhs = this->lhs().evaluate();
		T_Vector rhs = this->rhs().evaluate();
		ops::mult(c, op_t::N, lhs, rhs, Y);

	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Vector>
VirtualPairMv<T_Vector>::operator T_Vector() const 
{ 
	return evaluate(); 
};
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix>::VirtualPairMm()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix>::VirtualPairMm(const VirtualMatrix<T_Matrix>& lhs, const VirtualMatrix<T_Matrix>& rhs)
	: VirtualPairXx<VirtualMatrix<T_Matrix>, VirtualMatrix<T_Matrix>, VirtualPairMm<T_Matrix>>(lhs, rhs)
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix>::~VirtualPairMm()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
const VirtualPairMm<T_Matrix>& VirtualPairMm<T_Matrix>::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
T_Matrix VirtualPairMm<T_Matrix>::evaluate() const
{
	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

	return ops::mult(
			this->rhs().coeff() * this->lhs().coeff(), 
			this->lhs().transOp(), this->lhs().obj(), 
			this->rhs().transOp(), this->rhs().obj());

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		T_Matrix lhs = this->lhs().evaluate();
		return ops::mult(this->rhs().coeff(), op_t::N, lhs, this->rhs().transOp(), this->rhs().obj());

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		T_Matrix rhs = this->rhs().evaluate();
		return ops::mult(this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), op_t::N, rhs);

	} else {

		T_Matrix lhs = this->lhs().evaluate();
		T_Matrix rhs = this->rhs().evaluate();
		return ops::mult(T_Scalar(1), op_t::N, lhs, op_t::N, rhs);

	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void VirtualPairMm<T_Matrix>::update(T_Scalar c, T_Matrix& B) const
{
	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

		ops::mult(
				c * this->rhs().coeff() * this->lhs().coeff(), 
				this->lhs().transOp(), this->lhs().obj(), 
				this->rhs().transOp(), this->rhs().obj(), 
				B);

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		T_Matrix lhs = this->lhs().evaluate();
		ops::mult(c * this->rhs().coeff(), op_t::N, lhs, this->rhs().transOp(), this->rhs().obj(), B);

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		T_Matrix rhs = this->rhs().evaluate();
		ops::mult(c * this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), op_t::N, rhs, B);

	} else {

		T_Matrix lhs = this->lhs().evaluate();
		T_Matrix rhs = this->rhs().evaluate();
		ops::mult(c, op_t::N, lhs, op_t::N, rhs, B);

	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix>::operator T_Matrix() const 
{ 
	return evaluate(); 
};
/*-------------------------------------------------*/
template <typename T_Matrix>
void VirtualPairMm<T_Matrix>::swap() 
{
	VirtualMatrix<T_Matrix> tmp = this->rhs();
	this->rhs() = this->lhs();
	this->lhs() = tmp;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix> VirtualPairMm<T_Matrix>::transpose() const
{
	VirtualPairMm<T_Matrix> ret(this->rhs(), this->lhs());
	ret.lhs().itranspose();
	ret.rhs().itranspose();
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
VirtualPairMm<T_Matrix> VirtualPairMm<T_Matrix>::ctranspose() const
{
	VirtualPairMm<T_Matrix> ret(this->rhs(), this->lhs());
	ret.lhs().ictranspose();
	ret.rhs().ictranspose();
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualPairXx<VirtualMatrix<dns::RdMatrix>, VirtualVector<dns::RdVector>, VirtualPairMv<dns::RdVector>>;
template class VirtualPairXx<VirtualMatrix<dns::RfMatrix>, VirtualVector<dns::RfVector>, VirtualPairMv<dns::RfVector>>;
template class VirtualPairXx<VirtualMatrix<dns::CdMatrix>, VirtualVector<dns::CdVector>, VirtualPairMv<dns::CdVector>>;
template class VirtualPairXx<VirtualMatrix<dns::CfMatrix>, VirtualVector<dns::CfVector>, VirtualPairMv<dns::CfVector>>;
/*-------------------------------------------------*/
template class VirtualPairMv<dns::RdVector>;
template class VirtualPairMv<dns::RfVector>;
template class VirtualPairMv<dns::CdVector>;
template class VirtualPairMv<dns::CfVector>;
/*-------------------------------------------------*/
template class VirtualPairXx<VirtualMatrix<dns::RdMatrix>, VirtualMatrix<dns::RdMatrix>, VirtualPairMm<dns::RdMatrix>>;
template class VirtualPairXx<VirtualMatrix<dns::RfMatrix>, VirtualMatrix<dns::RfMatrix>, VirtualPairMm<dns::RfMatrix>>;
template class VirtualPairXx<VirtualMatrix<dns::CdMatrix>, VirtualMatrix<dns::CdMatrix>, VirtualPairMm<dns::CdMatrix>>;
template class VirtualPairXx<VirtualMatrix<dns::CfMatrix>, VirtualMatrix<dns::CfMatrix>, VirtualPairMm<dns::CfMatrix>>;
/*-------------------------------------------------*/
template class VirtualPairMm<dns::RdMatrix>;
template class VirtualPairMm<dns::RfMatrix>;
template class VirtualPairMm<dns::CdMatrix>;
template class VirtualPairMm<dns::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
