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
pMat::pMat()
{
	defaults();
}
/*-------------------------------------------------*/
pMat::pMat(uint_t size)
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
void pMat::defaults()
{
	setSize  (0);
	setValues(nullptr);
	setOwner (false);
}
/*-------------------------------------------------*/
void pMat::creator(uint_t size, uint_t *values, bool owner)
{
	dns_consistency_check(prop_t::GENERAL, size, 1, values, size);

	setSize  (size);
	setValues(values);
	setOwner (owner);
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
void pMat::setSize  (uint_t  size  ) { m_size   = size  ; }
void pMat::setValues(uint_t *values) { m_values = values; }
void pMat::setOwner (bool    owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
uint_t        pMat::size  () const { return m_size  ; }
uint_t*       pMat::values()       { return m_values; }
const uint_t* pMat::values() const { return m_values; }
bool          pMat::owner () const { return m_owner ; }
/*-------------------------------------------------*/
bool pMat::empty() const
{
  if(size() && values())
    return false;

  return true;
}
/*-------------------------------------------------*/
void pMat::clear()
{
	if(owner()) {
		i_free(values());
	} // owner  

	defaults();
}
/*-------------------------------------------------*/
void pMat::unbind()
{
	setOwner(false);
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

	std::cout << "  size................. " <<         size  () << "\n";
	std::cout << "  values............... " <<         values() << "\n";
	std::cout << "  owner................ " << bool2yn(owner ()) << "\n";

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
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/
