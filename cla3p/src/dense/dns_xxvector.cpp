// this file inc
#include "dns_xxvector.hpp"

// system

// 3rd

// cla3p
#include "../dense2.hpp"
#include "../bulk/dns.hpp"
#include "../support/utils.hpp"
#include "../checks/all_checks.hpp"

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
{
	Array2D<T_Scalar>::creator(n, 1, n);
}
/*-------------------------------------------------*/
XxVectorTlst
XxVectorTmpl::~XxVector()
{
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::operator=(T_Scalar val)
{
	Array2D<T_Scalar>::fill(val);
}
/*-------------------------------------------------*/
XxVectorTlst
uint_t XxVectorTmpl::size() const
{
	return Array2D<T_Scalar>::rsize();
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
	ss << "  Values............... " << Array2D<T_Scalar>::values() << "\n";
	ss << "  Owner................ " << bool2yn(Array2D<T_Scalar>::owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::copy() const
{
	T_ReturnType ret;
	Array2D<T_Scalar>::copyTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::rcopy()
{
	T_ReturnType ret;
	Array2D<T_Scalar>::copyToShallow(ret);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_ReturnType> XxVectorTmpl::rcopy() const
{
	T_ReturnType tmp;
	const_cast<XxVectorTmpl&>(*this).copyToShallow(tmp);
	Guard<T_ReturnType> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::move()
{
	T_ReturnType ret;
	Array2D<T_Scalar>::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::scale(T_Scalar val)
{
	bulk::dns::scale(uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize(), val);
}
/*-------------------------------------------------*/
XxVectorTlst
T_RScalar XxVectorTmpl::normOne() const
{ 
	return bulk::dns::norm_one(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxVectorTlst
T_RScalar XxVectorTmpl::normInf() const
{ 
	return bulk::dns::norm_inf(prop_t::GENERAL, uplo_t::F, 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			Array2D<T_Scalar>::values(), 
			Array2D<T_Scalar>::lsize());
}
/*-------------------------------------------------*/
XxVectorTlst
T_RScalar XxVectorTmpl::normEuc() const
{ 
	return bulk::dns::norm_euc(
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::values());
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::block(uint_t ibgn, uint_t ni) const
{
	block_op_consistency_check(
			defaultProperty(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			ibgn, 0, ni, 1);
	
	T_ReturnType ret;
	ret.creator(ni, 1, ni);

	bulk::dns::copy(uplo_t::F, ni, 1, 
			bulk::dns::ptrmv(Array2D<T_Scalar>::lsize(),Array2D<T_Scalar>::values(),ibgn,0), Array2D<T_Scalar>::lsize(), 
			ret.values(), ret.lsize());

	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::rblock(uint_t ibgn, uint_t ni)
{
	block_op_consistency_check(
			defaultProperty(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			ibgn, 0, ni, 1);

	T_ReturnType ret = wrap(ni, Array2D<T_Scalar>::values() + ibgn, false);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_ReturnType> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
{
	Guard<T_ReturnType> ret = wrap(ni, Array2D<T_Scalar>::values() + ibgn);
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::init(uint_t n)
{
	T_ReturnType ret;
	ret.creator(n, 1, n);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::random(uint_t n)
{
	T_ReturnType ret = init(n);
	bulk::dns::rand(uplo_t::F, ret.rsize(), ret.csize(), ret.values(), ret.lsize());
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
T_ReturnType XxVectorTmpl::wrap(uint_t n, T_Scalar *vals, bool bind)
{
	T_ReturnType ret;
	ret.wrapper(n, 1, vals, n, bind);
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
template class XxVector<real_t,real_t,RdVector2>;
template class XxVector<real4_t,real4_t,RfVector2>;
template class XxVector<complex_t,real_t,CdVector2>;
template class XxVector<complex8_t,real4_t,CfVector2>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
