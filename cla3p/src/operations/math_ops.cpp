// this file inc
#include "math_ops.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace ops {
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Object>
static void dns_update_tmpl(T_Scalar alpha, const T_Object& src, T_Object& trg)
{
	trg.updateWithScaledOther(alpha, src);
}
/*-------------------------------------------------*/
void update(real_t     alpha, const dns::RdVector& src, dns::RdVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real4_t    alpha, const dns::RfVector& src, dns::RfVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex_t  alpha, const dns::CdVector& src, dns::CdVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex8_t alpha, const dns::CfVector& src, dns::CfVector& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real_t     alpha, const dns::RdMatrix& src, dns::RdMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(real4_t    alpha, const dns::RfMatrix& src, dns::RfMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex_t  alpha, const dns::CdMatrix& src, dns::CdMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
void update(complex8_t alpha, const dns::CfMatrix& src, dns::CfMatrix& trg) { dns_update_tmpl(alpha, src, trg); }
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Object>
static T_Object dns_add_tmpl(T_Scalar alpha, const T_Object& srcA, T_Scalar beta, const T_Object& srcB)
{
	T_Object ret;
	ret.createFromScaledSum(alpha, srcA, beta, srcB);
	return ret;
}
/*-------------------------------------------------*/
dns::RdVector add(real_t     alpha, const dns::RdVector& srcA, real_t     beta, const dns::RdVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RfVector add(real4_t    alpha, const dns::RfVector& srcA, real4_t    beta, const dns::RfVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CdVector add(complex_t  alpha, const dns::CdVector& srcA, complex_t  beta, const dns::CdVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CfVector add(complex8_t alpha, const dns::CfVector& srcA, complex8_t beta, const dns::CfVector& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RdMatrix add(real_t     alpha, const dns::RdMatrix& srcA, real_t     beta, const dns::RdMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::RfMatrix add(real4_t    alpha, const dns::RfMatrix& srcA, real4_t    beta, const dns::RfMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CdMatrix add(complex_t  alpha, const dns::CdMatrix& srcA, complex_t  beta, const dns::CdMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
dns::CfMatrix add(complex8_t alpha, const dns::CfMatrix& srcA, complex8_t beta, const dns::CfMatrix& srcB) { return dns_add_tmpl(alpha, srcA, beta, srcB); }
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Matrix, typename T_Vector>
//static void dns_update_with_mv_tmpl(T_Scalar alpha, const Operation& opA, const T_Matrix& srcA, const T_Vector& srcX, T_Vector& trg)
static void dns_update_with_mv_tmpl(T_Scalar, const Operation&, const T_Matrix&, const T_Vector&, T_Vector&)
{
	//trg.updateSelfWithMatVec(alpha, opA, srcA, srcX); // FIXME: implement
}
/*-------------------------------------------------*/
void mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX, dns::RdVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX, dns::RfVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX, dns::CdVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX, dns::CfVector& trg) { dns_update_with_mv_tmpl(alpha, opA, srcA, srcX, trg); }
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Matrix, typename T_Vector>
static T_Vector dns_mv_tmpl(T_Scalar alpha, const Operation& opA, const T_Matrix& srcA, const T_Vector& srcX)
{
	T_Vector ret(opA.isTranspose() ? srcA.ncols() : srcA.nrows());
	ret = 0;
	mult(alpha, opA, srcA, srcX, ret);
	return ret;
}
/*-------------------------------------------------*/
dns::RdVector mult(real_t     alpha, const Operation& opA, const dns::RdMatrix& srcA, const dns::RdVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::RfVector mult(real4_t    alpha, const Operation& opA, const dns::RfMatrix& srcA, const dns::RfVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::CdVector mult(complex_t  alpha, const Operation& opA, const dns::CdMatrix& srcA, const dns::CdVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
dns::CfVector mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const dns::CfVector& srcX) { return dns_mv_tmpl(alpha, opA, srcA, srcX); }
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Matrix>
static void dns_update_with_gemm_tmpl(T_Scalar alpha, const Operation& opA, const T_Matrix& srcA, const Operation& opB, const T_Matrix& srcB, T_Matrix& trg)
{
	trg.updateSelfWithScaledMatMat(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
void mult(real_t alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB, dns::RdMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(real4_t alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB, dns::RfMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(complex_t alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB, dns::CdMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
void mult(complex8_t alpha, const Operation& opA, const dns::CfMatrix& srcA, const Operation& opB, const dns::CfMatrix& srcB, dns::CfMatrix& trg)
{
	dns_update_with_gemm_tmpl(alpha, opA, srcA, opB, srcB, trg);
}
/*-------------------------------------------------*/
template <typename T_Scalar, typename T_Matrix>
static T_Matrix dns_gemm_tmpl(T_Scalar alpha, const Operation& opA, const T_Matrix& srcA, const Operation& opB, const T_Matrix& srcB)
{
	T_Matrix ret(opA.isTranspose() ? srcA.ncols() : srcA.nrows(), opB.isTranspose() ? srcB.nrows() : srcB.ncols());
	ret = 0;
	mult(alpha, opA, srcA, opB, srcB, ret);
	return ret;
}
/*-------------------------------------------------*/
dns::RdMatrix mult(real_t alpha, const Operation& opA, const dns::RdMatrix& srcA, const Operation& opB, const dns::RdMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::RfMatrix mult(real4_t alpha, const Operation& opA, const dns::RfMatrix& srcA, const Operation& opB, const dns::RfMatrix& srcB)
{
	return dns_gemm_tmpl(alpha, opA, srcA, opB, srcB);
}
/*-------------------------------------------------*/
dns::CdMatrix mult(complex_t alpha, const Operation& opA, const dns::CdMatrix& srcA, const Operation& opB, const dns::CdMatrix& srcB)
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

