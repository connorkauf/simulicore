/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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
#include "cla3p/generic/array2d.hpp"

// system

// 3rd

// cla3p
#include "cla3p/perms.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/dns_io.hpp"
#include "cla3p/support/imalloc.hpp"
#include "cla3p/error/error.hpp"

#include "cla3p/checks/dns_checks.hpp"
#include "cla3p/checks/perm_checks.hpp"

#include "cla3p/types/integer_internal.hpp"
#include "cla3p/types/scalar_internal.hpp"
#include "cla3p/types/property_internal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::Array2D()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::Array2D(uint_t nr, uint_t nc, uint_t nl, const Property& pr)
{
	T_Scalar *vals = bulk::dns::alloc<T_Scalar>(nr, nc, nl);
	wrapper(nr, nc, nl, vals, true, pr);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::~Array2D()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::Array2D(Array2D<T_Scalar>&& other)
{
	other.moveTo(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>& Array2D<T_Scalar>::operator=(Array2D<T_Scalar>&& other)
{
	other.moveTo(*this);
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::defaults()
{
	setRsize(0);
	setCsize(0);
	setLsize(0);
	setValues(nullptr);
	property().clear();
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setRsize(uint_t nr) 
{ 
	m_rsize = nr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setCsize(uint_t nc) 
{
	m_csize = nc; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setLsize(uint_t nl) 
{
	m_lsize = nl; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setValues(T_Scalar* vals) 
{ 
	m_values = vals; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setProperty(const Property& pr) 
{ 
	m_property = pr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
uint_t Array2D<T_Scalar>::rsize() const
{ 
	return m_rsize; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
uint_t Array2D<T_Scalar>::csize() const
{
	return m_csize; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
uint_t Array2D<T_Scalar>::lsize() const
{
	return m_lsize; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
T_Scalar* Array2D<T_Scalar>::values() 
{ 
	return m_values; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
const T_Scalar* Array2D<T_Scalar>::values() const
{ 
	return m_values; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
const Property& Array2D<T_Scalar>::property() const
{ 
	return m_property; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
Property& Array2D<T_Scalar>::property()
{ 
	return m_property; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::wrapper(uint_t nr, uint_t nc, uint_t nl, T_Scalar *vals, bool bind, const Property& pr)
{
	Property pr2 = checkProperty<T_Scalar>(pr);

	dns_consistency_check(pr2, nr, nc, vals, nl);

	clear();

	setRsize(nr);
	setCsize(nc);
	setLsize(nl);
	setValues(vals);
	setProperty(pr2);

	setOwner(bind);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::clear()
{
	Ownership::clear();

	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
bool Array2D<T_Scalar>::empty() const
{
	return (!rsize() || !csize());
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::fill(T_Scalar val)
{
	if(property().isHermitian()) {
		T_Scalar diag = val;
		setim(diag,0);
		bulk::dns::fill(property().uplo(), rsize(), csize(), values(), lsize(), val, diag);
	} else if(property().isSkew()) {
		T_Scalar diag = 0;
		bulk::dns::fill(property().uplo(), rsize(), csize(), values(), lsize(), val, diag);
	} else {
		bulk::dns::fill(property().uplo(), rsize(), csize(), values(), lsize(), val);
	}
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::print(uint_t nsd) const
{
	bulk::dns::print(property().uplo(), rsize(), csize(), values(), lsize(), nsd);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string Array2D<T_Scalar>::toString(uint_t nsd) const
{
	return bulk::dns::print_to_string(property().uplo(), rsize(), csize(), values(), lsize(), nsd);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::copyTo(Array2D<T_Scalar>& trg) const
{
	if(this == &trg) return; // do not apply on self

	if(!empty()) {
		trg = Array2D<T_Scalar>(rsize(), csize(), lsize(), property());
		copyToAllocated(trg);
	} else {
		trg.clear();
	} // (!)empty
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::copyToAllocated(Array2D<T_Scalar>& trg) const
{
	if(this == &trg) return; // do not apply on self

	bool areSame = (rsize() == trg.rsize() && csize() == trg.csize() && property().uplo() == trg.property().uplo());

	if(areSame) {
		bulk::dns::copy(property().uplo(), rsize(), csize(), values(), lsize(), trg.values(), trg.lsize());
	} else {
		throw err::NoConsistency("Dimension and/or property mismatch when copying");
	}
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::copyToShallow(Array2D<T_Scalar>& trg)
{
	if(this == &trg) return; // do not apply on self

	trg.clear();
	trg.setRsize(rsize());
	trg.setCsize(csize());
	trg.setLsize(lsize());
	trg.setValues(values());
	trg.setProperty(property());

	trg.unbind();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::moveTo(Array2D<T_Scalar>& trg)
{
	copyToShallow(trg);
	trg.setOwner(owner());
	unbind();
	clear();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar& Array2D<T_Scalar>::operator()(uint_t i, uint_t j)
{
	return bulk::dns::entry(lsize(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const T_Scalar& Array2D<T_Scalar>::operator()(uint_t i, uint_t j) const
{
	return bulk::dns::entry(lsize(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteToLeftRight(Array2D<T_Scalar>& trg, const PiMatrix& P, const PiMatrix& Q) const
{
	perm_ge_op_consistency_check(property().type(), rsize(), csize(), P.size(), Q.size());

	trg = Array2D<T_Scalar>(rsize(), csize(), rsize(), property());
	bulk::dns::permute(property().type(), property().uplo(), rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), P.values(), Q.values());
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteToLeft(Array2D<T_Scalar>& trg, const PiMatrix& P) const
{
	perm_ge_op_consistency_check(property().type(), rsize(), csize(), P.size(), csize());

	trg = Array2D<T_Scalar>(rsize(), csize(), rsize(), property());
	bulk::dns::permute(property().type(), property().uplo(), rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), P.values(), nullptr);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteToRight(Array2D<T_Scalar>& trg, const PiMatrix& Q) const
{
	perm_ge_op_consistency_check(property().type(), rsize(), csize(), rsize(), Q.size());

	trg = Array2D<T_Scalar>(rsize(), csize(), rsize(), property());
	bulk::dns::permute(property().type(), property().uplo(), rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), nullptr, Q.values());
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::xxPermuteToMirror(Array2D<T_Scalar>& trg, const PiMatrix& P) const
{
	perm_op_consistency_check(rsize(), csize(), P.size(), P.size());

	PiMatrix iP;
	if(property().isGeneral()) iP = P.inverse();

	trg = Array2D<T_Scalar>(rsize(), csize(), rsize(), property());
	bulk::dns::permute(property().type(), property().uplo(), rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), P.values(), iP.values());
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteIpLeftRight(const PiMatrix& P, const PiMatrix& Q)
{
	Array2D<T_Scalar> tmp;
	gePermuteToLeftRight(tmp, P, Q);
	tmp.copyToAllocated(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteIpLeft(const PiMatrix& P)
{
	Array2D<T_Scalar> tmp;
	gePermuteToLeft(tmp, P);
	tmp.copyToAllocated(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::gePermuteIpRight(const PiMatrix& Q)
{
	Array2D<T_Scalar> tmp;
	gePermuteToRight(tmp, Q);
	tmp.copyToAllocated(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::xxPermuteIpMirror(const PiMatrix& P)
{
	Array2D<T_Scalar> tmp;
	xxPermuteToMirror(tmp, P);
	tmp.copyToAllocated(*this);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class Array2D<int_t>;
template class Array2D<uint_t>;
template class Array2D<real_t>;
template class Array2D<real4_t>;
template class Array2D<complex_t>;
template class Array2D<complex8_t>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
