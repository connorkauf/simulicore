// this file inc
#include "dns_rxmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define RxMatrixTmpl RxMatrix<T_Scalar>
#define RxMatrixTlst template <typename T_Scalar>
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: RxMatrixTmpl::XxMatrix(nr, nc, pr)
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::~RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix(RxMatrixTmpl&& /*other*/)
{
	// FIXME: implement
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl& RxMatrixTmpl::operator=(RxMatrixTmpl&& /*other*/)
{
	// FIXME: implement
	return *this;
}
/*-------------------------------------------------*/
RxMatrixTlst
void RxMatrixTmpl::operator=(T_Scalar val)
{
	RxMatrixTmpl::XxMatrix::operator=(val);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxMatrixTmpl
#undef RxMatrixTlst
/*-------------------------------------------------*/
template class RxMatrix<real_t>;
template class RxMatrix<real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
