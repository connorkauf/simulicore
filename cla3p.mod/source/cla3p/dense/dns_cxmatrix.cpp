// this file inc
#include "cla3p/dense/dns_cxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/dense/dns_rxmatrix.hpp"
#include "cla3p/checks/transp_checks.hpp"

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
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Symmetric, this->prop().uplo()) : this->prop());

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
	Property ret_prop = (this->prop().isHermitian() ? Property(prop_t::Skew, this->prop().uplo()) : this->prop());

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
CxMatrixTlst
CxMatrixTmpl CxMatrixTmpl::ctranspose() const
{
	transp_op_consistency_check(this->prop().type(), true);
	
	CxMatrixTmpl ret(this->nrows(), this->ncols(), this->prop());

	bulk::dns::conjugate_transpose(
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld(), 
			ret.values(), ret.ld());

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
template<> std::string BasicTypeTraits<dns::CxMatrix<complex_t>>::type_name() { return msg::DenseMatrix(); }
template<> std::string BasicTypeTraits<dns::CxMatrix<complex8_t>>::type_name() { return msg::DenseMatrix(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
