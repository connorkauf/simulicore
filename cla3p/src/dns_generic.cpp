// this file inc
#include "dns_generic.hpp"

// system

// 3rd

// cla3p
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
GenericObject<T>::GenericObject(uint_t nrows, uint_t ncols, T *values, uint_t ld, const Property& prop, bool owner)
{
	bulk::check(prop.type(), nrows, ncols, values, ld);

	set_nrows (nrows );
	set_ncols (ncols );
	set_ld    (ld    );
	set_values(values);
	set_prop  (prop  );
	set_owner (owner );
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>::GenericObject(GenericObject&& src)
{
	clear();

	set_nrows (src.nrows ());
	set_ncols (src.ncols ());
	set_ld    (src.ld    ());
	set_values(src.values());
	set_prop  (src.prop  ());
	set_owner (src.owner ());

	src.unbind();
	src.clear();
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T>& GenericObject<T>::operator=(GenericObject&& src)
{
	clear();

	set_nrows (src.nrows ());
	set_ncols (src.ncols ());
	set_ld    (src.ld    ());
	set_values(src.values());
	set_prop  (src.prop  ());
	set_owner (src.owner ());

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
GenericObject<T> GenericObject<T>::copy() const
{
	uint_t          m   = nrows ();
	uint_t          n   = ncols ();
	uint_t          ldv = ld    ();
	const T*        v   = values();
	const Property& p   = prop  ();

	T *vnew = bulk::alloc<T>(m, n, m);
	bulk::copy(p.type(), m, n, v, ldv, vnew, m);

	return GenericObject<T>(m, n, vnew, m, p, true);
}
/*-------------------------------------------------*/
template<class T>
GenericObject<T> GenericObject<T>::move()
{
	uint_t   m   = nrows ();
	uint_t   n   = ncols ();
	uint_t   ldv = ld    ();
	T*       v   = values();
	Property p   = prop  (); // copy this
	bool     own = owner ();

	unbind();
	clear();

	return GenericObject<T>(m, n, v, ldv, p, own);
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::info(const std::string& msg) const
{
	std::cout << "INFO:: " << msg << std::endl;

	std::cout << nrows () << std::endl;
	std::cout << ncols () << std::endl;
	std::cout << ld    () << std::endl;
	std::cout << values() << std::endl;
	std::cout << prop  () << std::endl;
	std::cout << owner () << std::endl << std::endl;
}
/*-------------------------------------------------*/
template<class T>
void GenericObject<T>::print(uint_t nsd) const
{
	bulk::print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <class T>
GenericObject<T> GenericObject<T>::init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	if(ld == defaultld) ld = nrows;
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	return GenericObject<T>(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <class T>
GenericObject<T> GenericObject<T>::zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	if(ld == defaultld) ld = nrows;
	T *values = bulk::alloc<T>(nrows, ncols, ld, true);
	return GenericObject<T>(nrows, ncols, values, ld, prop, true);
}
/*-------------------------------------------------*/
template <class T>
GenericObject<T> GenericObject<T>::random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	if(ld == defaultld) ld = nrows;
	T *values = bulk::alloc<T>(nrows, ncols, ld);
	bulk::rand(prop.type(), nrows, ncols, values, ld);
	return GenericObject<T>(nrows, ncols, values, ld, prop, true);
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
