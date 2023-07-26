#ifndef CLA3P_DNS_CXVECTOR_HPP_
#define CLA3P_DNS_CXVECTOR_HPP_
/*-------------------------------------------------*/
//
//
// Common functionality for complex dense vectors
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
RxVector XxVector::realPart() const
{
	RxVector ret;
	ThisObjectType::getRealPart(ret);
	return ret.move();
}
/*-------------------------------------------------*/
RxVector XxVector::imagPart() const
{
	RxVector ret;
	ThisObjectType::getImagPart(ret);
	return ret.move();
}
/*-------------------------------------------------*/
void XxVector::setRealPart(const RxVector& src)
{
	ThisObjectType::setRealPart(src);
}
/*-------------------------------------------------*/
void XxVector::setImagPart(const RxVector& src)
{
	ThisObjectType::setImagPart(src);
}
/*-------------------------------------------------*/
RxVector XxVector::realBlock(uint_t ibgn, uint_t ni) const
{
	RxVector ret;
	ThisObjectType::getRealBlock(ret, ibgn, 0, ni, 1);
	return ret.move();
}
/*-------------------------------------------------*/
RxVector XxVector::imagBlock(uint_t ibgn, uint_t ni) const
{
	RxVector ret;
	ThisObjectType::getImagBlock(ret, ibgn, 0, ni, 1);
	return ret.move();
}
/*-------------------------------------------------*/
void XxVector::setRealBlock(uint_t ibgn, const RxVector& src)
{
	ThisObjectType::setRealBlock(src, ibgn, 0);
}
/*-------------------------------------------------*/
void XxVector::setImagBlock(uint_t ibgn, const RxVector& src)
{
	ThisObjectType::setImagBlock(src, ibgn, 0);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXVECTOR_HPP_
