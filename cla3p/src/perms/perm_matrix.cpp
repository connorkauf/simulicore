// this file inc
#include "perm_matrix.hpp"

// system

// 3rd

// cla3p
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
using ThisDataType = uint_t;
using ThisObjectType = dns::GenericObject<ThisDataType,ThisDataType>;
/*-------------------------------------------------*/
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::UINT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::UINT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
PermMatrix::PermMatrix()
	:
		UniversalConstructor()
{
}
/*-------------------------------------------------*/
PermMatrix::PermMatrix(uint_t n)
	:
		UniversalConstructor(),
		ThisObjectType(prop_t::GENERAL, n, 1, n, false)
{
}
/*-------------------------------------------------*/
PermMatrix::~PermMatrix()
{
}
/*-------------------------------------------------*/
PermMatrix::PermMatrix(PermMatrix&& other)
	:
		UniversalConstructor(),
		ThisObjectType(std::move(other))
{
}
/*-------------------------------------------------*/
PermMatrix& PermMatrix::operator=(PermMatrix&& other)
{
	ThisObjectType::operator=(std::move(other));
	return *this;
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
uint_t PermMatrix::size() const { return rsize(); }
/*-------------------------------------------------*/
PermMatrix PermMatrix::copy() const
{
	PermMatrix ret;
  ThisObjectType::copyTo(ret);
  return ret.move();
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::move()
{
	PermMatrix ret;
	ThisObjectType::moveTo(ret);
	return ret;
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::inverse() const
{
	PermMatrix ret(size());
	for(uint_t i = 0; i < size(); i++) {
		ret((*this)(i)) = i;
	} // i
	return ret.move();
}
/*-------------------------------------------------*/
std::string PermMatrix::info(const std::string& msg) const
{
	return ThisObjectType::info(false, msg, objTypeName(), dataTypeName(), precTypeName());
}
/*-------------------------------------------------*/
ThisDataType& PermMatrix::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return ThisObjectType::operator()(i,0);
}
/*-------------------------------------------------*/
const ThisDataType& PermMatrix::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(msg::out_of_bounds(size(),i));
	} // out-of-bounds

	return ThisObjectType::operator()(i,0);
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::init(uint_t n)
{
	PermMatrix ret;
	ret.blankCreator(prop_t::GENERAL, n, 1, n);
	return ret.move();
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::random(uint_t n)
{
	PermMatrix ret;
	ret.blankCreator(prop_t::GENERAL, n, 1, n);
	fill_random_perm(ret.size(), ret.values());
	return ret.move();
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::PermMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
