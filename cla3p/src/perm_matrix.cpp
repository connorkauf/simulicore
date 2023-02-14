// this file inc
#include "perm_matrix.hpp"

// system
#include <iostream>
#include <cstring>

// 3rd

// cla3p
#include "checks/all_checks.hpp"
#include "support/error.hpp"
#include "support/error_internal.hpp"
#include "support/imalloc.hpp"
#include "support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
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
	defaults();
}
/*-------------------------------------------------*/
PermMatrix::PermMatrix(uint_t size)
	:
		UniversalConstructor()
{
	blankCreator(size);
}
/*-------------------------------------------------*/
PermMatrix::~PermMatrix()
{
	clear();
}
/*-------------------------------------------------*/
PermMatrix::PermMatrix(PermMatrix&& src)
	:
		UniversalConstructor()
{
	*this = src.move();
}
/*-------------------------------------------------*/
PermMatrix& PermMatrix::operator=(PermMatrix&& src)
{
	*this = src.move();
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
void PermMatrix::defaults()
{
	UniversalMetaData::defaults();

	setValues(nullptr);
}
/*-------------------------------------------------*/
void PermMatrix::creator(uint_t size, uint_t *values, bool owner)
{
	uint_t rsize = size;
	uint_t csize = 1;

	dns_consistency_check(prop_t::GENERAL, rsize, csize, values, size);

	// meta data
	setAllMeta(rsize, csize, owner);

	// additional
	setValues(values);
}
/*-------------------------------------------------*/
void PermMatrix::blankCreator(uint_t size)
{
	clear();
	uint_t *p = static_cast<uint_t*>(i_malloc(size, sizeof(uint_t)));
	creator(size, p, true);
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::init(uint_t size)
{
	PermMatrix ret;
	ret.blankCreator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void PermMatrix::randomCreator(uint_t size)
{
	blankCreator(size);
	fill_random_perm(this->size(), this->values());
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::random(uint_t size)
{
	PermMatrix ret;
	ret.randomCreator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void PermMatrix::setValues(uint_t *values) { m_values = values; }
/*-------------------------------------------------*/
uint_t PermMatrix::size() const { return rsize(); }
/*-------------------------------------------------*/
uint_t*       PermMatrix::values()       { return m_values; }
const uint_t* PermMatrix::values() const { return m_values; }
/*-------------------------------------------------*/
void PermMatrix::clear()
{
	if(owner()) {
		i_free(values());
	} // owner  

	defaults();
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::copy() const
{
	PermMatrix ret;
	ret.blankCreator(size());
	std::memcpy(ret.values(), values(), size() * sizeof(uint_t));
	return ret.move();
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::move()
{
	PermMatrix ret;
	ret.creator(size(), values(), owner());
	unbind();
	clear();
	return ret;
}
/*-------------------------------------------------*/
void PermMatrix::info(const std::string& msg) const
{
  std::string top;
  std::string bottom;
  fill_info_margins(msg, top, bottom);

  std::cout << top << "\n";

	std::cout << "  Object type.......... " <<  objTypeName() << "\n";
  std::cout << "  Datatype............. " << dataTypeName() << "\n";
  std::cout << "  Precision............ " << precTypeName() << "\n";

	std::cout << "  Size................. " <<         size  ()  << "\n";
	std::cout << "  Values............... " <<         values()  << "\n";
	std::cout << "  Owner................ " << bool2yn(owner ()) << "\n";

  std::cout << bottom << "\n";
}
/*-------------------------------------------------*/
void PermMatrix::print() const
{
	nint_t nd = inumlen(size());
	for(uint_t i = 0; i < size(); i++) {
		std::printf("%*" _UFMT_ " | %*" _UFMT_ "\n", nd, i, nd, (*this)(i));
	} // i
}
/*-------------------------------------------------*/
uint_t& PermMatrix::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(out_of_bounds_message(size(),i));
	} // out-of-bounds

  return values()[i];
}
/*-------------------------------------------------*/
const uint_t& PermMatrix::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(out_of_bounds_message(size(),i));
	} // out-of-bounds

  return values()[i];
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
