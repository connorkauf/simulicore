#ifndef CLA3P_DNS_CXMATRIX_HPP_
#define CLA3P_DNS_CXMATRIX_HPP_
/*-------------------------------------------------*/
//
//
// Common functionality for complex dense matrices
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
XxMatrix XxMatrix::ctranspose() const
{
	XxMatrix ret;
	ThisObjectType::ctransposeTo(ret);
	return ret.move();
}
/*-------------------------------------------------*/
void XxMatrix::iconjugate()
{
	ThisObjectType::conjugateIp();
}
/*-------------------------------------------------*/
RxMatrix XxMatrix::realPart() const
{
	RxMatrix ret;
	ThisObjectType::getRealPart(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RxMatrix XxMatrix::imagPart() const
{
	RxMatrix ret;
	ThisObjectType::getImagPart(ret);
	return ret.move();
}
/*-------------------------------------------------*/
void XxMatrix::setRealPart(const RxMatrix& src)
{
	ThisObjectType::setRealPart(src);
}
/*-------------------------------------------------*/
void XxMatrix::setImagPart(const RxMatrix& src)
{
	ThisObjectType::setImagPart(src);
}
/*-------------------------------------------------*/
RxMatrix XxMatrix::realBlock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RxMatrix ret;
	ThisObjectType::getRealBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
RxMatrix XxMatrix::imagBlock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	RxMatrix ret;
	ThisObjectType::getImagBlock(ret, ibgn, jbgn, ni, nj);
	return ret.move();
}
/*-------------------------------------------------*/
void XxMatrix::setRealBlock(uint_t ibgn, uint_t jbgn, const RxMatrix& src)
{
	ThisObjectType::setRealBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
void XxMatrix::setImagBlock(uint_t ibgn, uint_t jbgn, const RxMatrix& src)
{
	ThisObjectType::setImagBlock(src, ibgn, jbgn);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXMATRIX_HPP_
