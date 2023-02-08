// this file inc
#include "prm_mat.hpp"

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
namespace prm {
/*-------------------------------------------------*/
#if defined (CLA3P_I64)
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::UINT, PrecisionType::DOUBLE)
#else
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_VECTOR, DataType::UINT, PrecisionType::SINGLE)
#endif
/*-------------------------------------------------*/
pMat::pMat()
	:
		UniversalConstructor()
{
	defaults();
}
/*-------------------------------------------------*/
pMat::pMat(uint_t size)
	:
		UniversalConstructor()
{
	blankCreator(size);
}
/*-------------------------------------------------*/
pMat::~pMat()
{
	clear();
}
/*-------------------------------------------------*/
pMat::pMat(pMat&& src)
	:
		UniversalConstructor()
{
	*this = src.move();
}
/*-------------------------------------------------*/
pMat& pMat::operator=(pMat&& src)
{
	*this = src.move();
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
void pMat::defaults()
{
	UniversalMetaData::defaults();

	setValues(nullptr);
}
/*-------------------------------------------------*/
void pMat::creator(uint_t size, uint_t *values, bool owner)
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
void pMat::blankCreator(uint_t size)
{
	clear();
	uint_t *p = static_cast<uint_t*>(i_malloc(size, sizeof(uint_t)));
	creator(size, p, true);
}
/*-------------------------------------------------*/
pMat pMat::init(uint_t size)
{
	pMat ret;
	ret.blankCreator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void pMat::randomCreator(uint_t size)
{
	blankCreator(size);
	fill_random_perm(this->size(), this->values());
}
/*-------------------------------------------------*/
pMat pMat::random(uint_t size)
{
	pMat ret;
	ret.randomCreator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void pMat::setValues(uint_t *values) { m_values = values; }
/*-------------------------------------------------*/
uint_t pMat::size() const { return rsize(); }
/*-------------------------------------------------*/
uint_t*       pMat::values()       { return m_values; }
const uint_t* pMat::values() const { return m_values; }
/*-------------------------------------------------*/
void pMat::clear()
{
	if(owner()) {
		i_free(values());
	} // owner  

	defaults();
}
/*-------------------------------------------------*/
pMat pMat::copy() const
{
	pMat ret;
	ret.blankCreator(size());
	std::memcpy(ret.values(), values(), size() * sizeof(uint_t));
	return ret.move();
}
/*-------------------------------------------------*/
pMat pMat::move()
{
	pMat ret;
	ret.creator(size(), values(), owner());
	unbind();
	clear();
	return ret;
}
/*-------------------------------------------------*/
void pMat::info(const std::string& msg) const
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
void pMat::print() const
{
	nint_t nd = inumlen(size());
	for(uint_t i = 0; i < size(); i++) {
		std::printf("%*" _UFMT_ " | %*" _UFMT_ "\n", nd, i, nd, (*this)(i));
	} // i
}
/*-------------------------------------------------*/
uint_t& pMat::operator()(uint_t i)
{
	if(i >= size()) {
		throw OutOfBounds(out_of_bounds_message(size(),i));
	} // out-of-bounds

  return values()[i];
}
/*-------------------------------------------------*/
const uint_t& pMat::operator()(uint_t i) const
{
	if(i >= size()) {
		throw OutOfBounds(out_of_bounds_message(size(),i));
	} // out-of-bounds

  return values()[i];
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/
