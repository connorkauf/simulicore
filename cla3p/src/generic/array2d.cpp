// this file inc
#include "array2d.hpp"

// system

// 3rd

// cla3p
#include "../bulk/dns.hpp"
#include "../bulk/dns_io.hpp"
#include "../support/imalloc.hpp"
#include "../support/error.hpp"

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
Array2D<T_Scalar>::~Array2D()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::Array2D(Array2D<T_Scalar>&& src)
{
	src.moveTo(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>& Array2D<T_Scalar>::operator=(Array2D<T_Scalar>&& src)
{
	src.moveTo(*this);
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::defaults()
{
	Ownership::defaults();

	setRsize(0);
	setCsize(0);
	setLsize(0);
	setValues(nullptr);
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
void Array2D<T_Scalar>::creator(uint_t nr, uint_t nc, uint_t nl)
{
	T_Scalar *vals = bulk::dns::alloc<T_Scalar>(nr, nc, nl);
	wrapper(nr, nc, vals, nl, true);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::wrapper(uint_t nr, uint_t nc, T_Scalar *vals, uint_t nl, bool bind)
{
	clear();

	setRsize(nr);
	setCsize(nc);
	setLsize(nl);
	setValues(vals);

	setOwner(bind);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::clear()
{
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
	bulk::dns::fill(uplo_t::F, rsize(), csize(), values(), lsize(), val);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::print(uint_t nsd) const
{
	bulk::dns::print(uplo_t::F, rsize(), csize(), values(), lsize(), nsd);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string Array2D<T_Scalar>::toString(uint_t nsd) const
{
	return bulk::dns::print_to_string(uplo_t::F, rsize(), csize(), values(), lsize(), nsd);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::copyTo(Array2D<T_Scalar>& trg) const
{
	if(this == &trg) return; // do not apply on self

	if(!empty()) {
		trg.creator(rsize(), csize(), lsize());
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

	if(rsize() == trg.rsize() && csize() == trg.csize()) {
		bulk::dns::copy(uplo_t::F, rsize(), csize(), values(), lsize(), trg.values(), trg.lsize());
	} else {
		throw NoConsistency("Dimension mismatch when copying");
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
void Array2D<T_Scalar>::permuteToLeftRight(Array2D<T_Scalar>& trg, const uint_t *P, const uint_t *Q) const
{
	trg.creator(rsize(), csize(), rsize());
	bulk::dns::permute(prop_t::GENERAL, uplo_t::F, rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), P, Q);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::permuteToLeftRight(Array2D<T_Scalar>& trg, const int_t *P, const int_t *Q) const
{
	trg.creator(rsize(), csize(), rsize());
	bulk::dns::permute(prop_t::GENERAL, uplo_t::F, rsize(), csize(), values(), lsize(), trg.values(), trg.lsize(), P, Q);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::permuteIpLeftRight(const uint_t *P, const uint_t *Q)
{
	Array2D<T_Scalar> tmp;
	permuteToLeftRight(tmp, P, Q);
	tmp.copyToAllocated(*this);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::permuteIpLeftRight(const int_t *P, const int_t *Q)
{
	Array2D<T_Scalar> tmp;
	permuteToLeftRight(tmp, P, Q);
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
