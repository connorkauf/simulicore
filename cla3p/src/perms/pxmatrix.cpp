// this file inc
#include "pxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../checks/all_checks.hpp"
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar>::PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar>::PxMatrix(uint_t n)
	: Array2D<T_Scalar>(n, 1, n, defaultProperty())
{
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar>::~PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar& PxMatrix<T_Scalar>::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
const T_Scalar& PxMatrix<T_Scalar>::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Scalar>::operator()(i,0);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
uint_t PxMatrix<T_Scalar>::size() const 
{ 
	return Array2D<T_Scalar>::rsize(); 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
std::string PxMatrix<T_Scalar>::info(const std::string& msg) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << BasicTypeTraits<PxMatrix<T_Scalar>>::type_name() << "\n";
	ss << "  Datatype............. " << BasicTypeTraits<T_Scalar>::type_name() << "\n";
	ss << "  Precision............ " << BasicTypeTraits<T_Scalar>::prec_name() << "\n";
	ss << "  Size................. " << size() << "\n";
	ss << "  Values............... " << Array2D<T_Scalar>::values() << "\n";
	ss << "  Owner................ " << bool2yn(Array2D<T_Scalar>::owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::copy() const
{
	PxMatrix<T_Scalar> ret;
  Array2D<T_Scalar>::copyTo(ret);
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::rcopy()
{
	PxMatrix<T_Scalar> ret;
  Array2D<T_Scalar>::copyToShallow(ret);
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Guard<PxMatrix<T_Scalar>> PxMatrix<T_Scalar>::rcopy() const
{
	Guard<PxMatrix<T_Scalar>> ret = *this;
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::move()
{
	PxMatrix<T_Scalar> ret;
	Array2D<T_Scalar>::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::inverse() const
{
	PxMatrix<T_Scalar> ret(size());

	for(uint_t i = 0; i < size(); i++) {
		ret((*this)(i)) = i;
	} // i

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::permute(const PxMatrix<T_Scalar>& P) const
{
	PxMatrix<T_Scalar> ret;
	Array2D<T_Scalar>::gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void PxMatrix<T_Scalar>::ipermute(const PxMatrix<T_Scalar>& P)
{
	Array2D<T_Scalar>::gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::init(uint_t n)
{
	PxMatrix<T_Scalar> ret(n);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::identity(uint_t n)
{
	PxMatrix<T_Scalar> ret(n);
	fill_identity_perm(ret.size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
PxMatrix<T_Scalar> PxMatrix<T_Scalar>::random(uint_t n)
{
	PxMatrix<T_Scalar> ret(n);
	fill_random_perm(ret.size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class PxMatrix<int_t>;
/*-------------------------------------------------*/
template<> const std::string& BasicTypeTraits<PxMatrix<int_t>>::type_name() { return stringPermutationMatrix(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
