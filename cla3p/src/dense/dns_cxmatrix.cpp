// this file inc
#include "dns_cxmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define CxMatrixTmpl CxMatrix<T_Scalar,T_RScalar>
#define CxMatrixTlst template <typename T_Scalar, typename T_RScalar>
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
CxMatrixTmpl::CxMatrix(CxMatrixTmpl&& /*other*/)
{
  // FIXME: implement
}
/*-------------------------------------------------*/
CxMatrixTlst
CxMatrixTmpl& CxMatrixTmpl::operator=(CxMatrixTmpl&& /*other*/)
{
	// FIXME: implement
	return *this;
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
template class CxMatrix<complex_t,real_t>;
template class CxMatrix<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
