// this file inc
#include "dns_xxobject.hpp"

// system

// 3rd

// cla3p
#include "../bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxObjectTmpl XxObject<T_Scalar,T_RScalar>
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
XxObjectTmpl::XxObject()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
XxObjectTmpl::~XxObject()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
void XxObjectTmpl::scale(T_Scalar val)
{
	bulk::dns::scale(uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize(), val);
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
T_RScalar XxObjectTmpl::normOne() const
{ 
	return bulk::dns::norm_one(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
T_RScalar XxObjectTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
T_RScalar XxObjectTmpl::normMax() const
{ 
	return bulk::dns::norm_max(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_RScalar>
T_RScalar XxObjectTmpl::normFro() const
{ 
	return bulk::dns::norm_fro(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxObjectTmpl
/*-------------------------------------------------*/
template class XxObject<real_t    ,real_t >;
template class XxObject<real4_t   ,real4_t>;
template class XxObject<complex_t ,real_t >;
template class XxObject<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
