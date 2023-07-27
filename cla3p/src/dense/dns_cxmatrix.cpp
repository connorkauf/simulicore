// this file inc
#include "dns_cxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

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
