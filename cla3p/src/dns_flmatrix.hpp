#ifndef CLA3P_DNS_FLMATRIX_HPP_
#define CLA3P_DNS_FLMATRIX_HPP_
/*-------------------------------------------------*/
//
//
// Common functionality for floating point dense matrices
//
//
/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
ThisRealType XxMatrix::normOne() const { return ThisObjectType::normOne(); }
ThisRealType XxMatrix::normInf() const { return ThisObjectType::normInf(); }
ThisRealType XxMatrix::normMax() const { return ThisObjectType::normMax(); }
ThisRealType XxMatrix::normFro() const { return ThisObjectType::normFro(); }
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_FLMATRIX_HPP_
