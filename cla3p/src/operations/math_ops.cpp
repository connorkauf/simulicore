// this file inc
#include "math_ops.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T, typename Tobj>
static void dns_update_tmpl(T alpha, const Tobj& src, Tobj& trg)
{
	trg.updateSelf(alpha, src);
}
/*-------------------------------------------------*/
void update(int_t      alpha, const dns::RiVector& src, dns::RiVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real_t     alpha, const dns::RdVector& src, dns::RdVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real4_t    alpha, const dns::RfVector& src, dns::RfVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex_t  alpha, const dns::CdVector& src, dns::CdVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex8_t alpha, const dns::CfVector& src, dns::CfVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(int_t      alpha, const dns::RiMatrix& src, dns::RiMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real_t     alpha, const dns::RdMatrix& src, dns::RdMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real4_t    alpha, const dns::RfMatrix& src, dns::RfMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex_t  alpha, const dns::CdMatrix& src, dns::CdMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex8_t alpha, const dns::CfMatrix& src, dns::CfMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
/*-------------------------------------------------*/
template <typename T, typename Tobj>
static Tobj dns_add_tmpl(T alpha, const Tobj& srcA, T beta, const Tobj& srcB)
{
	Tobj ret;
	ret.createFromSum(alpha, srcA, beta, srcB);
	return ret.move();
}
/*-------------------------------------------------*/
dns::RiVector add(int_t      alpha, const dns::RiVector& srcA, int_t      beta, const dns::RiVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RdVector add(real_t     alpha, const dns::RdVector& srcA, real_t     beta, const dns::RdVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RfVector add(real4_t    alpha, const dns::RfVector& srcA, real4_t    beta, const dns::RfVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CdVector add(complex_t  alpha, const dns::CdVector& srcA, complex_t  beta, const dns::CdVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CfVector add(complex8_t alpha, const dns::CfVector& srcA, complex8_t beta, const dns::CfVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RiMatrix add(int_t      alpha, const dns::RiMatrix& srcA, int_t      beta, const dns::RiMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RdMatrix add(real_t     alpha, const dns::RdMatrix& srcA, real_t     beta, const dns::RdMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RfMatrix add(real4_t    alpha, const dns::RfMatrix& srcA, real4_t    beta, const dns::RfMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CdMatrix add(complex_t  alpha, const dns::CdMatrix& srcA, complex_t  beta, const dns::CdMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CfMatrix add(complex8_t alpha, const dns::CfMatrix& srcA, complex8_t beta, const dns::CfMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
/*-------------------------------------------------*/
template <typename T, typename Tmat, typename Tvec>
static void dns_update_with_mv_tmpl(T alpha, const Operation& opA, const Tmat& srcA, const Tvec& srcX, Tvec& trg)
{
	trg.updateSelfWithMatVec(alpha, opA, srcA, srcX);
}
/*-------------------------------------------------*/
void mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const dns::RiVector& srcX, dns::RiVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX, dns::RdVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX, dns::RfVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX, dns::CdVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX, dns::CfVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
/*-------------------------------------------------*/
template <typename T, typename Tmat, typename Tvec>
static Tvec dns_mv_tmpl(T alpha, const Operation& opA, const Tmat& srcA, const Tvec& srcX)
{
	Tvec ret = Tvec::zero(opA.isTranspose() ? srcA.ncols() : srcA.nrows());
	mult(alpha, opA, srcA, srcX, ret);
	return ret.move();
}
/*-------------------------------------------------*/
dns::RiVector mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const dns::RiVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::RdVector mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::RfVector mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::CdVector mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::CfVector mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
/*-------------------------------------------------*/
template <typename T, typename Tmat>
static void dns_update_with_gemm_tmpl(T alpha, const Operation& opA, const Tmat& srcA, const Operation& opB, const Tmat& srcB, Tmat& trg)
{
	trg.updateSelfWithGeMatMat(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
void mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const Operation& opB, const dns::RiMatrix& srcB, dns::RiMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB, dns::RdMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB, dns::RfMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB, dns::CdMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const Operation& opB, const dns::CfMatrix& srcB, dns::CfMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
template <typename T, typename Tmat>
static Tmat dns_gemm_tmpl(T alpha, const Operation& opA, const Tmat& srcA, const Operation& opB, const Tmat& srcB)
{
	Tmat ret = Tmat::zero(opA.isTranspose() ? srcA.ncols() : srcA.nrows(), opB.isTranspose() ? srcB.nrows() : srcB.ncols());
	mult(alpha, opA, srcA, opB, srcB, ret);
	return ret.move();
}
/*-------------------------------------------------*/
dns::RiMatrix mult(int_t      alpha, const Operation& opA, const dns::RiMatrix& srcA, const Operation& opB, const dns::RiMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::RdMatrix mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::RfMatrix mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::CdMatrix mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::CfMatrix mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const Operation& opB, const dns::CfMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

