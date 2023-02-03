// this file inc
#include "prm_mat.hpp"

// system
#include <iostream>
#include <cstring>

// 3rd

// cla3p
#include "error.hpp"
#include "error_internal.hpp"
#include "imalloc.hpp"
#include "utils.hpp"

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
	blank_creator(size);
}
/*-------------------------------------------------*/
pMat::~pMat()
{
	clear();
}
/*-------------------------------------------------*/
pMat::pMat(pMat&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.size(), src.values(), src.owner());
	} // !empty

	src.unbind();
	src.clear();
}
/*-------------------------------------------------*/
pMat& pMat::operator=(pMat&& src)
{
	clear();

	if(!src.empty()) {
		creator(src.size(), src.values(), src.owner());
	} // !empty

	src.unbind();
	src.clear();

	return *this;
}
/*-------------------------------------------------*/
void pMat::defaults()
{
	set_size  (0);
	set_values(nullptr);
	set_owner (false);
}
/*-------------------------------------------------*/
void pMat::creator(uint_t size, uint_t *values, bool owner)
{
	clear();

	if(!size) return; // policy is on zero dimensions, return empty object

	if(!values)
		throw NoConsistency(msg_invald_pointer());

	set_size  (size);
	set_values(values);
	set_owner (owner);
}
/*-------------------------------------------------*/
void pMat::blank_creator(uint_t size)
{
	uint_t *p = static_cast<uint_t*>(i_malloc(size, sizeof(uint_t)));
	creator(size, p, true);
}
/*-------------------------------------------------*/
pMat pMat::init(uint_t size)
{
	pMat ret;
	ret.blank_creator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void pMat::random_creator(uint_t size)
{
	uint_t *p = static_cast<uint_t*>(i_malloc(size, sizeof(uint_t)));
	fill_random_perm(size, p);
	creator(size, p, true);
}
/*-------------------------------------------------*/
pMat pMat::random(uint_t size)
{
	pMat ret;
	ret.random_creator(size);
	return ret.move();
}
/*-------------------------------------------------*/
void pMat::set_size  (uint_t  size  ) { m_size   = size  ; }
void pMat::set_values(uint_t *values) { m_values = values; }
void pMat::set_owner (bool    owner ) { m_owner  = owner ; }
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
	set_owner(false);
}
/*-------------------------------------------------*/
pMat pMat::copy() const
{
	pMat ret;

	if(!empty()) {
		ret.blank_creator(size());
		std::memcpy(ret.values(), values(), size() * sizeof(uint_t));
	} // !empty

	return ret.move();
}
/*-------------------------------------------------*/
pMat pMat::move()
{
	pMat ret;

	if(!empty()) {
		ret.creator(size(), values(), owner());
	} // !empty
		//
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
		std::printf("%*llu | %*llu\n", nd, i, nd, (*this)(i));
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
