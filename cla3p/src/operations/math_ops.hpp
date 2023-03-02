#ifndef CLA3P_MATH_OPS_HPP_
#define CLA3P_MATH_OPS_HPP_

#include "../types.hpp"
#include "../dense.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

// trg += alpha * src
void update(int_t      alpha, const dns::RiVector& src, dns::RiVector& trg);
void update(real_t     alpha, const dns::RdVector& src, dns::RdVector& trg);
void update(real4_t    alpha, const dns::RfVector& src, dns::RfVector& trg);
void update(complex_t  alpha, const dns::CdVector& src, dns::CdVector& trg);
void update(complex8_t alpha, const dns::CfVector& src, dns::CfVector& trg);

void update(int_t      alpha, const dns::RiMatrix& src, dns::RiMatrix& trg);
void update(real_t     alpha, const dns::RdMatrix& src, dns::RdMatrix& trg);
void update(real4_t    alpha, const dns::RfMatrix& src, dns::RfMatrix& trg);
void update(complex_t  alpha, const dns::CdMatrix& src, dns::CdMatrix& trg);
void update(complex8_t alpha, const dns::CfMatrix& src, dns::CfMatrix& trg);

// returns trg = alpha * srcA + beta * srcB
dns::RiVector add(int_t      alpha, const dns::RiVector& srcA, int_t      beta, const dns::RiVector& srcB);
dns::RdVector add(real_t     alpha, const dns::RdVector& srcA, real_t     beta, const dns::RdVector& srcB);
dns::RfVector add(real4_t    alpha, const dns::RfVector& srcA, real4_t    beta, const dns::RfVector& srcB);
dns::CdVector add(complex_t  alpha, const dns::CdVector& srcA, complex_t  beta, const dns::CdVector& srcB);
dns::CfVector add(complex8_t alpha, const dns::CfVector& srcA, complex8_t beta, const dns::CfVector& srcB);

dns::RiMatrix add(int_t      alpha, const dns::RiMatrix& srcA, int_t      beta, const dns::RiMatrix& srcB);
dns::RdMatrix add(real_t     alpha, const dns::RdMatrix& srcA, real_t     beta, const dns::RdMatrix& srcB);
dns::RfMatrix add(real4_t    alpha, const dns::RfMatrix& srcA, real4_t    beta, const dns::RfMatrix& srcB);
dns::CdMatrix add(complex_t  alpha, const dns::CdMatrix& srcA, complex_t  beta, const dns::CdMatrix& srcB);
dns::CfMatrix add(complex8_t alpha, const dns::CfMatrix& srcA, complex8_t beta, const dns::CfMatrix& srcB);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATH_OPS_HPP_
