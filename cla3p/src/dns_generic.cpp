// this file inc
#include "dns_generic.hpp"

// system

// 3rd

// cla3p
#include "error.hpp"
#include "utils.hpp"
#include "imalloc.hpp"
#include "bulk/dns.hpp"
#include "bulk/dns_io.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::GenericObject()
{
	defaults();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::GenericObject(GenericObject<T>&& src)
{
	clear();
	creator(src.nrows(), src.ncols(), src.values(), src.ld(), src.prop(), src.owner());
	src.unbind();
	src.clear();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>& GenericObject<T>::operator=(GenericObject<T>&& src)
{
	clear();
	creator(src.nrows(), src.ncols(), src.values(), src.ld(), src.prop(), src.owner());
	src.unbind();
	src.clear();

	return *this;
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::defaults()
{
	set_nrows (0);
	set_ncols (0);
	set_ld    (0);
	set_values(nullptr);
	set_prop  (prop_t::NONE);
	set_owner (false);
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::creator(uint_t nrows, uint_t ncols, T *values, uint_t ld, const Property& prop, bool owner)
{
	set_nrows (nrows );
	set_ncols (ncols );
	set_values(values);
	set_ld    (ld    );
	set_prop  (prop  );
	set_owner (owner );
}
/*-------------------------------------------------*/
template<class T> void GenericObject<T>::set_nrows (uint_t          nrows ) { m_nrows  = nrows ; }
template<class T> void GenericObject<T>::set_ncols (uint_t          ncols ) { m_ncols  = ncols ; }
template<class T> void GenericObject<T>::set_ld    (uint_t          ld    ) { m_ld     = ld    ; }
template<class T> void GenericObject<T>::set_values(T*              values) { m_values = values; }
template<class T> void GenericObject<T>::set_prop  (const Property& prop  ) { m_prop   = prop  ; }
template<class T> void GenericObject<T>::set_owner (bool            owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template<class T> uint_t          GenericObject<T>::nrows () const { return m_nrows ; }
template<class T> uint_t          GenericObject<T>::ncols () const { return m_ncols ; }
template<class T> uint_t          GenericObject<T>::ld    () const { return m_ld    ; }
template<class T> T*              GenericObject<T>::values()       { return m_values; }
template<class T> const T*        GenericObject<T>::values() const { return m_values; }
template<class T> const Property& GenericObject<T>::prop  () const { return m_prop  ; }
template<class T> bool            GenericObject<T>::owner () const { return m_owner ; }
/*-------------------------------------------------*/
template<class T>
bool GenericObject<T>::empty() const
{
	if(nrows() && ncols() && values()) 
		return false;

	return true;
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::unbind()
{
	set_owner(false);
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::copy_to(GenericObject<T>& trg) const
{
	T *vnew = bulk::alloc<T>(nrows(), ncols(), nrows());
	bulk::copy(prop().type(), nrows(), ncols(), values(), ld(), vnew, nrows());
	trg.creator(nrows(), ncols(), vnew, nrows(), prop(), true);
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::move_to(GenericObject<T>& trg)
{
	trg.creator(nrows(), ncols(), values(), ld(), prop(), owner());
	unbind();
	clear();
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::clone_to(GenericObject<T>& trg)
{
	trg.creator(nrows(), ncols(), values(), ld(), prop(), false);
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::info(
		const std::string& msg, 
		const std::string& otype, 
		const std::string& dtype, 
		const std::string& dprec) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::cout << top << "\n";

	std::cout << "  Object type.......... " << otype << "\n";
	std::cout << "  Datatype............. " << dtype << "\n";
	std::cout << "  Precision............ " << dprec << "\n";

	bool is_vector = (otype == "Vector");
	bool is_matrix = (otype == "Matrix");

	if(is_vector) {
		std::cout << "  size................. " <<         nrows () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // vector

	if(is_matrix) {
		std::cout << "  nrows................ " <<         nrows () << "\n";
		std::cout << "  ncols................ " <<         ncols () << "\n";
		std::cout << "  ld................... " <<         ld    () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  prop................. " <<         prop  () << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // matrix

	std::cout << bottom << "\n";
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::print(uint_t nsd) const
{
	bulk::print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template<class T>
T& GenericObject<T>::operator()(uint_t i, uint_t j)
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template<class T>
const T& GenericObject<T>::operator()(uint_t i, uint_t j) const
{
	return dns::bulk::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template <class T>
void GenericObject<T>::create_empty(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	creator(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <class T>
void GenericObject<T>::create_zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::alloc<T>(nrows, ncols, ld, true);
	creator(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <class T>
void GenericObject<T>::create_random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	bulk::rand(prop.type(), nrows, ncols, values, ld);
	creator(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <class T>
void GenericObject<T>::create_mapped(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld)
{
	creator(nrows, ncols, values, ld, prop, false);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class GenericObject<real_t>;
template class GenericObject<real4_t>;
template class GenericObject<complex_t>;
template class GenericObject<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
