// this file inc
#include "dns_cxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"
#include "../bulk/dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxMatrixTmpl CxMatrix<T_Scalar>
#define CxMatrixTlst template <typename T_Scalar>
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix()
{
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::CxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: CxMatrixTmpl::XxMatrix(nr, nc, pr)
{
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl::~CxMatrix()
{
}
/*-------------------------------------------------*/
CxMatrixTlst
void CxMatrixTmpl::operator=(T_Scalar val)
{
	CxMatrixTmpl::XxMatrix::operator=(val);
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::real() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::SYMMETRIC, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), ret_prop);

	bulk::dns::get_real(
			this->prop().uplo(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->lsize(), 
			ret.values(), ret.lsize());

	return ret;
}
/*-------------------------------------------------*/
CxMatrixTlst
typename CxMatrixTmpl::T_RMatrix CxMatrixTmpl::imag() const
{
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::SKEW, this->prop().uplo()) : this->prop());

	T_RMatrix ret(this->nrows(), this->ncols(), ret_prop);

	bulk::dns::get_imag(
			this->prop().uplo(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->lsize(), 
			ret.values(), ret.lsize());

	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef CxMatrixTmpl
#undef CxMatrixTlst
/*-------------------------------------------------*/
template class CxMatrix<complex_t>;
template class CxMatrix<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template<> const std::string& BasicTypeTraits<dns::CxMatrix<complex_t>>::type_name() { return stringDenseMatrix(); }
template<> const std::string& BasicTypeTraits<dns::CxMatrix<complex8_t>>::type_name() { return stringDenseMatrix(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
