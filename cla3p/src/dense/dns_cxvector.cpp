// this file inc
#include "dns_cxvector.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"
#include "../bulk/dns.hpp"
#include "../checks/all_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxVectorTmpl CxVector<T_Scalar>
#define CxVectorTlst template <typename T_Scalar>
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector()
{
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::CxVector(uint_t n)
	: CxVectorTmpl::XxVector(n)
{
}
/*-------------------------------------------------*/
CxVectorTlst
CxVectorTmpl::~CxVector()
{
}
/*-------------------------------------------------*/
CxVectorTlst
void CxVectorTmpl::operator=(T_Scalar val)
{
	CxVectorTmpl::XxVector::operator=(val);
}
/*-------------------------------------------------*/
CxVectorTlst
typename CxVectorTmpl::T_RVector CxVectorTmpl::real() const
{
	T_RVector ret(this->size());
	bulk::dns::get_real(uplo_t::F, this->size(), 1, this->values(), this->lsize(), ret.values(), ret.lsize());
	return ret;
}
/*-------------------------------------------------*/
CxVectorTlst
typename CxVectorTmpl::T_RVector CxVectorTmpl::imag() const
{
	T_RVector ret(this->size());
	bulk::dns::get_imag(uplo_t::F, this->size(), 1, this->values(), this->lsize(), ret.values(), ret.lsize());
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxVectorTmpl
#undef CxVectorTlst
/*-------------------------------------------------*/
template class CxVector<complex_t>;
template class CxVector<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template<> const std::string& BasicTypeTraits<dns::CxVector<complex_t>>::type_name() { return stringDenseVector(); }
template<> const std::string& BasicTypeTraits<dns::CxVector<complex8_t>>::type_name() { return stringDenseVector(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/


