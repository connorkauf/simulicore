// this file inc
#include "dns_xxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../dense2.hpp"
#include "../bulk/dns.hpp"
#include "../bulk/dns_io.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../checks/all_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define XxMatrixTmpl XxMatrix<T_Scalar,T_RScalar,T_ReturnType>
#define XxMatrixTlst template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix()
{
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: XxObject<T_Scalar,T_RScalar,T_ReturnType>(nr, nc, nr, pr)
{
}
/*-------------------------------------------------*/
XxMatrixTlst
XxMatrixTmpl::~XxMatrix()
{
}
/*-------------------------------------------------*/
XxMatrixTlst
T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j)
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,j);
}
/*-------------------------------------------------*/
XxMatrixTlst
const T_Scalar& XxMatrixTmpl::operator()(uint_t i, uint_t j) const
{
	if(i >= nrows() || j >= ncols()) {
		throw OutOfBounds(msg::out_of_bounds(nrows(),ncols(),i,j));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,j);
}
/*-------------------------------------------------*/
XxMatrixTlst
void XxMatrixTmpl::operator=(T_Scalar val)
{
	Array2D<T_Scalar>::fill(val);
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::nrows() const
{
	return Array2D<T_Scalar>::rsize();
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::ncols() const
{
	return Array2D<T_Scalar>::csize();
}
/*-------------------------------------------------*/
XxMatrixTlst
uint_t XxMatrixTmpl::ld() const
{
	return Array2D<T_Scalar>::lsize();
}
/*-------------------------------------------------*/
XxMatrixTlst
const Property& XxMatrixTmpl::prop() const
{
	return Array2D<T_Scalar>::property();
}
/*-------------------------------------------------*/
XxMatrixTlst
std::string XxMatrixTmpl::info(const std::string& msg) const
{ 
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Number of rows....... " << nrows()  << "\n";
	ss << "  Number of columns.... " << ncols()  << "\n";
	ss << "  Leading dimension.... " << ld()  << "\n";
	ss << "  Values............... " << Array2D<T_Scalar>::values() << "\n";
	ss << "  Property............. " << prop()  << "\n";
	ss << "  Owner................ " << bool2yn(Array2D<T_Scalar>::owner ()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
XxMatrixTlst
T_RScalar XxMatrixTmpl::normMax() const
{ 
	return bulk::dns::norm_max(
			prop().type(), 
			prop().uplo(), 
			nrows(), 
			ncols(),
			Array2D<T_Scalar>::values(), 
			ld());
}
/*-------------------------------------------------*/
XxMatrixTlst
T_RScalar XxMatrixTmpl::normFro() const
{ 
	return bulk::dns::norm_fro(
			prop().type(), 
			prop().uplo(), 
			nrows(), 
			ncols(),
			Array2D<T_Scalar>::values(), 
			ld());
}
/*-------------------------------------------------*/
#if 0
XxVectorTlst
T_ReturnType XxVectorTmpl::permute(const PiMatrix& P) const
{
	T_ReturnType ret;
	Array2D<T_Scalar>::permuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::ipermute(const PiMatrix& P) 
{ 
	Array2D<T_Scalar>::permuteIpLeft(P);
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
	block_op_consistency_check(
			defaultProperty(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			ibgn, 0, ni, 1);

	T_Scalar *p_vi = bulk::dns::ptrmv(Array2D<T_Scalar>::lsize(),Array2D<T_Scalar>::values(),ibgn,0);

	T_ReturnType ret = wrap(ni, p_vi, false);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
Guard<T_ReturnType> XxVectorTmpl::rblock(uint_t ibgn, uint_t ni) const
{
	block_op_consistency_check(
			defaultProperty(), 
			Array2D<T_Scalar>::rsize(), 
			Array2D<T_Scalar>::csize(), 
			ibgn, 0, ni, 1);

	const T_Scalar *p_vi = bulk::dns::ptrmv(Array2D<T_Scalar>::lsize(),Array2D<T_Scalar>::values(),ibgn,0);
	Guard<T_ReturnType> ret = wrap(ni, p_vi);
	return ret;
}
/*-------------------------------------------------*/
XxVectorTlst
void XxVectorTmpl::setBlock(uint_t ibgn, const XxVectorTmpl& src)
{
	XxVectorTmpl tmp = rblock(ibgn, src.rsize());
	src.copyToAllocated(tmp);
}
#endif // 0
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
XxMatrixTlst
T_ReturnType XxMatrixTmpl::init(uint_t nr, uint_t nc, const Property& pr)
{
	T_ReturnType ret(nr, nc, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_ReturnType XxMatrixTmpl::random(uint_t nr, uint_t nc, const Property& pr)
{
	T_ReturnType ret = init(nr, nc, pr);
	bulk::dns::rand(ret.prop().uplo(), ret.nrows(), ret.ncols(), ret.values(), ret.ld());
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
T_ReturnType XxMatrixTmpl::wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr)
{
	T_ReturnType ret;
	ret.wrapper(nr, nc, ldv, vals, bind, pr);
	return ret;
}
/*-------------------------------------------------*/
XxMatrixTlst
Guard<T_ReturnType> XxMatrixTmpl::wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr)
{
	T_ReturnType tmp = wrap(nr, nc, const_cast<T_Scalar*>(vals), ldv, false, pr);
	Guard<T_ReturnType> ret = tmp;
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef XxMatrixTmpl
#undef XxMatrixTlst
/*-------------------------------------------------*/
template class XxMatrix<real_t,real_t,RdMatrix2>;
template class XxMatrix<real4_t,real4_t,RfMatrix2>;
template class XxMatrix<complex_t,real_t,CdMatrix2>;
template class XxMatrix<complex8_t,real4_t,CfMatrix2>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
