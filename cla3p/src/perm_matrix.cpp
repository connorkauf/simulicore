// this file inc
#include "perm_matrix.hpp"

// system
#include <iostream>
#include <cstring>
#include <sstream>

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
PermMatrix::PermMatrix(uint_t n)
	:
		UniversalConstructor()
{
	blankCreator(n);
}
/*-------------------------------------------------*/
PermMatrix::~PermMatrix()
{
	clear();
}
/*-------------------------------------------------*/
PermMatrix::PermMatrix(PermMatrix&& other)
	:
		UniversalConstructor()
{
	*this = other.move();
}
/*-------------------------------------------------*/
PermMatrix& PermMatrix::operator=(PermMatrix&& other)
{
	*this = other.move();
	return *this;
}
/*-------------------------------------------------*/
#undef UniversalConstructor
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
void PermMatrix::defaults()
{
	UniversalMetaData::defaults();

	setValues(nullptr);
}
/*-------------------------------------------------*/
void PermMatrix::creator(uint_t n, uint_t *vals, bool owner)
{
	uint_t rsize = n;
	uint_t csize = 1;

	dns_consistency_check(prop_t::GENERAL, rsize, csize, vals, rsize);

	// meta data
	setAllMeta(rsize, csize, owner);

	// additional
	setValues(vals);
}
/*-------------------------------------------------*/
void PermMatrix::blankCreator(uint_t n)
{
	clear();
	uint_t *p = static_cast<uint_t*>(i_malloc(n, sizeof(uint_t)));
	creator(n, p, true);
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::init(uint_t n)
{
	PermMatrix ret;
	ret.blankCreator(n);
	return ret.move();
}
/*-------------------------------------------------*/
void PermMatrix::randomCreator(uint_t n)
{
	blankCreator(n);
	fill_random_perm(this->size(), this->values());
}
/*-------------------------------------------------*/
PermMatrix PermMatrix::random(uint_t n)
{
	PermMatrix ret;
	ret.randomCreator(n);
	return ret.move();
}
/*-------------------------------------------------*/
void PermMatrix::setValues(uint_t *vals) { m_values = vals; }
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
std::string PermMatrix::info(const std::string& msg) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object type.......... " <<  objTypeName() << "\n";
	ss << "  Datatype............. " << dataTypeName() << "\n";
	ss << "  Precision............ " << precTypeName() << "\n";

	ss << "  Size................. " <<         size  ()  << "\n";
	ss << "  Values............... " <<         values()  << "\n";
	ss << "  Owner................ " << bool2yn(owner ()) << "\n";

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
std::string PermMatrix::printToString() const
{
	std::string ret;

	char tmp[64];
	nint_t nd = inumlen(size());
	for(uint_t i = 0; i < size(); i++) {
		std::sprintf(tmp, "%*" _UFMT_ " | %*" _UFMT_ "\n", nd, i, nd, (*this)(i));
		ret.append(tmp);
	} // i

	return ret;
}
/*-------------------------------------------------*/
void PermMatrix::print() const
{
	std::cout << printToString();
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
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::PermMatrix& mat)
{
	os << mat.printToString();
	return os;
}
/*-------------------------------------------------*/
