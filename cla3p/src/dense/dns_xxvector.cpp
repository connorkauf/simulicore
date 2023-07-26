// this file inc
#include "dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../bulk/dns.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxVectorTmpl XxVector<T_Scalar,T_RScalar,T_ReturnType>
#define XxVectorTlst template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::XxVector(uint_t n)
	: XxObject<T_Scalar,T_RScalar,T_ReturnType>(n, 1, n, defaultProperty())
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

	ss << "  Size................. " << size() << "\n";
	ss << "  Values............... " << this->values() << "\n";
	ss << "  Owner................ " << bool2yn(this->owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxVectorTlst
T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(size(), this->values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::permute(const PiMatrix& P) const
{
	T_ReturnType ret;
	this->gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::ipermute(const PiMatrix& P) 
{ 
	this->gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::block(uint_t ibgn, uint_t ni) const
{
	return rblock(ibgn,ni).get().copy();
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::rblock(uint_t ibgn, uint_t ni)
{
	return this->getBlockReference(ibgn, 0, ni, 1);
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_ReturnType> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
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
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::init(uint_t n)
{
	T_ReturnType ret(n);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::random(uint_t n)
{
	T_ReturnType ret(n);
	bulk::dns::rand(uplo_t::F, ret.rsize(), ret.csize(), ret.values(), ret.lsize());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::wrap(uint_t n, T_Scalar *vals, bool bind)
{
	T_ReturnType ret;
	ret.wrapper(n, 1, n, vals, bind, defaultProperty());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_ReturnType> XxVectorTmpl::wrap(uint_t n, const T_Scalar *vals)
{
	T_ReturnType tmp = wrap(n, const_cast<T_Scalar*>(vals), false);
	Guard<T_ReturnType> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxVectorTmpl
#undef XxVectorTlst
/*-------------------------------------------------*/
template class XxVector<real_t,real_t,RdVector>;
template class XxVector<real4_t,real4_t,RfVector>;
template class XxVector<complex_t,real_t,CdVector>;
template class XxVector<complex8_t,real4_t,CfVector>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
