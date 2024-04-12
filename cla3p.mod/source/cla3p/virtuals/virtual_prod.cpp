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
#include "cla3p/virtuals/virtual_prod.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/algebra/functional_multmv.hpp"
#include "cla3p/algebra/functional_multmm.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::VirtualProdXx()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::VirtualProdXx(const T_Lhs& lhs, const T_Rhs& rhs)
{
	m_lhs = lhs;
	m_rhs = rhs;
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::~VirtualProdXx()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
const T_Lhs& VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::lhs() const
{ 
	return m_lhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
T_Lhs& VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::lhs()
{ 
	return m_lhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
const T_Rhs& VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::rhs() const
{ 
	return m_rhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
T_Rhs& VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::rhs()
{ 
	return m_rhs; 
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::clear()
{
	lhs().clear();
	rhs().clear();
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::iscale(T_Scalar val)
{
	lhs().iscale(val);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
void VirtualProdXx<T_Lhs,T_Rhs,T_Virtual>::iconjugate()
{
	lhs().iconjugate();
	rhs().iconjugate();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMv<T_Lhs,T_Rhs>::VirtualProdMv()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMv<T_Lhs,T_Rhs>::VirtualProdMv(const T_Lhs& lhs, const T_Rhs& rhs)
	: VirtualProdXx<T_Lhs, T_Rhs, VirtualProdMv<T_Lhs,T_Rhs>>(lhs, rhs)
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMv<T_Lhs,T_Rhs>::~VirtualProdMv()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
const VirtualProdMv<T_Lhs,T_Rhs>& VirtualProdMv<T_Lhs,T_Rhs>::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
typename T_Rhs::value_type VirtualProdMv<T_Lhs,T_Rhs>::evaluate() const
{
	T_Vector ret(
			this->lhs().transOp() == op_t::N ? 
			this->lhs().obj().nrows() : 
			this->lhs().obj().ncols());
	evaluateOnExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
void VirtualProdMv<T_Lhs,T_Rhs>::evaluateOnExisting(T_Vector& trg) const
{
	if(this->rhs().transOp() != op_t::N) {
		throw err::InvalidOp("Cannot multiply");
	}

	trg = 0;
	addToExisting(trg);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
void VirtualProdMv<T_Lhs,T_Rhs>::addToExisting(T_Vector& Y) const
{
	if(this->rhs().transOp() != op_t::N) {
		throw err::InvalidOp("Cannot multiply");
	}

	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

		ops::mult(this->rhs().coeff() * this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), this->rhs().obj(), Y);

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		T_Matrix lhs = this->lhs().evaluate();
		ops::mult(this->rhs().coeff(), op_t::N, lhs, this->rhs().obj(), Y);

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		T_Vector rhs = this->rhs().evaluate();
		ops::mult(this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), rhs, Y);

	} else {

		T_Matrix lhs = this->lhs().evaluate();
		T_Vector rhs = this->rhs().evaluate();
		ops::mult(T_Scalar(1), op_t::N, lhs, rhs, Y);

	} // conjop
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMm<T_Lhs,T_Rhs>::VirtualProdMm()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMm<T_Lhs,T_Rhs>::VirtualProdMm(const T_Lhs& lhs, const T_Rhs& rhs)
	: VirtualProdXx<T_Lhs, T_Rhs, VirtualProdMm<T_Lhs,T_Rhs>>(lhs, rhs)
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
VirtualProdMm<T_Lhs,T_Rhs>::~VirtualProdMm()
{
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
const VirtualProdMm<T_Lhs,T_Rhs>& VirtualProdMm<T_Lhs,T_Rhs>::self() const
{
	return (*this);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
typename T_Rhs::value_type VirtualProdMm<T_Lhs,T_Rhs>::evaluate() const
{
	uint_t m = (this->lhs().transOp() == op_t::N ? this->lhs().obj().nrows() : this->lhs().obj().ncols());
	uint_t n = (this->rhs().transOp() == op_t::N ? this->rhs().obj().ncols() : this->rhs().obj().nrows());

  T_Matrix ret(m, n);
	evaluateOnExisting(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
void VirtualProdMm<T_Lhs,T_Rhs>::evaluateOnExisting(T_Matrix& trg) const
{
	trg = 0;
	addToExisting(trg);
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
void VirtualProdMm<T_Lhs,T_Rhs>::addToExisting(T_Matrix& B) const
{
	if(!this->lhs().conjOp() && !this->rhs().conjOp()) {

		ops::mult(
				this->rhs().coeff() * this->lhs().coeff(), 
				this->lhs().transOp(), this->lhs().obj(), 
				this->rhs().transOp(), this->rhs().obj(), 
				B);

	} else if(this->lhs().conjOp() && !this->rhs().conjOp()) {

		typename T_Lhs::value_type lhs = this->lhs().evaluate();
		ops::mult(this->rhs().coeff(), op_t::N, lhs, this->rhs().transOp(), this->rhs().obj(), B);

	} else if(!this->lhs().conjOp() && this->rhs().conjOp()) {

		typename T_Rhs::value_type rhs = this->rhs().evaluate();
		ops::mult(this->lhs().coeff(), this->lhs().transOp(), this->lhs().obj(), op_t::N, rhs, B);

	} else {

		typename T_Lhs::value_type lhs = this->lhs().evaluate();
		typename T_Rhs::value_type rhs = this->rhs().evaluate();
		ops::mult(T_Scalar(1), op_t::N, lhs, op_t::N, rhs, B);

	} // conjop
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
typename T_Rhs::value_type VirtualProdMm<T_Lhs,T_Rhs>::transpose() const
{
	return evaluate().transpose();
}
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs>
typename T_Rhs::value_type VirtualProdMm<T_Lhs,T_Rhs>::ctranspose() const
{
	return evaluate().ctranspose();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualProdXx<VirtualMatrix<dns::RdMatrix>, VirtualVector<dns::RdVector>, VirtualProdMv<VirtualMatrix<dns::RdMatrix>, VirtualVector<dns::RdVector>>>;
template class VirtualProdXx<VirtualMatrix<dns::RfMatrix>, VirtualVector<dns::RfVector>, VirtualProdMv<VirtualMatrix<dns::RfMatrix>, VirtualVector<dns::RfVector>>>;
template class VirtualProdXx<VirtualMatrix<dns::CdMatrix>, VirtualVector<dns::CdVector>, VirtualProdMv<VirtualMatrix<dns::CdMatrix>, VirtualVector<dns::CdVector>>>;
template class VirtualProdXx<VirtualMatrix<dns::CfMatrix>, VirtualVector<dns::CfVector>, VirtualProdMv<VirtualMatrix<dns::CfMatrix>, VirtualVector<dns::CfVector>>>;
/*-------------------------------------------------*/
template class VirtualProdMv<VirtualMatrix<dns::RdMatrix>, VirtualVector<dns::RdVector>>;
template class VirtualProdMv<VirtualMatrix<dns::RfMatrix>, VirtualVector<dns::RfVector>>;
template class VirtualProdMv<VirtualMatrix<dns::CdMatrix>, VirtualVector<dns::CdVector>>;
template class VirtualProdMv<VirtualMatrix<dns::CfMatrix>, VirtualVector<dns::CfVector>>;
/*-------------------------------------------------*/
template class VirtualProdXx<VirtualMatrix<dns::RdMatrix>, VirtualMatrix<dns::RdMatrix>, VirtualProdMm<VirtualMatrix<dns::RdMatrix>,VirtualMatrix<dns::RdMatrix>>>;
template class VirtualProdXx<VirtualMatrix<dns::RfMatrix>, VirtualMatrix<dns::RfMatrix>, VirtualProdMm<VirtualMatrix<dns::RfMatrix>,VirtualMatrix<dns::RfMatrix>>>;
template class VirtualProdXx<VirtualMatrix<dns::CdMatrix>, VirtualMatrix<dns::CdMatrix>, VirtualProdMm<VirtualMatrix<dns::CdMatrix>,VirtualMatrix<dns::CdMatrix>>>;
template class VirtualProdXx<VirtualMatrix<dns::CfMatrix>, VirtualMatrix<dns::CfMatrix>, VirtualProdMm<VirtualMatrix<dns::CfMatrix>,VirtualMatrix<dns::CfMatrix>>>;
/*-------------------------------------------------*/
template class VirtualProdMm<VirtualMatrix<dns::RdMatrix>,VirtualMatrix<dns::RdMatrix>>;
template class VirtualProdMm<VirtualMatrix<dns::RfMatrix>,VirtualMatrix<dns::RfMatrix>>;
template class VirtualProdMm<VirtualMatrix<dns::CdMatrix>,VirtualMatrix<dns::CdMatrix>>;
template class VirtualProdMm<VirtualMatrix<dns::CfMatrix>,VirtualMatrix<dns::CfMatrix>>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
