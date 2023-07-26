#ifndef CLA3P_DNS_FLVECTOR_HPP_
#define CLA3P_DNS_FLVECTOR_HPP_
/*-------------------------------------------------*/
//
//
// Common functionality for floating point dense vectors
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
ThisRealType XxVector::normOne() const { return ThisObjectType::normOne(); }
ThisRealType XxVector::normInf() const { return ThisObjectType::normInf(); }
ThisRealType XxVector::normEuc() const { return ThisObjectType::normEuc(); }
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_FLVECTOR_HPP_
