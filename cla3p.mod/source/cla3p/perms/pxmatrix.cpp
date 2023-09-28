// this file inc
#include "cla3p/perms/pxmatrix.hpp"

// system

// 3rd

// cla3p
#include "cla3p/support/error.hpp"
#include "cla3p/support/error_internal.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::PxMatrix(uint_t n)
	: Array2D<T_Int>(n, 1, n, defaultProperty())
{
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::~PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Int>
T_Int& PxMatrix<T_Int>::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Int>::operator()(i,0);
}
/*-------------------------------------------------*/
template <typename T_Int>
const T_Int& PxMatrix<T_Int>::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return Array2D<T_Int>::operator()(i,0);
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::operator*(const PxMatrix<T_Int>& P) const
{
	return P.permuteLeft(*this);
}
/*-------------------------------------------------*/
template <typename T_Int>
uint_t PxMatrix<T_Int>::size() const 
{ 
	return Array2D<T_Int>::rsize(); 
}
/*-------------------------------------------------*/
template <typename T_Int>
std::string PxMatrix<T_Int>::info(const std::string& msg) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object Type.......... " << BasicTypeTraits<PxMatrix<T_Int>>::type_name() << "\n";
	ss << "  Datatype............. " << BasicTypeTraits<T_Int>::type_name() << "\n";
	ss << "  Precision............ " << BasicTypeTraits<T_Int>::prec_name() << "\n";
	ss << "  Size................. " << size() << "\n";
	ss << "  Values............... " << Array2D<T_Int>::values() << "\n";
	ss << "  Owner................ " << bool2yn(Array2D<T_Int>::owner()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::copy() const
{
	PxMatrix<T_Int> ret;
  Array2D<T_Int>::copyTo(ret);
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::rcopy()
{
	PxMatrix<T_Int> ret;
  Array2D<T_Int>::copyToShallow(ret);
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
Guard<PxMatrix<T_Int>> PxMatrix<T_Int>::rcopy() const
{
	Guard<PxMatrix<T_Int>> ret = *this;
  return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::move()
{
	PxMatrix<T_Int> ret;
	Array2D<T_Int>::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::inverse() const
{
	PxMatrix<T_Int> ret(size());

	for(uint_t i = 0; i < size(); i++) {
		ret((*this)(i)) = i;
	} // i

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::permuteLeft(const PxMatrix<T_Int>& P) const
{
	PxMatrix<T_Int> ret;
	Array2D<T_Int>::gePermuteToLeft(ret, P);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
void PxMatrix<T_Int>::ipermuteLeft(const PxMatrix<T_Int>& P)
{
	Array2D<T_Int>::gePermuteIpLeft(P);
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::init(uint_t n)
{
	PxMatrix<T_Int> ret(n);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::identity(uint_t n)
{
	PxMatrix<T_Int> ret(n);
	fill_identity_perm(ret.size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::random(uint_t n)
{
	PxMatrix<T_Int> ret(n);
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
