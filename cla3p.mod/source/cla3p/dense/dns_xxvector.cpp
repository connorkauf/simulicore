// this file inc
#include "cla3p/dense/dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/perms.hpp"
#include "cla3p/bulk/dns.hpp"
#include "cla3p/bulk/dns_math.hpp"
#include "cla3p/support/error.hpp"
#include "cla3p/support/error_internal.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/checks/all_checks.hpp"
#include "cla3p/linsol/dns_auto_lsolver.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XxVector<T_Scalar,T_Vector>
#define XxVectorTlst template <typename T_Scalar, typename T_Vector>
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector(uint_t n)
	: XxObject<T_Scalar,T_Vector>(n, 1, n, defaultProperty())
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
T_Scalar& XxVectorTmpl::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
XxVectorTlst
const T_Scalar& XxVectorTmpl::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::operator=(T_Scalar val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::operator/(const XxMatrix<T_Scalar,T_Matrix>& other) const
{
	T_Vector ret = this->copy();
	ret /= other;
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
XxVector<T_Scalar,T_Vector>& XxVectorTmpl::operator/=(const XxMatrix<T_Scalar,T_Matrix>& other)
{
	T_Vector rhs = this->rcopy();
	default_linear_solver<T_Matrix,T_Vector>(other.rcopy().get(), rhs);
	return *this;
}
/*-------------------------------------------------*/
XxVectorTlst
uint_t XxVectorTmpl::size() const
{
	return this->rsize();
}
/*-------------------------------------------------*/
XxVectorTlst
std::string XxVectorTmpl::info(const std::string& msg) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << BasicTypeTraits<T_Vector>::type_name() << "\n";
	ss << "  Datatype............. " << BasicTypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << BasicTypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Size................. " << size() << "\n";
	ss << "  Values............... " << this->values() << "\n";
	ss << "  Owner................ " << bool2yn(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(size(), this->values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::permuteLeft(const PiMatrix& P) const
{
	T_Vector ret;
	this->gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::ipermuteLeft(const PiMatrix& P) 
{ 
	this->gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::block(uint_t ibgn, uint_t ni) const
{
	return rblock(ibgn,ni).get().copy();
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::rblock(uint_t ibgn, uint_t ni)
{
	return this->getBlockReference(ibgn, 0, ni, 1);
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
{
	return this->getBlockReference(ibgn, 0, ni, 1);
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::setBlock(uint_t ibgn, const XxVectorTmpl& src)
{
	this->setBlockCopy(src, ibgn, 0);
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_Matrix XxVectorTmpl::matrix() const
{ 
	return rmatrix().get().copy();
}
/*-------------------------------------------------*/
XxVectorTlst
typename XxVectorTmpl::T_Matrix XxVectorTmpl::rmatrix()
{
	return T_Matrix::wrap(size(), 1, this->values(), this->lsize(), false);
};
/*-------------------------------------------------*/
XxVectorTlst
Guard<typename XxVectorTmpl::T_Matrix> XxVectorTmpl::rmatrix() const 
{ 
	return T_Matrix::wrap(size(), 1, this->values(), this->lsize());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::init(uint_t n)
{
	T_Vector ret(n);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::random(uint_t n)
{
	T_Vector ret(n);
	bulk::dns::rand(uplo_t::F, ret.rsize(), ret.csize(), ret.values(), ret.lsize());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_Vector XxVectorTmpl::wrap(uint_t n, T_Scalar *vals, bool bind)
{
	T_Vector ret;
	ret.wrapper(n, 1, n, vals, bind, defaultProperty());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_Vector> XxVectorTmpl::wrap(uint_t n, const T_Scalar *vals)
{
	Guard<T_Vector> ret = wrap(n, const_cast<T_Scalar*>(vals), false);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::updateSelfWithScaledMatVec(T_Scalar alpha, const Operation& opA, const XxMatrix<T_Scalar,T_Matrix>& otherA, const XxVectorTmpl& otherX)
{
	matvec_mult_check(opA, 
			otherA.prop(), otherA.nrows(), otherA.ncols(), 
			otherX.property(), otherX.rsize(), otherX.csize(), 
			this->property(), 
			this->rsize(), 
			this->csize());

	if(otherA.prop().isGeneral()) {

		bulk::dns::gem_x_vec(opA.type(), otherA.nrows(), otherA.ncols(), alpha, otherA.values(), otherA.ld(), otherX.values(), 1, this->values());

	} else if(otherA.prop().isSymmetric()) {

		bulk::dns::sym_x_vec(otherA.prop().uplo(), otherA.ncols(), alpha, otherA.values(), otherA.ld(), otherX.values(), 1, this->values());

	} else if(otherA.prop().isHermitian()) {

		bulk::dns::hem_x_vec(otherA.prop().uplo(), otherA.ncols(), alpha, otherA.values(), otherA.ld(), otherX.values(), 1, this->values());

	} else if(otherA.prop().isTriangular()) {

		T_Vector tmp(size());
		bulk::dns::trm_x_vec(otherA.prop().uplo(), opA.type(), otherA.nrows(), otherA.ncols(), alpha, otherA.values(), otherA.ld(), otherX.values(), tmp.values());
		this->updateSelfWithScaledOther(1, tmp);

	} else {

		throw Exception();

	} // property 
}
/*-------------------------------------------------*/
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
template class XxVector<real_t,RdVector>;
template class XxVector<real4_t,RfVector>;
template class XxVector<complex_t,CdVector>;
template class XxVector<complex8_t,CfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
