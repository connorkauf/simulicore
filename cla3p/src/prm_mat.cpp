// this file inc
#include "prm_mat.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"
#include "error_internal.hpp"
#include "imalloc.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/
pMat::pMat()
{
	defaults();
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
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/
